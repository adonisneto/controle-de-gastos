# Controle de Gastos Pessoais

## Nome e ideia

O Controle de Gastos Pessoais é um sistema em modo texto para registrar e consultar despesas pessoais. Ele permite acompanhar os gastos, saber quanto foi gasto em cada categoria e identificar os maiores gastos de um mês.

## O que o sistema guarda

Cada gasto possui:
- Descrição;
- Valor em reais;
- Data do gasto;
- Categoria.

O sistema também guarda os limites de gastos definidos pelo usuário para cada categoria.

## O que dá para fazer

1. Cadastrar um gasto.
2. Listar todos os gastos cadastrados.
3. Consultar os gastos de uma categoria.
4. Consultar o total gasto por categoria.
5. Listar os maiores gastos de um mês.
6. Definir ou alterar o limite de gastos de uma categoria.
7. Consultar as categorias cujo limite foi ultrapassado.
8. Encerrar o programa.

## Regras

- O valor de um gasto deve ser maior que zero.
- A descrição, a data e a categoria são obrigatórias.
- As categorias são definidas pelo usuário.
- Os gastos ficam armazenados apenas durante a execução do programa.
- O sistema calcula os totais a partir dos gastos cadastrados.
- Um limite de gastos pertence a uma categoria.
- O sistema deve indicar quando o total gasto em uma categoria ultrapassar o limite definido.

## Quando algo dá errado

- Se o valor informado for inválido ou menor ou igual a zero, o gasto não será cadastrado.
- Se a descrição, a data ou a categoria estiver vazia, o cadastro será recusado.
- Se não houver gastos cadastrados, o sistema informará que a lista está vazia.
- Se uma categoria não possuir gastos, o total dessa categoria será zero.
- Se uma categoria não possuir limite definido, ela não será considerada como tendo ultrapassado um limite.
- Se o usuário digitar texto onde o programa espera um número, o sistema informará o erro e permitirá tentar novamente.

## Classes que eu imagino

- Gasto: guarda a descrição, o valor, a data e a categoria de um gasto.
- Categoria: guarda o nome e o limite de gastos de uma categoria.
- ControleGastos: cadastra gastos e realiza consultas e cálculos.

## Exemplo de uso

O usuário cadastra um gasto de R$ 50,00 com a descrição "Supermercado", na data 18/10/2026, na categoria "Alimentação".

Depois, cadastra outro gasto de R$ 20,00 na mesma categoria.

Ao consultar o total da categoria Alimentação, o sistema mostra R$ 70,00.

Se o usuário definir um limite de R$ 60,00 para Alimentação, o sistema informa que o limite foi ultrapassado.