#ifndef INTERPRETADOR_H
#define INTERPRETADOR_H

#include "Gramatica.h"
#include <string>

class Interpretador {
public:
    Interpretador(const Gramatica& gramatica);
    bool reconhecer(const std::string& palavra);

private:
    const Gramatica& gramatica;
};

#endif // INTERPRETADOR_H
