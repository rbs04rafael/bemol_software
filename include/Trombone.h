#ifndef TROMBONE_H
#define TROMBONE_H

#include "Instrumento.h"

class Trombone: public Instrumento {
    public: 
        void emitirSom(string nota, double tempo) override;
        string getNome() override;
        vector<string> getNotas() override;
        int getMidiProgram() override;
};

#endif