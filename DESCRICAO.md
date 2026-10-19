# Controle de Gastos Pessoais

## Nome e ideia

O Controle de Gastos Pessoais é um sistema em modo texto para registrar e consultar despesas pessoais. Ele permite acompanhar os gastos, saber quanto foi gasto em cada categoria e identificar os maiores gastos do mês atual.

## O que o sistema guarda

Cada gasto possui:
- Descrição;
- Valor em reais;
- Data do gasto;
- Categoria.

O sistema também guarda os limites de gastos definidos pelo usuário para cada categoria. Uma categoria passa a existir quando o usuário define um limite para ela.

## O que dá para fazer

1. Cadastrar um gasto.
2. Listar todos os gastos cadastrados.
3. Consultar os gastos de uma categoria.
4. Consultar o total gasto por categoria.
5. Listar os maiores gastos do mês atual.
6. Definir ou alterar o limite de gastos de uma categoria.
7. Consultar as categorias cujo limite foi ultrapassado.
8. Encerrar o programa.

## Regras

- Todo gasto tem descrição obrigatória e não vazia, valor maior que zero, data válida e categoria.
- Gastos duplicados são permitidos.
- Uma categoria só existe a partir do momento em que o usuário define um limite para ela; para cadastrar um gasto em uma categoria nova, é preciso antes definir o limite dela.
- Categorias são comparadas sem diferenciar maiúsculas e minúsculas. Na exibição, é preservada a primeira grafia cadastrada.
- A data tem o formato DD/MM/AAAA e deve existir no calendário. Datas futuras são permitidas.
- Os dados ficam somente em memória, durante a execução do programa.
- Um limite de gastos pertence a uma categoria.
- Alterar o limite de uma categoria substitui o anterior; o limite deve ser maior que zero.
- O sistema calcula os totais a partir dos gastos cadastrados. Categorias sem gastos têm total zero.
- Total igual ao limite significa limite atingido, mas não ultrapassado. Só há ultrapassagem quando o total é maior que o limite.
- A consulta de totais por categoria mostra todas as categorias cadastradas.
- A consulta de maiores gastos considera o mês e o ano atuais do computador e mostra até cinco gastos, em ordem decrescente de valor. Em empate, ordena pela descrição em ordem alfabética, ignorando diferenças entre maiúsculas e minúsculas.
- A consulta de limites ultrapassados mostra somente categorias com limite definido cujo total seja maior que o limite.
- Nenhuma classe de lógica usa cin nem cout; a leitura e a escrita na tela ficam na interface.

## Quando algo dá errado

- Se o valor informado for inválido ou menor ou igual a zero, o gasto não será cadastrado.
- Se a descrição estiver vazia, se a data for inválida ou se a categoria não existir, o cadastro será recusado.
- Toda entrada inválida (texto onde se espera um número, data fora do formato, valor não numérico) gera mensagem de erro e nova tentativa do dado.
- Se uma categoria consultada não existir, o sistema informa que ela não está cadastrada.
- Se não houver gastos cadastrados, o sistema informará que não há gastos.
- Se houver gastos cadastrados, mas nenhum no mês atual, o sistema informará que não há gastos neste mês.
- Se uma categoria não possuir gastos, o total dessa categoria será zero.
- Se uma categoria não possuir limite definido, ela não será considerada como tendo ultrapassado um limite.
- Quando não houver dados a mostrar (lista vazia, nenhum limite definido ou nenhum limite ultrapassado), o sistema exibe uma mensagem explicativa e retorna ao menu.

## Classes que eu imagino

- Gasto: guarda a descrição, o valor, a data e a categoria de um gasto.
- Categoria: guarda o nome e o limite de gastos de uma categoria.
- ControleGastos: cadastra gastos e realiza consultas e cálculos.

A interface (menu, leitura e escrita na tela) fica em arquivos próprios, separados dessas classes.

## Exemplo de uso

Primeiro, o usuário define um limite de R$ 60,00 para a categoria "Alimentação". É nesse momento que a categoria passa a existir.

Depois, cadastra um gasto de R$ 50,00 com a descrição "Supermercado", na data 18/10/2026, na categoria "Alimentação".

Em seguida, cadastra outro gasto de R$ 20,00 na mesma categoria. Gastos duplicados também podem ser cadastrados sem problema.

Ao consultar o total da categoria Alimentação, o sistema mostra R$ 70,00 (e mostra zero para categorias cadastradas sem gastos).

Como R$ 70,00 é maior que o limite de R$ 60,00, a consulta de limites ultrapassados informa que o limite de Alimentação foi ultrapassado. Se o total fosse exatamente R$ 60,00, o limite estaria atingido, mas não ultrapassado.
