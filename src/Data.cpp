#include "Data.hpp"

static bool bissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

static int diasDoMes(int mes, int ano) {
    static const int dias[12] = {31, 28, 31, 30, 31, 30,
                                 31, 31, 30, 31, 30, 31};
    if (mes < 1 || mes > 12) {
        return 0;
    }
    if (mes == 2 && bissexto(ano)) {
        return 29;
    }
    return dias[mes - 1];
}

static bool dataExiste(int dia, int mes, int ano) {
    if (ano < 1) {
        return false;
    }
    if (mes < 1 || mes > 12) {
        return false;
    }
    return dia >= 1 && dia <= diasDoMes(mes, ano);
}

static bool digito(char c) {
    return c >= '0' && c <= '9';
}

Data::Data() : dia_(0), mes_(0), ano_(0) {
}

bool Data::definir(const std::string& texto) {
    if (texto.size() != 10) {
        return false;
    }
    if (texto[2] != '/' || texto[5] != '/') {
        return false;
    }
    for (std::string::size_type i = 0; i < texto.size(); ++i) {
        if (i != 2 && i != 5 && !digito(texto[i])) {
            return false;
        }
    }

    int dia = (texto[0] - '0') * 10 + (texto[1] - '0');
    int mes = (texto[3] - '0') * 10 + (texto[4] - '0');
    int ano = (texto[6] - '0') * 1000 + (texto[7] - '0') * 100 +
              (texto[8] - '0') * 10 + (texto[9] - '0');

    if (!dataExiste(dia, mes, ano)) {
        return false;
    }

    dia_ = dia;
    mes_ = mes;
    ano_ = ano;
    return true;
}

bool Data::valida() const {
    return dataExiste(dia_, mes_, ano_);
}

int Data::dia() const {
    return dia_;
}

int Data::mes() const {
    return mes_;
}

int Data::ano() const {
    return ano_;
}

std::string Data::toString() const {
    std::string texto;
    texto += static_cast<char>('0' + dia_ / 10);
    texto += static_cast<char>('0' + dia_ % 10);
    texto += '/';
    texto += static_cast<char>('0' + mes_ / 10);
    texto += static_cast<char>('0' + mes_ % 10);
    texto += '/';
    texto += static_cast<char>('0' + ano_ / 1000 % 10);
    texto += static_cast<char>('0' + ano_ / 100 % 10);
    texto += static_cast<char>('0' + ano_ / 10 % 10);
    texto += static_cast<char>('0' + ano_ % 10);
    return texto;
}
