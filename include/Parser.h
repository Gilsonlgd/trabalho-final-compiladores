#ifndef PARSER_H
#define PARSER_H

#include "Gramatica.h"
#include <string>
#include <sstream>
#include <vector>

class Parser {
public:
    Parser(const std::string& nomeArquivo);
    bool parse();
    const Gramatica& getGramatica() const;

private:
    std::string nomeArquivo;
    Gramatica gramatica;
    std::vector<std::string> split(const std::string& s, char delim) const;
};

#endif // PARSER_H
