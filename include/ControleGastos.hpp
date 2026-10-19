#ifndef CONTROLEGASTOS_HPP
#define CONTROLEGASTOS_HPP

#include <map>
#include <string>
#include <vector>

#include "Categoria.hpp"

class ControleGastos {
public:
    bool definirLimite(const std::string& nome, double valor);
    bool existeCategoria(const std::string& nome) const;
    std::vector<Categoria> categorias() const;

private:
    std::map<std::string, Categoria> categorias_;
};

#endif
