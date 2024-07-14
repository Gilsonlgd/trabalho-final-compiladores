# Trabalho Final de Compiladores - Gilson Garcia

## Compilação
```bash	
g++ -o main ./src/main.cpp ./src/Gramatica.cpp ./src/Parser.cpp ./src/Interpretador.cpp
```

## Execução
```bash
./main
```

## Gramática
A gramática deverá ser informada no arquivo "gramatica.txt" seguindo o seguinte padrão:
```bash
Simbolos nao terminais (separados por espaço)
Simbolos terminais (separados por espaço)
Simbolo inicial
Produções (uma por linha)
```
- Produções alternativas devem ser separadas por "|".
- Não pode haver espaços entre produções alternativas.
- Exemplo:
```bash
S A B
a b
S
S -> aA
A -> bB
B -> a|b|#
```
onde "#" é o símbolo que representa o vazio.

## Descrição
Ao executar o programa, o usuário deverá informar a palavra a ser validada. O programa irá informar se a palavra é válida ou não, e caso seja válida, irá informar os movimentos entre as produções da gramática.

## Alunos
- Gilson Garcia
- Jhuan Luis