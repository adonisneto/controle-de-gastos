#include "interface.hpp"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Categoria.hpp"
#include "ControleGastos.hpp"
#include "Data.hpp"
#include "Gasto.hpp"

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
    std::string texto = linha;
    for (std::string::size_type i = 0; i < texto.size(); ++i) {
        if (texto[i] == ',') {
            texto[i] = '.';
        }
    }
    std::istringstream fluxo(texto);
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

static void mostrarGasto(const Gasto& gasto) {
    std::cout << "  " << gasto.data().toString() << " | "
              << gasto.descricao() << " | " << reais(gasto.valor()) << " | "
              << gasto.categoria() << std::endl;
}

static bool lerNomeCategoria(const std::string& titulo, std::string& nome) {
    while (true) {
        std::cout << titulo;
        if (!lerLinha(nome)) {
            return false;
        }
        if (!nome.empty()) {
            return true;
        }
        std::cout << "Erro: o nome da categoria não pode ficar vazio."
                  << std::endl;
    }
}

static void cadastrarGasto(ControleGastos& controle) {
    std::string descricao;
    while (true) {
        std::cout << "Descrição: ";
        if (!lerLinha(descricao)) {
            return;
        }
        if (!descricao.empty()) {
            break;
        }
        std::cout << "Erro: a descrição não pode ficar vazia." << std::endl;
    }

    double valor = 0;
    while (true) {
        std::cout << "Valor (R$): ";
        std::string linha;
        if (!lerLinha(linha)) {
            return;
        }
        if (!interpretarNumero(linha, valor)) {
            std::cout << "Erro: digite um número válido." << std::endl;
            continue;
        }
        if (valor > 0) {
            break;
        }
        std::cout << "Erro: o valor deve ser maior que zero." << std::endl;
    }

    Data data;
    while (true) {
        std::cout << "Data (DD/MM/AAAA): ";
        std::string linha;
        if (!lerLinha(linha)) {
            return;
        }
        if (data.definir(linha)) {
            break;
        }
        std::cout << "Erro: data inválida. Use DD/MM/AAAA com data que exista."
                  << std::endl;
    }

    std::string categoria;
    while (true) {
        if (!lerNomeCategoria("Categoria: ", categoria)) {
            return;
        }
        if (controle.existeCategoria(categoria)) {
            break;
        }
        std::cout << "Erro: a categoria \"" << categoria
                  << "\" não está cadastrada." << std::endl;
    }

    if (controle.cadastrarGasto(descricao, valor, data, categoria)) {
        std::cout << "Gasto cadastrado." << std::endl;
    } else {
        std::cout << "Erro: gasto não cadastrado." << std::endl;
    }
}

static void listarGastos(const ControleGastos& controle) {
    std::vector<Gasto> lista = controle.gastos();
    if (lista.empty()) {
        std::cout << "Não há gastos cadastrados." << std::endl;
        return;
    }
    std::cout << "Gastos cadastrados:" << std::endl;
    for (std::vector<Gasto>::size_type i = 0; i < lista.size(); ++i) {
        mostrarGasto(lista[i]);
    }
}

static void gastosDaCategoria(const ControleGastos& controle) {
    std::string nome;
    if (!lerNomeCategoria("Categoria: ", nome)) {
        return;
    }
    std::vector<Gasto> lista;
    if (!controle.gastosDaCategoria(nome, lista)) {
        std::cout << "A categoria \"" << nome
                  << "\" não está cadastrada." << std::endl;
        return;
    }
    if (lista.empty()) {
        std::cout << "Não há gastos na categoria \"" << nome << "\"."
                  << std::endl;
        return;
    }
    std::cout << "Gastos da categoria " << nome << ":" << std::endl;
    for (std::vector<Gasto>::size_type i = 0; i < lista.size(); ++i) {
        mostrarGasto(lista[i]);
    }
}

static void totaisPorCategoria(const ControleGastos& controle) {
    std::vector<std::pair<std::string, double> > linhas =
        controle.totaisPorCategoria();
    if (linhas.empty()) {
        std::cout << "Não há categorias cadastradas." << std::endl;
        return;
    }
    std::cout << "Totais por categoria:" << std::endl;
    for (std::vector<std::pair<std::string, double> >::size_type i = 0;
         i < linhas.size(); ++i) {
        std::cout << "  " << linhas[i].first << " - total "
                  << reais(linhas[i].second) << std::endl;
    }
}

static void maioresGastos(const ControleGastos& controle) {
    if (controle.gastos().empty()) {
        std::cout << "Não há gastos cadastrados." << std::endl;
        return;
    }

    std::time_t agora = std::time(0);
    std::tm* momento = std::localtime(&agora);
    int mes = momento->tm_mon + 1;
    int ano = momento->tm_year + 1900;

    std::vector<Gasto> lista = controle.maioresGastosDoMes(mes, ano);
    if (lista.empty()) {
        std::cout << "Não há gastos neste mês." << std::endl;
        return;
    }

    std::ostringstream titulo;
    titulo << (mes < 10 ? "0" : "") << mes << "/" << ano;
    std::cout << "Maiores gastos de " << titulo.str() << " (até 5):"
              << std::endl;
    for (std::vector<Gasto>::size_type i = 0; i < lista.size(); ++i) {
        mostrarGasto(lista[i]);
    }
}

static void definirLimite(ControleGastos& controle) {
    mostrarCategorias(controle);

    std::string nome;
    if (!lerNomeCategoria("Nome da categoria: ", nome)) {
        return;
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

static void categoriasUltrapassadas(const ControleGastos& controle) {
    if (controle.categorias().empty()) {
        std::cout << "Não há categorias cadastradas." << std::endl;
        return;
    }
    std::vector<Categoria> lista = controle.categoriasUltrapassadas();
    if (lista.empty()) {
        std::cout << "Nenhum limite foi ultrapassado." << std::endl;
        return;
    }
    std::cout << "Categorias com limite ultrapassado:" << std::endl;
    for (std::vector<Categoria>::size_type i = 0; i < lista.size(); ++i) {
        std::cout << "  " << lista[i].nome()
                  << " - limite " << reais(lista[i].limite()) << std::endl;
    }
}

static void mostrarMenu() {
    std::cout << std::endl;
    std::cout << "1 - Cadastrar um gasto" << std::endl;
    std::cout << "2 - Listar todos os gastos cadastrados" << std::endl;
    std::cout << "3 - Consultar os gastos de uma categoria" << std::endl;
    std::cout << "4 - Consultar o total gasto por categoria" << std::endl;
    std::cout << "5 - Listar os maiores gastos do mês atual" << std::endl;
    std::cout << "6 - Definir ou alterar o limite de gastos de uma categoria"
              << std::endl;
    std::cout << "7 - Consultar as categorias cujo limite foi ultrapassado"
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
            std::cout << "Erro: digite um número entre 1 e 8." << std::endl;
            continue;
        }

        if (opcao == 1) {
            cadastrarGasto(controle);
        } else if (opcao == 2) {
            listarGastos(controle);
        } else if (opcao == 3) {
            gastosDaCategoria(controle);
        } else if (opcao == 4) {
            totaisPorCategoria(controle);
        } else if (opcao == 5) {
            maioresGastos(controle);
        } else if (opcao == 6) {
            definirLimite(controle);
        } else if (opcao == 7) {
            categoriasUltrapassadas(controle);
        } else if (opcao == 8) {
            std::cout << "Encerrando o programa." << std::endl;
            return;
        } else {
            std::cout << "Erro: opção inválida. Digite um número entre 1 e 8."
                      << std::endl;
        }
    }
}
