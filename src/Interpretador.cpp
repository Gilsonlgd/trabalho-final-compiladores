#include "../include/Interpretador.h"
#include <iostream>
#include <string>
#include <queue>
#include <unordered_set>

Interpretador::Interpretador(const Gramatica &gramatica)
    : gramatica(gramatica) {}

/* Utilizar um algoritmo de busca em largura para reconhecer as palavras */
bool Interpretador::reconhecer(const std::string &palavra) {
    if (palavra.empty()) {
        std::cerr << "Palavra vazia." << std::endl;
        return false;
    }

    std::queue<std::string> fila;
    std::unordered_set<std::string> visitados; // Para evitar estados repetidos
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

        if (estado.size() > palavra.size() + 1) {
            continue;
        }

        for (size_t i = 0; i < estado.size(); ++i) {
            if (gramatica.getNaoTerminais().count(estado[i])) {
                char naoTerminal = estado[i];
                const auto& producoes = gramatica.getProducoes();

                std::cout << "Expandindo a partir de: " << naoTerminal << std::endl;

                for (const auto& producao : producoes) {
                    if (producao.naoTerminal == naoTerminal) {
                        for (const auto& alternativa : producao.producoes) {
                            std::string novoEstado;
                            if (alternativa == "#") {
                                novoEstado = estado.substr(0, i) + estado.substr(i + 1);
                            } else {
                                novoEstado = estado.substr(0, i) + alternativa + estado.substr(i + 1);
                            }

                            if (visitados.find(novoEstado) == visitados.end()) {
                                std::cout << "Aplicando producao: " << producao.naoTerminal << " -> " << alternativa << std::endl;
                                fila.push(novoEstado);
                                visitados.insert(novoEstado);
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
