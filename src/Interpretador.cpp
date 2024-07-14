#include "../include/Interpretador.h"
#include <iostream>
#include <string>
#include <queue>

Interpretador::Interpretador(const Gramatica &gramatica)
    : gramatica(gramatica) {}

bool Interpretador::reconhecer(const std::string &palavra) {
    if (palavra.empty()) {
        std::cerr << "Palavra vazia." << std::endl;
        return false;
    }

    std::queue<std::string> fila;
    fila.push(std::string(1, gramatica.getSimboloInicial()));

    std::cout << "Simbolo inicial: " << gramatica.getSimboloInicial() << std::endl;

    while (!fila.empty()) {
        std::string estado = fila.front();
        fila.pop();

        std::cout << "Estado atual: " << estado << std::endl;

        if (estado == palavra) {
            std::cout << "Palavra reconhecida." << std::endl;
            return true;
        }

        if (estado.size() > palavra.size()) {
            return false;
        }

        for (size_t i = 0; i < estado.size(); ++i) {
            if (gramatica.getNaoTerminais().count(estado[i])) {
                char naoTerminal = estado[i];
                const auto& producoes = gramatica.getProducoes();

                std::cout << "Expandindo a partir de: " << estado[i] << std::endl;

                for (const auto& producao : producoes) {
                    if (producao.naoTerminal == naoTerminal) {
                        for (const auto& alternativa : producao.producoes) {
                            std::string novoEstado = estado.substr(0, i) + alternativa + estado.substr(i + 1);
                            if (novoEstado.length() <= palavra.length()) {
                                std::cout << "Aplicando producao: " << producao.naoTerminal << " -> " << alternativa << std::endl;
                                fila.push(novoEstado);
                            }
                        }
                    }
                }
            }
        }
    }

    std::cerr << "Erro na posicao: " << palavra.length() << std::endl;
    return false;
}
