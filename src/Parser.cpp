#include "../include/Parser.h"
#include <fstream>
#include <sstream>
#include <iostream>

Parser::Parser(const std::string& nomeArquivo) : nomeArquivo(nomeArquivo) {}

bool Parser::parse() {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) return false;

    std::string linha;
    while (std::getline(arquivo, linha)) {
        std::istringstream iss(linha);
        char naoTerminal;
        std::string producao;
        if (!(iss >> naoTerminal >> producao)) {
            std::cerr << "Erro ao ler linha: " << linha << std::endl;
            return false;
        }
        if (!gramatica.adicionarProducao(naoTerminal, producao)) {
            std::cerr << "Produção inválida: " << producao << std::endl;
            return false;
        }
    }
    return gramatica.ehValida();
}

const Gramatica& Parser::obterGramatica() const {
    return gramatica;
}
