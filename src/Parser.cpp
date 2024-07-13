#include "../include/Parser.h"
#include <fstream>
#include <sstream>
#include <iostream>

Parser::Parser(const std::string& nomeArquivo) : nomeArquivo(nomeArquivo) {}

bool Parser::parse() {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) return false;

    std::string linha;

    // Leitura da primeira linha: Símbolos não terminais
    if (!std::getline(arquivo, linha)) return false;
    std::istringstream issNaoTerminais(linha);
    char naoTerminal;
    while (issNaoTerminais >> naoTerminal) {
        gramatica.addNaoTerminal(naoTerminal);
    }

    // Leitura da segunda linha: Símbolos terminais
    if (!std::getline(arquivo, linha)) return false;
    std::istringstream issTerminais(linha);
    char terminal;
    while (issTerminais >> terminal) {
        gramatica.addTerminal(terminal);
    }

    // Leitura da terceira linha: Símbolo inicial
    if (!std::getline(arquivo, linha)) return false;
    std::istringstream issInicial(linha);
    char simboloInicial;
    if (!(issInicial >> simboloInicial)) return false;
    gramatica.defSimboloInicial(simboloInicial);

    // Leitura das produções
    while (std::getline(arquivo, linha)) {
        std::istringstream issProducao(linha);
        char naoTerminal;
        std::string seta, producao;
        if (!(issProducao >> naoTerminal >> seta >> producao) || seta != "->") {
            std::cerr << "Erro ao ler linha: " << linha << std::endl;
            return false;
        }
        if (!gramatica.addProducao(naoTerminal, producao)) {
            std::cerr << "Producao invalida: " << producao << std::endl;
            return false;
        }
    }

    return gramatica.ehValida();
}

const Gramatica& Parser::getGramatica() const {
    return gramatica;
}
