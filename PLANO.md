# Plano de implementação — Controle de Gastos Pessoais

Plano feito a partir de `DESCRICAO.md`, `AGENTS.md` e `ENUNCIADO.md`.
Sem código: só arquivos, classes, métodos (descritos em palavras) e testes.
Cada etapa termina com o programa compilando e algo que dá para testar.

## Visão geral das etapas

| Etapa | O que ela entrega | Opções do menu que já funcionam |
| --- | --- | --- |
| 1 | Estrutura de pastas, `Categoria`, limites | 6 e 8 |
| 2 | `Data`, `Gasto`, cadastro e listagem | 1, 2, 6, 8 |
| 3 | Consultas por categoria (gastos e total) | 3, 4 |
| 4 | Consulta de limites ultrapassados | 7 |
| 5 | Maiores gastos do mês atual | 5 |
| 6 | Revisão, mensagens de vazio e exemplos completos | 1 a 8 |

O menu começa apenas com as opções prontas e cresce etapa a etapa — assim não
fica botão que não faz nada. Ao final ele tem as oito opções do `DESCRICAO.md`,
na mesma ordem.

## Decisões de projeto (valem para todas as etapas)

**Containers da STL** (atende os requisitos da seção 2 do `ENUNCIADO.md`):

- `map<string, Categoria>` dentro de `ControleGastos`: guarda as categorias e
  seus limites. A chave é o nome em minúsculas; assim a comparação ignora
  maiúsculas/minúsculas e a listagem de todas as categorias já sai em ordem
  alfabética. **Atende "pelo menos um map".**
- `list<Gasto>` dentro de `ControleGastos`: guarda os gastos na ordem de
  cadastro. Só se acrescenta no fim e se percorre inteira — nunca é preciso
  acessar pela posição. **Atende "pelo menos um set ou list".**
- `vector<Gasto>` temporário, usado só dentro da consulta da opção 5: copia os
  gastos do mês pedido e ordena com `std::sort`, aplicado aos objetos `Gasto`
  através do `operator<` definido na própria classe `Gasto`.
  **Atende "sort com operator< da sua classe" (exemplo 11 da aula).**

**Comparação de categorias sem caixa:** a chave do `map` é o nome em
minúsculas, e a `Categoria` guarda a primeira grafia digitada — é a que aparece
na tela. Não precisa de comparador especial nem de lambda.

**Classe `Data` de apoio:** o `DESCRICAO.md` imagina `Gasto`, `Categoria` e
`ControleGastos`; o `ENUNCIADO.md` pede "pelo menos três classes". A `Data`
(dia, mês, ano + validação de calendário) entra como quarta classe, para não
jogar a validação de data dentro do `Gasto`. Se você preferir guardar os três
números direto no `Gasto`, a decisão é sua — me avise.

**Quem lê o relógio:** a regra diz que a opção 5 considera o mês e o ano
atuais do computador. Quem lê o relógio (`<ctime>`) é a **interface**, que
passa mês e ano como parâmetro para a lógica. Assim `ControleGastos` não
acessa o relógio e continua sendo uma classe testável.

**Interface:** `interface.hpp` / `interface.cpp` com as funções do menu, e
`main.cpp` só com o `main`. Nenhuma classe de lógica usa `cin` nem `cout`.
A leitura é feita pela linha inteira (`getline`) e interpretada com
`istringstream`: texto onde se espera número não derruba o programa — mostra
erro e pede de novo, como manda o `DESCRICAO.md`.

**Regras gerais do `AGENTS.md`:** C++11, só biblioteca padrão, sem `new`/`delete`
(objetos guardados direto nos containers), sem lambda e sem `unordered_map`,
uma classe por par de arquivos, um `.cpp` da interface, e o comando de
compilação continua o do `README.md`:

```bash
g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude -o sistema
```

## Arquivos do projeto

```text
include/Data.hpp            src/Data.cpp
include/Gasto.hpp           src/Gasto.cpp
include/Categoria.hpp       src/Categoria.cpp
include/ControleGastos.hpp  src/ControleGastos.cpp
include/interface.hpp       src/interface.cpp
                            src/main.cpp
                            exemplos/cenario1.txt ... cenario5.txt
```

---

## Etapa 1 — Estrutura, Categoria e limites (opções 6 e 8)

**Objetivo:** montar o esqueleto e já dar eixo de limite de categoria, que é
de onde as categorias nascem.

**Arquivos criados:** `include/Categoria.hpp`, `src/Categoria.cpp`,
`include/ControleGastos.hpp`, `src/ControleGastos.cpp`,
`include/interface.hpp`, `src/interface.cpp`, `src/main.cpp`.

**Categoria** guarda: a grafia original do nome e o limite.

- `definirLimite(nome, valor)`: cria a categoria com esse limite ou substitui
  o limite anterior; recusa valor menor ou igual a zero.
- Acesso ao nome e ao limite para exibição.

**ControleGastos** guarda: o `map` de categorias.

- `definirLimite(nome, valor)`: normaliza a chave (minúsculas), cria ou
  atualiza a `Categoria`; devolve `bool` dizendo se deu certo.
- `existeCategoria(nome)`: procura pela chave normalizada.
- `categorias()`: devolve as categorias para a interface exibir, com a grafia
  original e em ordem alfabética (ordem natural do `map`).

**Interface:** menu com as opções 6 e 8; função de leitura de número
(`getline` + `istringstream`); leitura do nome e do valor do limite com
tratamento de erro e nova tentativa; mensagens de limite alterado e de limite
inválido; `main` chama a interface.

**Testes desta etapa:**

- Normal: definir limite novo; alterar um limite (o anterior é substituído).
- Inválidas: valor `0`; valor negativo; texto onde se espera o número (no
  limite e na opção do menu) — mensagem de erro e nova tentativa.
- Categorias: `alimentação` e `Alimentação` caem na mesma categoria; na
  tela aparece sempre a primeira grafia digitada.
- Sem dados: opção 6 é a primeira coisa a ser usada — não há menu morto.

**Fim da etapa:** compilar com o comando do `README.md`, sem avisos com
`-Wall -Wextra`; rodar `exemplos/cenario1.txt`; commit.

---

## Etapa 2 — Data, Gasto, cadastro e listagem (opções 1 e 2)

**Objetivo:** representar datas válidas e cadastrar/listar gastos.

**Arquivos criados:** `include/Data.hpp`, `src/Data.cpp`,
`include/Gasto.hpp`, `src/Gasto.cpp`.
**Arquivos alterados:** `ControleGastos` (ganha a lista de gastos),
`interface` (ganha as opções 1 e 2).

**Data** guarda dia, mês e ano.

- Leitura a partir de `DD/MM/AAAA`: confere o formato e se a data existe no
  calendário (31/02/2026 recusada); datas futuras são aceitas.
- Conversão de volta para `DD/MM/AAAA` (string) para exibição.
- Acesso a mês e ano (será usado na etapa 5).

**Gasto** guarda descrição, valor, `Data` e o nome da categoria.

- `descricao()`, `valor()`, `data()`, `categoria()`.

**ControleGastos** ganha: o `list<Gasto>` de gastos.

- `cadastrarGasto(descrição, valor, data, categoria)`: valida tudo —
  descrição não vazia, valor maior que zero, data válida, categoria existente
  no `map`. Duplicados são aceitos sem checagem. Devolve `bool`.
- `gastos()`: devolve todos, na ordem de cadastro.

**Interface:** opção 1 pede os quatro dados, repetindo com mensagem de erro o
que estiver inválido; opção 2 lista os gastos ou informa que não há gastos
cadastrados.

**Testes desta etapa:**

- Normal: cadastrar gasto do exemplo do `DESCRICAO.md` (R$ 50,00,
  "Supermercado", 18/10/2026, categoria já existente); cadastrar duplicado
  (mesmos dados) — é aceito; listar aparece tudo na ordem de cadastro.
- Inválidas: valor `0`, negativo e texto; descrição vazia; categoria não
  cadastrada; texto no menu.
- Datas: `31/02/2026`, `32/01/2026`, `00/01/2026`, `10/13/2026`, `abc`,
  `18-10-2026` — todas recusadas; `18/10/2026` aceita; data futura (ex.:
  `01/01/2099`) aceita.
- Sem dados: listar sem nenhum gasto → "não há gastos cadastrados".

**Fim da etapa:** compilar sem avisos; rodar `exemplos/cenario1.txt` (não
quebrou) e `exemplos/cenario2.txt`; commit.

---

## Etapa 3 — Consultas por categoria (opções 3 e 4)

**Objetivo:** responder "quanto e o quê" em cada categoria.

**Arquivos alterados:** `ControleGastos`, `interface`.
Nenhum arquivo novo.

**ControleGastos** ganha:

- `gastosDaCategoria(nome)`: devolve um resultado que diz se a categoria
  existe; se existe, traz os gastos dela (comparação sem caixa).
- `totaisPorCategoria()`: devolve uma linha por categoria cadastrada —
  grafia original e total — inclusive as que têm total zero.

**Interface:** opção 3 mostra os gastos da categoria; se a categoria não
existir, informa que ela não está cadastrada; se existir mas não tiver
gastos, informa que não há gastos nela. Opção 4 mostra todos os totais; sem
nenhuma categoria, mensagem explicativa e volta ao menu.

**Testes desta etapa:**

- Normal: categoria com gastos soma certo (ex.: 50 + 20 = R$ 70,00).
- Categorias: consultar `ALIMENTAÇÃO` acha gastos de `Alimentação`;
  categoria cadastrada sem gastos aparece com total zero; categoria
  inexistente → "não está cadastrada".
- Sem dados: opções 3 e 4 com sistema vazio → mensagens explicativas.

**Fim da etapa:** compilar sem avisos; rodar os cenários 1 a 3; commit.

---

## Etapa 4 — Limites ultrapassados (opção 7)

**Objetivo:** cruzar totais com limites.

**Arquivos alterados:** `ControleGastos`, `interface`.

**ControleGastos** ganha:

- `categoriasUltrapassadas()`: percorre o `map`; inclui a categoria só quando
  tem limite definido **e** total maior que o limite. Total igual ao limite
  é limite atingido, **não** ultrapassado — não entra na lista.

**Interface:** opção 7 mostra a lista com grafia original, nome e valores; se
não houver categorias, nenhum limite definido ou nenhum ultrapassado, mensagem
explicativa e volta ao menu (as três situações têm mensagens diferentes).

**Testes desta etapa:**

- Normal: total acima do limite aparece; categoria do exemplo do
  `DESCRICAO.md` (total 70, limite 60) aparece como ultrapassada.
- Limites: total **igual** ao limite não aparece (atingido); categoria sem
  limite nunca aparece; categoria com limite e zero gastos não aparece.
- Sem dados: sem nenhuma categoria → mensagem; com categorias e nenhum
  ultrapassado → outra mensagem.

**Fim da etapa:** compilar sem avisos; rodar os cenários 1 a 4; commit.

---

## Etapa 5 — Maiores gastos do mês atual (opção 5)

**Objetivo:** ordenar com `std::sort` e o `operator<` do `Gasto`.

**Arquivos alterados:** `Gasto` (ganha `operator<`), `ControleGastos`,
`interface`.

**Gasto** ganha `operator<`, que define a ordem de exibição da opção 5: vem
antes quem tem valor maior; em empate de valor, vem primeiro quem tem
descrição em ordem alfabética, ignorando maiúsculas/minúsculas. Com esse
`operator<`, um `std::sort` simples já deixa o `vector` pronto para exibir.

**ControleGastos** ganha:

- `maioresGastosDoMes(mes, ano)`: filtra a `list` do mês e ano pedidos,
  copia para um `vector<Gasto>` temporário, ordena com `std::sort` e devolve
  até cinco gastos.

**Interface:** opção 5 lê o mês e o ano atuais do computador (`<ctime>`) e
passa para a lógica. Mensagens: sem nenhum gasto no sistema → "não há gastos
cadastrados"; com gastos, mas nenhum no mês atual → "não há gastos neste
mês" (os dois casos são diferentes, como manda o `DESCRICAO.md`).

**Testes desta etapa:**

- Normal: mais de cinco gastos no mês → aparecem os cinco maiores, do maior
  para o menor; menos de cinco → aparecem todos.
- Empate: dois gastos com o mesmo valor, descrições `Mercado` e `mercado` →
  ordem alfabética ignorando a caixa.
- Datas/mês: gasto de outro mês (inclusive futuro) não aparece; gasto do mês
  atual aparece.
- Sem dados: sistema vazio → primeira mensagem; sistema com gastos só de
  outro mês → segunda mensagem.
- Inválidas: texto na opção do menu → erro e nova tentativa.

> Observação: a saída desta opção depende do relógio da máquina. No
> `exemplos/cenario5.txt` cadastre gastos em vários meses; a conferência é
> olhando a tela (os cinco maiores devem ser sempre do mês corrente).

**Fim da etapa:** compilar sem avisos; rodar os cenários 1 a 5; commit.

---

## Etapa 6 — Revisão e bateria completa

**Objetivo:** fechar o sistema e conferir tudo de uma vez.

**Arquivos alterados:** `interface` (menu final com as oito opções na ordem do
`DESCRICAO.md`), `exemplos/` (completar cenários).

**O que fazer:**

1. Conferir se todas as regras do `DESCRICAO.md` têm teste correspondente
   (lista abaixo).
2. Conferir todas as mensagens de "não há dados" e a separação entre "não há
   gastos" e "não há gastos no mês".
3. Compilar com `-Wall -Wextra` e ler cada aviso; rodar os cinco cenários em
   sequência, um por execução.
4. `git status` e `git diff`: nenhum arquivo inesperado, nenhum `.o` nem
   executável commitado.
5. Commit da etapa final. (Os commits de cada etapa são feitos por você, um
   por etapa, como pede o `ENUNCIADO.md`.)
6. Depois, sem IA: preencher a seção "Onde uso a STL" do `README.md`, usando
   a tabela de decisões de projeto lá em cima.

## Bateria de testes consolidada

- **Situações normais:** definir e alterar limite; cadastrar gastos simples e
  duplicados; listar tudo; total por categoria; cinco maiores do mês; limite
  ultrapassado.
- **Entradas inválidas:** texto no lugar de número (menu, valor, limite);
  valor zero ou negativo; descrição vazia; categoria não cadastrada; toda
  entrada inválida gera erro e nova tentativa.
- **Datas:** formato `DD/MM/AAAA` aceito; fora do calendário recusado
  (`31/02/2026`, `10/13/2026`, `00/01/2026`); fora do formato recusado;
  data futura aceita; filtro por mês atual ignora os demais.
- **Categorias:** comparação sem caixa; primeira grafia preservada na tela;
  categoria nasce pelo limite; consultá-la sem cadastro → "não está
  cadastrada"; categorias sem gastos com total zero aparecem na opção 4.
- **Limites:** alterar substitui; maior que zero; total igual = atingido e
  não ultrapassado; total maior = ultrapassado; sem limite = nunca
  ultrapassado.

## Detalhes que este plano assumiu (confirme se discordar)

- O formato `DD/MM/AAAA` significa exatamente dois dígitos para dia e mês e
  quatro para ano (`1/1/2026` seria recusado).
- O valor usa ponto como separador decimal (`50.50`); vírgula (`50,50`) é
  tratada como entrada inválida.
- Descrição só com espaços é aceita (apenas a string vazia é recusada). Se
  preferir tratar espaços como vazia, é uma regra a acrescentar no
  `DESCRICAO.md`.
