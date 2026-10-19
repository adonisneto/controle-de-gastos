#ifndef GASTO_HPP
#define GASTO_HPP

#include <string>

#include "Data.hpp"

class Gasto {
public:
    Gasto(const std::string& descricao, double valor, const Data& data,
          const std::string& categoria);

    static std::string normalizar(const std::string& texto);

    std::string descricao() const;
    double valor() const;
    Data data() const;
    std::string categoria() const;

    bool operator<(const Gasto& outro) const;

private:
    std::string descricao_;
    double valor_;
    Data data_;
    std::string categoria_;
};

#endif
