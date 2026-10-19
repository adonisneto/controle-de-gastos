#include "Gasto.hpp"

Gasto::Gasto(const std::string& descricao, double valor, const Data& data,
             const std::string& categoria)
    : descricao_(descricao), valor_(valor), data_(data),
      categoria_(categoria) {
}

std::string Gasto::normalizar(const std::string& texto) {
    const std::string maiusculas = "ÁÀÂÃÉÊÍÓÔÕÚÜÇ";
    const std::string minusculas = "áàâãéêíóôõúüç";
    std::string chave;

    for (std::string::size_type i = 0; i < texto.size(); ++i) {
        unsigned char c = static_cast<unsigned char>(texto[i]);
        if (c >= 'A' && c <= 'Z') {
            chave += static_cast<char>(c + ('a' - 'A'));
        } else if (c == 0xC3 && i + 1 < texto.size()) {
            std::string par;
            par += texto[i];
            par += texto[i + 1];
            std::string::size_type pos = maiusculas.find(par);
            if (pos != std::string::npos) {
                chave += minusculas.substr(pos, 2);
                ++i;
            } else {
                chave += texto[i];
            }
        } else {
            chave += texto[i];
        }
    }
    return chave;
}

std::string Gasto::descricao() const {
    return descricao_;
}

double Gasto::valor() const {
    return valor_;
}

Data Gasto::data() const {
    return data_;
}

std::string Gasto::categoria() const {
    return categoria_;
}

bool Gasto::operator<(const Gasto& outro) const {
    if (valor_ != outro.valor_) {
        return valor_ > outro.valor_;
    }
    return normalizar(descricao_) < normalizar(outro.descricao_);
}
