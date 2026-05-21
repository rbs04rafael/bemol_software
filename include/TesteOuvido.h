#ifndef TESTE_OUVIDO_H
#define TESTE_OUVIDO_H

#include <vector>
#include <string>
#include "Instrumento.h"

class TesteOuvido {
    private:
        Instrumento* instrumentoAtual;
        std::vector<std::string> notasGeradas;
        int dificuldade = 0;    
    public:
        TesteOuvido(Instrumento* inst, int dif);
        void gerarSequencia();
        void reproduzirTeste();
        bool verificarResposta(std::vector<std::string> resposta);       
};
#endif
