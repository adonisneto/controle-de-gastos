#include "Categoria.hpp"

Categoria::Categoria(const std::string& nome, double limite)
    : nome_(nome), limite_(limite) {
}

bool Categoria::definirLimite(double limite) {
    if (limite <= 0) {
        return false;
    }
    limite_ = limite;
    return true;
}

std::string Categoria::nome() const {
    return nome_;
}

double Categoria::limite() const {
    return limite_;
}
