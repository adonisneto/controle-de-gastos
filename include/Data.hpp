#ifndef DATA_HPP
#define DATA_HPP

#include <string>

class Data {
public:
    Data();

    bool definir(const std::string& texto);
    bool valida() const;
    int dia() const;
    int mes() const;
    int ano() const;
    std::string toString() const;

private:
    int dia_;
    int mes_;
    int ano_;
};

#endif
