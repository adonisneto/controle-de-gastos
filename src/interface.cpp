#include "interface.hpp"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Categoria.hpp"
#include "ControleGastos.hpp"

static std::string reais(double valor) {
    std::ostringstream fluxo;
    fluxo << std::fixed << std::setprecision(2) << valor;
    std::string texto = fluxo.str();
    for (std::string::size_type i = 0; i < texto.size(); ++i) {
        if (texto[i] == '.') {
            texto[i] = ',';
        }
    }
    return "R$ " + texto;
}

static bool lerLinha(std::string& linha) {
    return static_cast<bool>(std::getline(std::cin, linha));
}

static bool interpretarInteiro(const std::string& linha, int& valor) {
    std::istringstream fluxo(linha);
    char sobra;
    if (!(fluxo >> valor)) {
        return false;
    }
    if (fluxo >> sobra) {
        return false;
    }
    return true;
}

static bool interpretarNumero(const std::string& linha, double& valor) {
    std::istringstream fluxo(linha);
    char sobra;
    if (!(fluxo >> valor)) {
        return false;
    }
    if (fluxo >> sobra) {
        return false;
    }
    return true;
}

static void mostrarCategorias(const ControleGastos& controle) {
    std::vector<Categoria> lista = controle.categorias();
    if (lista.empty()) {
        std::cout << "Categorias cadastradas: nenhuma." << std::endl;
        return;
    }
    std::cout << "Categorias cadastradas:" << std::endl;
    for (std::vector<Categoria>::size_type i = 0; i < lista.size(); ++i) {
        std::cout << "  " << lista[i].nome()
                  << " - limite " << reais(lista[i].limite()) << std::endl;
    }
}

static void definirLimite(ControleGastos& controle) {
    mostrarCategorias(controle);

    std::string nome;
    while (true) {
        std::cout << "Nome da categoria: ";
        if (!lerLinha(nome)) {
            return;
        }
        if (!nome.empty()) {
            break;
        }
        std::cout << "Erro: o nome da categoria não pode ficar vazio."
                  << std::endl;
    }

    while (true) {
        std::cout << "Valor do limite (R$): ";
        std::string linha;
        if (!lerLinha(linha)) {
            return;
        }
        double valor;
        if (!interpretarNumero(linha, valor)) {
            std::cout << "Erro: digite um número válido." << std::endl;
            continue;
        }
        if (controle.definirLimite(nome, valor)) {
            std::cout << "Limite definido." << std::endl;
            mostrarCategorias(controle);
            return;
        }
        std::cout << "Erro: o limite deve ser maior que zero." << std::endl;
    }
}

static void mostrarMenu() {
    std::cout << std::endl;
    std::cout << "6 - Definir ou alterar o limite de gastos de uma categoria"
              << std::endl;
    std::cout << "8 - Encerrar o programa" << std::endl;
    std::cout << "Opção: ";
}

void executar() {
    ControleGastos controle;

    std::cout << "Controle de Gastos Pessoais" << std::endl;

    while (true) {
        mostrarMenu();

        std::string linha;
        if (!lerLinha(linha)) {
            std::cout << std::endl << "Encerrando o programa." << std::endl;
            return;
        }

        int opcao;
        if (!interpretarInteiro(linha, opcao)) {
            std::cout << "Erro: digite um número válido (6 ou 8)."
                      << std::endl;
            continue;
        }

        if (opcao == 6) {
            definirLimite(controle);
        } else if (opcao == 8) {
            std::cout << "Encerrando o programa." << std::endl;
            return;
        } else {
            std::cout << "Erro: opção inválida. Digite 6 ou 8." << std::endl;
        }
    }
}
