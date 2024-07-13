#ifndef PARSER_H
#define PARSER_H

#include "Gramatica.h"
#include <string>

class Parser {
public:
    Parser(const std::string& nomeArquivo);
    bool parse();
    const Gramatica& getGramatica() const;

private:
    std::string nomeArquivo;
    Gramatica gramatica;
};

#endif // PARSER_H
