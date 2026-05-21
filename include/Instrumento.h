#ifndef INSTRUMENTO_H
#define INSTRUMENTO_H

#include <string>

using namespace std;

class Instrumento {
public:
    virtual ~Instrumento() = default;
    
    // Método virtual puro: obriga as classes filhas a implementarem
    virtual void emitirSom(string nota) = 0;
    
    // Método virtual puro para retornar o nome do instrumento
    virtual string getNome() = 0;
};

#endif