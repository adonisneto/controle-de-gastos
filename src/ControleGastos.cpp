#include "ControleGastos.hpp"

#include <algorithm>

bool ControleGastos::definirLimite(const std::string& nome, double valor) {
    if (nome.empty() || valor <= 0) {
        return false;
    }

    std::string chave = Gasto::normalizar(nome);
    std::map<std::string, Categoria>::iterator it = categorias_.find(chave);
    if (it != categorias_.end()) {
        return it->second.definirLimite(valor);
    }

    Categoria categoria(nome, valor);
    categorias_.insert(std::make_pair(chave, categoria));
    return true;
}

bool ControleGastos::existeCategoria(const std::string& nome) const {
    return categorias_.find(Gasto::normalizar(nome)) != categorias_.end();
}

std::vector<Categoria> ControleGastos::categorias() const {
    std::vector<Categoria> lista;
    for (std::map<std::string, Categoria>::const_iterator it = categorias_.begin();
         it != categorias_.end(); ++it) {
        lista.push_back(it->second);
    }
    return lista;
}

bool ControleGastos::cadastrarGasto(const std::string& descricao, double valor,
                                    const Data& data,
                                    const std::string& categoria) {
    if (descricao.empty() || valor <= 0 || !data.valida() ||
        !existeCategoria(categoria)) {
        return false;
    }
    gastos_.push_back(Gasto(descricao, valor, data, categoria));
    return true;
}

std::vector<Gasto> ControleGastos::gastos() const {
    return std::vector<Gasto>(gastos_.begin(), gastos_.end());
}

bool ControleGastos::gastosDaCategoria(const std::string& nome,
                                       std::vector<Gasto>& saida) const {
    saida.clear();
    if (!existeCategoria(nome)) {
        return false;
    }
    std::string chave = Gasto::normalizar(nome);
    for (std::list<Gasto>::const_iterator it = gastos_.begin();
         it != gastos_.end(); ++it) {
        if (Gasto::normalizar(it->categoria()) == chave) {
            saida.push_back(*it);
        }
    }
    return true;
}

double ControleGastos::totalDaCategoria(const std::string& chave) const {
    double total = 0;
    for (std::list<Gasto>::const_iterator it = gastos_.begin();
         it != gastos_.end(); ++it) {
        if (Gasto::normalizar(it->categoria()) == chave) {
            total += it->valor();
        }
    }
    return total;
}

std::vector<std::pair<std::string, double> >
ControleGastos::totaisPorCategoria() const {
    std::vector<std::pair<std::string, double> > linhas;
    for (std::map<std::string, Categoria>::const_iterator it = categorias_.begin();
         it != categorias_.end(); ++it) {
        linhas.push_back(
            std::make_pair(it->second.nome(), totalDaCategoria(it->first)));
    }
    return linhas;
}

std::vector<Categoria> ControleGastos::categoriasUltrapassadas() const {
    std::vector<Categoria> lista;
    for (std::map<std::string, Categoria>::const_iterator it = categorias_.begin();
         it != categorias_.end(); ++it) {
        if (totalDaCategoria(it->first) > it->second.limite()) {
            lista.push_back(it->second);
        }
    }
    return lista;
}

std::vector<Gasto> ControleGastos::maioresGastosDoMes(int mes, int ano) const {
    std::vector<Gasto> doMes;
    for (std::list<Gasto>::const_iterator it = gastos_.begin();
         it != gastos_.end(); ++it) {
        if (it->data().mes() == mes && it->data().ano() == ano) {
            doMes.push_back(*it);
        }
    }
    std::sort(doMes.begin(), doMes.end());
    if (doMes.size() > 5) {
        doMes.erase(doMes.begin() + 5, doMes.end());
    }
    return doMes;
}
