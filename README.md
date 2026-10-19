# Controle de Gastos Pessoais

Sistema desenvolvido em C++ para cadastrar gastos, organizar categorias, definir limites de despesas e consultar totais e maiores gastos.

## Arquivos

```text
.
├── AGENTS.md
├── DESCRICAO.md
├── ENUNCIADO.md
├── PLANO.md
├── README.md
├── exemplos/
├── include/
└── src/
```

## Compilar e executar

```bash
g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude -o sistema
./sistema
```

## Onde uso a STL

| Onde | O quê | Por quê |
|---|---|---|
| `ControleGastos` | `map` de categorias | Utilizo para organizar as categorias pelo nome e facilitar a busca de uma categoria cadastrada. |
| `ControleGastos` | `list` de gastos | Utilizo para armazenar os gastos cadastrados e percorrê-los durante as consultas. |
| Consulta dos maiores gastos | `vector` e `sort` | Utilizo para reunir os gastos em um vetor temporário e ordená-los, facilitando a exibição dos maiores valores. |

## Como usei a IA

- **Modelo usado:** Big Pickle, utilizado por meio do OpenCode.

- **Um pedido que deu certo, e por que você acha que deu certo:** Pedir ajuda para dividir o desenvolvimento em etapas facilitou a organização do projeto. Assim, foi possível implementar as categorias e os limites primeiro e depois integrar as demais funcionalidades.

- **Um pedido que deu errado, o que veio errado e como você mudou o pedido:** Na primeira versão, a entrada de valores decimais com vírgula, como `100,00`, apresentou um problema. Foi necessário esclarecer melhor o comportamento esperado para que a implementação fosse ajustada.

- **Uma coisa que a IA sugeriu e você recusou, e por quê:** Durante o desenvolvimento, procurei manter o projeto dentro das regras do professor, utilizando C++11 e a biblioteca padrão. Por isso, qualquer sugestão que exigisse recursos fora dessas regras precisaria ser adaptada ou descartada.g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude -o sistema