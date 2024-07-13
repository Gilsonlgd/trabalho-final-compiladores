#ifndef GRAMATICA_H
#define GRAMATICA_H

#include <string>
#include <vector>
#include <unordered_map>

class Gramatica {
public:
    struct Producao {
        char naoTerminal;
        std::string producao;
    };

    Gramatica();
    bool adicionarProducao(char naoTerminal, const std::string& producao);
    bool ehValida() const;
    const std::vector<Producao>& obterProducoes() const;

private:
    std::vector<Producao> producoes;
    std::unordered_map<char, std::vector<std::string>> mapaProducoes;
};

#endif // GRAMATICA_H
