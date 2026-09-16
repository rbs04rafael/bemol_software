#ifndef FLAUTA_TRANSVERSAL_H
#define FLAUTA_TRANSVERSAL_H

#include "Instrumento.h"

class FlautaTransversal : public Instrumento {
    public:
        void emitirSom(string nota, double tempo) override;
        string getNome() override; 
        vector<string> getNotas() override;
        int getMidiProgram() override;   
};

#endif