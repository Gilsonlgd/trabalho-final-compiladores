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

bool Gramatica::addProducao(char naoTerminal, const std::string &producao) {
  if (naoTerminais.find(naoTerminal) == naoTerminais.end()) {
    std::string erro = "Nao terminal invalido: ";
    erro += naoTerminal;
    setErro(erro);
    return false;
  }

  if (producao.empty()) {
    std::string erro = "Producao vazia para o nao terminal: ";
    erro += naoTerminal;
    setErro(erro);
    return false;
  }

  producoes.push_back({naoTerminal, producao});
  mapaProducoes[naoTerminal].push_back(producao);
  return true;
}

bool Gramatica::ehValida() const {
  // Verifica se o símbolo inicial é um não terminal válido
  if (naoTerminais.find(simboloInicial) == naoTerminais.end()) {
    std::string erro = "Simbolo inicial invalido: ";
    erro += simboloInicial;
    setErro(erro);
    return false;
  }

  // Verifica se todas as produções estão corretas
  for (const auto &prod : producoes) {
    if (prod.producao.size() < 1) {
      std::string erro = "Produção vazia: ";
      erro += prod.naoTerminal;
      erro += " -> " + prod.producao;
      setErro(erro);
      return false;
    }

    if (prod.producao.size() == 2 && !isupper(prod.producao[1])) {
      std::string erro = "Esta gramatica nao eh uma GLD: ";
      erro += prod.naoTerminal;
      erro += " -> " + prod.producao;
      setErro(erro);
      return false;
    }

    for (char ch : prod.producao) {
      if (!naoTerminais.count(ch) && !terminais.count(ch)) {
        std::string erro = "Simbolo invalido: ";
        erro += ch;
        setErro(erro);
        return false;
      }
    }
  }
  return true;
}

void Gramatica::setErro(const std::string &erro) const { this->erro = erro; }

void Gramatica::printErro() const { std::cerr << erro << std::endl; }

const std::vector<Gramatica::Producao> &Gramatica::getProducoes() const {
  return producoes;
}

const std::unordered_set<char> &Gramatica::getNaoTerminais() const {
  return naoTerminais;
}

const std::unordered_set<char> &Gramatica::getTerminais() const {
  return terminais;
}

char Gramatica::getSimboloInicial() const { return simboloInicial; }
