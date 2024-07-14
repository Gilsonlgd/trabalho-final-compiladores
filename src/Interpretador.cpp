#include "../include/Interpretador.h"
#include <iostream>
#include <string>

Interpretador::Interpretador(const Gramatica& gramatica) : gramatica(gramatica) {}

bool Interpretador::reconhecer(const std::string& palavra) {
    std::string atual = std::string(1, gramatica.getSimboloInicial());
    std::cout << "Simbolo inicial: " << atual << std::endl;

    size_t pos = 0;
    while (pos < palavra.length()) {
        std::cout << "Posicao: " << pos << ", Simbolo atual: " << atual << std::endl;
        bool casou = false;
        for (const auto& prod : gramatica.getProducoes()) {
            if (prod.naoTerminal == atual.back()) {
                std::string terminais = prod.producao.substr(0, prod.producao.length() - 1);
                char proximoSimbolo = prod.producao.back();

                if (palavra.substr(pos, terminais.length()) == terminais) {
                    std::cout << "Producao: " << prod.naoTerminal << " -> " << prod.producao << std::endl;
                    atual.pop_back();
                    if (proximoSimbolo != '#') {  // '#' representa produção vazia
                        if (gramatica.getTerminais().count(proximoSimbolo)) {
                            if (palavra[pos] == proximoSimbolo) {
                                pos++;
                            } else {
                                std::cerr << "Erro na posicao: " << pos << std::endl;
                                return false;
                            }
                        } else {
                            atual += proximoSimbolo;
                        }
                    }
                    pos += terminais.length();
                    casou = true;
                    break;
                }
            }
        }
        if (!casou) {
            std::cerr << "Erro na posicao: " << pos << std::endl;
            return false;
        }
    }
    return atual.empty();  // Verifique se a pilha está vazia no final
}
