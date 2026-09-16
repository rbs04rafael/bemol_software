#ifndef SAXOFONE_ALTO_H
#define SAXOFONE_ALTO_H

#include "Instrumento.h"

class SaxofoneAlto : public Instrumento {
    public:
        void emitirSom(string nota, double tempo) override;
        string getNome() override; 
        vector<string> getNotas() override;
        int getMidiProgram() override;
};

#endif