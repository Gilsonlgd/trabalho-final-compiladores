#include "../include/Interpretador.h"
#include <iostream>
#include <iterator> // Para std::prev
#include <string>

Interpretador::Interpretador(const Gramatica &gramatica)
    : gramatica(gramatica) {}

bool Interpretador::reconhecer(const std::string &palavra) {
  std::string atual = std::string(1, gramatica.getSimboloInicial());
  std::cout << "Simbolo inicial: " << atual << std::endl;

  size_t pos = 0;
  while (pos < palavra.length()) {
    std::cout << "Posicao: " << pos << ", Simbolo atual: " << atual
              << std::endl;
    bool casou = false;
    for (const auto &prods : gramatica.getProducoes()) {
      if (prods.naoTerminal == atual.back()) {
        int countProds = 0;
        for (const auto &prod : prods.producoes) {
          countProds++;
          std::string terminais = prod.substr(0, prod.length() - 1);
          char proximoSimbolo = prod.back();

          if (palavra.substr(pos, terminais.length()) == terminais) {
            std::cout << "Producao: " << prods.naoTerminal << " -> " << prod
                      << std::endl;
            atual.pop_back();
            if (proximoSimbolo != '#') { // '#' representa produção vazia
              if (gramatica.getTerminais().count(proximoSimbolo)) {
                if (palavra[pos] == proximoSimbolo) {
                  pos++;
                } else if (countProds == prods.producoes.size()) {
                  std::cerr << "Erro na posicao: " << pos << std::endl;
                  return false;
                }
              } else {
                atual += proximoSimbolo;
              }
            }
            pos += terminais.length();
            casou = true;
            break; // Quebra o loop interno de produções
          }
        }
        if (casou) {
          break; // Quebra o loop externo de não terminais
        }
      }
    }
    if (!casou) {
      std::cerr << "Erro na posicao: " << pos << std::endl;
      return false;
    }
  }
  return atual.empty(); // Verifique se a pilha está vazia no final
}
