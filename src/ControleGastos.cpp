#include "ControleGastos.hpp"

static std::string normalizar(const std::string& nome) {
    const std::string maiusculas = "ÁÀÂÃÉÊÍÓÔÕÚÜÇ";
    const std::string minusculas = "áàâãéêíóôõúüç";
    std::string chave;

    for (std::string::size_type i = 0; i < nome.size(); ++i) {
        unsigned char c = static_cast<unsigned char>(nome[i]);
        if (c >= 'A' && c <= 'Z') {
            chave += static_cast<char>(c + ('a' - 'A'));
        } else if (c == 0xC3 && i + 1 < nome.size()) {
            std::string par;
            par += nome[i];
            par += nome[i + 1];
            std::string::size_type pos = maiusculas.find(par);
            if (pos != std::string::npos) {
                chave += minusculas.substr(pos, 2);
                ++i;
            } else {
                chave += nome[i];
            }
        } else {
            chave += nome[i];
        }
    }
    return chave;
}

bool ControleGastos::definirLimite(const std::string& nome, double valor) {
    if (nome.empty() || valor <= 0) {
        return false;
    }

    std::string chave = normalizar(nome);
    std::map<std::string, Categoria>::iterator it = categorias_.find(chave);
    if (it != categorias_.end()) {
        return it->second.definirLimite(valor);
    }

    Categoria categoria(nome, valor);
    categorias_.insert(std::make_pair(chave, categoria));
    return true;
}

bool ControleGastos::existeCategoria(const std::string& nome) const {
    return categorias_.find(normalizar(nome)) != categorias_.end();
}

std::vector<Categoria> ControleGastos::categorias() const {
    std::vector<Categoria> lista;
    for (std::map<std::string, Categoria>::const_iterator it = categorias_.begin();
         it != categorias_.end(); ++it) {
        lista.push_back(it->second);
    }
    return lista;
}
