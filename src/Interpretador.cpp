#include "../include/Interpretador.h"
#include <iostream>
#include <string>

Interpretador::Interpretador(const Gramatica& gramatica) : gramatica(gramatica) {}

bool Interpretador::reconhecer(const std::string& palavra) {
    std::string atual = std::string(1, gramatica.getSimboloInicial());
    for (char ch : palavra) {
        bool casou = false;
        for (const auto& prod : gramatica.getProducoes()) {
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
