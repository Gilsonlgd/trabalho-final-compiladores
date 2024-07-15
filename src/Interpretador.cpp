#include "../include/Interpretador.h"
#include <iostream>
#include <string>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <vector>

Interpretador::Interpretador(const Gramatica &gramatica)
    : gramatica(gramatica) {}

/* Utiliza um algoritmo de busca em largura para reconhecer as palavras */
bool Interpretador::reconhecer(const std::string &palavra) {
    if (palavra.empty()) {
        std::cerr << "Palavra vazia." << std::endl;
        return false;
    }

    std::queue<std::pair<std::string, std::vector<std::string>>> fila; // pair<estado, caminho> estado e caminho até o estado atual
    std::unordered_set<std::string> visitados; // Para evitar estados repetidos
    fila.push(std::make_pair(std::string(1, gramatica.getSimboloInicial()), std::vector<std::string>()));

    std::cout << "Simbolo inicial: " << gramatica.getSimboloInicial() << std::endl;

    while (!fila.empty()) {
        std::pair<std::string, std::vector<std::string>> front = fila.front();
        std::string estado = front.first;
        std::vector<std::string> path = front.second;
        fila.pop();

        std::cout << "Estado atual: " << estado << std::endl;

        if (estado == palavra) {
            std::cout << "Palavra reconhecida." << std::endl;
            std::cout << "Caminho:\n";
            for (const auto &step : path) {
                std::cout << step << std::endl;
            }
            return true;
        }

        if (estado.size() > palavra.size() + 1) {
            continue;
        }

        for (size_t i = 0; i < estado.size(); ++i) {
            if (gramatica.getNaoTerminais().count(estado[i])) {
                char naoTerminal = estado[i];
                const auto& producoes = gramatica.getProducoes();

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
                                std::vector<std::string> novoPath = path;
                                novoPath.push_back("Aplicando producao: " + std::string(1, producao.naoTerminal) + " -> " + alternativa);
                                fila.push(std::make_pair(novoEstado, novoPath));
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
