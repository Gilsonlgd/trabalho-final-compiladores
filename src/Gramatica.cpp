#include "../include/Gramatica.h"
#include <cctype>

Gramatica::Gramatica() : simboloInicial('\0') {}

bool Gramatica::addNaoTerminal(char naoTerminal) {
    if (isupper(naoTerminal)) {
        naoTerminais.insert(naoTerminal);
        return true;
    }
    return false;
}

bool Gramatica::addTerminal(char terminal) {
    if (islower(terminal)) {
        terminais.insert(terminal);
        return true;
    }
    return false;
}

void Gramatica::defSimboloInicial(char simboloInicial) {
    this->simboloInicial = simboloInicial;
}

bool Gramatica::addProducao(char naoTerminal, const std::string& producao) {
    if (naoTerminais.find(naoTerminal) == naoTerminais.end() || producao.empty()) {
        return false;
    }
    producoes.push_back({naoTerminal, producao});
    mapaProducoes[naoTerminal].push_back(producao);
    return true;
}

bool Gramatica::ehValida() const {
    // Verifica se o símbolo inicial é um não terminal válido
    if (naoTerminais.find(simboloInicial) == naoTerminais.end()) {
        return false;
    }

    // Verifica se todas as produções estão corretas
    for (const auto& prod : producoes) {
        if (!(prod.producao.size() == 1 || (prod.producao.size() == 2 && isupper(prod.producao[1])))) {
            return false;
        }
        for (char ch : prod.producao) {
            if (!(naoTerminais.count(ch) || terminais.count(ch))) {
                return false;
            }
        }
    }
    return true;
}

const std::vector<Gramatica::Producao>& Gramatica::getProducoes() const {
    return producoes;
}

const std::unordered_set<char>& Gramatica::getNaoTerminais() const {
    return naoTerminais;
}

const std::unordered_set<char>& Gramatica::getTerminais() const {
    return terminais;
}

char Gramatica::getSimboloInicial() const {
    return simboloInicial;
}
