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

        /* Verifica o formato da produção lida */
        if (!(issProducao >> naoTerminal >> seta >> producao) || seta != "->") {
            std::cerr << "Erro ao ler linha: " << linha << std::endl;
            return false;
        }


        
        if (!gramatica.addProducao(naoTerminal, split(producao, '|'))) {
            std::cout << "Erro de especificacao da gramatica." << std::endl;
            std::cout << "Producao invalida: " << naoTerminal << " -> " << producao << std::endl;
            gramatica.printErro();
            return false;
        }
    }

    if (!gramatica.ehValida()) {
        std::cout << "Erro de especificacao da gramatica." << std::endl;
        gramatica.printErro();
        return false;
    }

    return true;
}

const Gramatica& Parser::getGramatica() const {
    return gramatica;
}

std::vector<std::string> Parser::split(const std::string& s, char delim) const {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delim)) {
        tokens.push_back(token);
    }

    return tokens;
}