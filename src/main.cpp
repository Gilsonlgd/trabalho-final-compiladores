#include <iostream>
#include "../include/Parser.h"
#include "../include/Interpretador.h"

int main() {
    std::string nomeArquivo = "gramatica.txt";
    Parser parser(nomeArquivo);

    if (!parser.parse()) {
        std::cerr << "Falha ao analisar a gramatica." << std::endl;
        return 1;
    }

    Interpretador interpretador(parser.getGramatica());
    std::string palavra;
    std::cout << "Digite uma palavra para ser validada: ";
    std::cin >> palavra;

    if (interpretador.reconhecer(palavra)) {
        std::cout << "A palavra eh valida." << std::endl;
    } else {
        std::cout << "A palavra nao eh valida." << std::endl;
    }

    return 0;
}
