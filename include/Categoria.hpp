#ifndef CATEGORIA_HPP
#define CATEGORIA_HPP

#include <string>

class Categoria {
public:
    Categoria(const std::string& nome, double limite);

    bool definirLimite(double limite);
    std::string nome() const;
    double limite() const;

private:
    std::string nome_;
    double limite_;
};

#endif
