#include "../include/Interpretador.h"
#include <iostream>

Interpretador::Interpretador(const Gramatica& gramatica) : gramatica(gramatica) {}

bool Interpretador::reconhecer(const std::string& palavra) {
    std::string atual = "S";  // Assumindo que 'S' é o símbolo inicial
    for (char ch : palavra) {
        bool casou = false;
        for (const auto& prod : gramatica.obterProducoes()) {
            if (prod.naoTerminal == atual.back() && prod.producao.front() == ch) {
                atual.pop_back();
                atual += prod.producao.substr(1);
                casou = true;
                break;
            }
        }
        if (!casou) {
            std::cerr << "Erro na posicao: " << &ch - &palavra[0] << std::endl;
            return false;
        }
    }
    return atual == "ε" || atual.empty();  // 'ε' representa produção vazia
}
