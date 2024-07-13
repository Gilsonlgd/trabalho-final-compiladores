#include "../include/Gramatica.h"

Gramatica::Gramatica() {}

bool Gramatica::adicionarProducao(char naoTerminal, const std::string& producao) {
    if (producao.empty()) return false;
    producoes.push_back({naoTerminal, producao});
    mapaProducoes[naoTerminal].push_back(producao);
    return true;
}

bool Gramatica::ehValida() const {
    for (const auto& prod : producoes) {
        if (!(prod.producao.size() == 1 || (prod.producao.size() == 2 && isupper(prod.producao[1])))) {
            return false;
        }
    }
    return true;
}

const std::vector<Gramatica::Producao>& Gramatica::obterProducoes() const {
    return producoes;
}
