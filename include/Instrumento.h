#ifndef INSTRUMENTO_H
#define INSTRUMENTO_H

#include <string>
#include <vector>

using namespace std;

class Instrumento {
public:
    virtual ~Instrumento() = default;
    
    // Método virtual puro: obriga as classes filhas a implementarem
    virtual void emitirSom(string nota, double tempo) = 0;
    
    // Método virtual puro para retornar o nome do instrumento
    virtual string getNome() = 0;

    //Método virtual para retornar todas as notas do instrumento
    virtual vector<string> getNotas() = 0;

};

#endif