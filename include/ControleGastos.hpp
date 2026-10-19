#ifndef CONTROLEGASTOS_HPP
#define CONTROLEGASTOS_HPP

#include <list>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "Categoria.hpp"
#include "Gasto.hpp"

class ControleGastos {
public:
    bool definirLimite(const std::string& nome, double valor);
    bool existeCategoria(const std::string& nome) const;
    std::vector<Categoria> categorias() const;

    bool cadastrarGasto(const std::string& descricao, double valor,
                        const Data& data, const std::string& categoria);
    std::vector<Gasto> gastos() const;
    bool gastosDaCategoria(const std::string& nome,
                           std::vector<Gasto>& saida) const;
    std::vector<std::pair<std::string, double> > totaisPorCategoria() const;
    std::vector<Categoria> categoriasUltrapassadas() const;
    std::vector<Gasto> maioresGastosDoMes(int mes, int ano) const;

private:
    double totalDaCategoria(const std::string& chave) const;

    std::map<std::string, Categoria> categorias_;
    std::list<Gasto> gastos_;
};

#endif
