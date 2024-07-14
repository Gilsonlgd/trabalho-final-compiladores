#include "../include/Interpretador.h"
#include <iostream>
#include <iterator> // Para std::prev
#include <string>
#include <queue>
#include <unordered_set>

Interpretador::Interpretador(const Gramatica &gramatica)
    : gramatica(gramatica) {}

bool Interpretador::reconhecer(const std::string &palavra) {
   // Verifica se a palavra está vazia
    if (palavra.empty()) {
        return false;
    }

    // Inicializa a fila de estados
    std::queue<std::string> fila;
    fila.push(std::string(1, gramatica.getSimboloInicial()));

    while (!fila.empty()) {
        std::string estado = fila.front();
        fila.pop();

        // Se o estado é igual à palavra, a palavra é reconhecida
        if (estado == palavra) {
            return true;
        }

        // Se o estado é mais longo que a palavra, não é necessário continuar
        if (estado.size() > palavra.size()) {
            continue;
        }

        // Expande os estados atuais
        for (size_t i = 0; i < estado.size(); ++i) {
            if (gramatica.getNaoTerminais().count(estado[i])) {
                char naoTerminal = estado[i];
                const auto& producoes = gramatica.getProducoes();

                // Verifica produções para o não terminal atual
                for (const auto& producao : producoes) {
                    if (producao.naoTerminal == naoTerminal) {
                        for (const auto& alternativa : producao.producoes) {
                            std::string novoEstado = estado.substr(0, i) + alternativa + estado.substr(i + 1);
                            if (novoEstado.length() <= palavra.length()) {
                                fila.push(novoEstado);
                            }
                        }
                    }
                }
            }
        }
    }

    return false;
}
