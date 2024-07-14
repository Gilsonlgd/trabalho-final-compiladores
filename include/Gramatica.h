#ifndef GRAMATICA_H
#define GRAMATICA_H

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

class Gramatica {
public:
    struct Producao {
        char naoTerminal;
        std::vector<std::string> producoes;
    };

    Gramatica();

    bool addNaoTerminal(char naoTerminal);
    bool addTerminal(char terminal);
    void defSimboloInicial(char simboloInicial);

    bool addProducao(char naoTerminal, const std::vector<std::string>& producao);
    bool ehValida() const;

    const std::vector<Producao>& getProducoes() const;
    const std::unordered_set<char>& getNaoTerminais() const;
    const std::unordered_set<char>& getTerminais() const;
    char getSimboloInicial() const;
    
    void printErro() const;
    void setErro(const std::string& erro) const;

private:
    std::vector<Producao> producoes;
    std::unordered_map<char, std::vector<std::vector<std::string>>> mapaProducoes;
    std::string join(const std::vector<std::string>& v, char delim) const;
    std::unordered_set<char> naoTerminais;
    std::unordered_set<char> terminais;
    mutable std::string erro;

    char simboloInicial;
};

#endif // GRAMATICA_H
