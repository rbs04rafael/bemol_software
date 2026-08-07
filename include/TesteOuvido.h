#ifndef TESTE_OUVIDO_H
#define TESTE_OUVIDO_H

#include <vector>
#include <string>
#include "Instrumento.h"

class TesteOuvido {
    private:
        Instrumento* instrumentoAtual;
        std::vector<std::string> notasGeradas;
        std::vector<bool> notaFoiGerada;
        int dificuldade = 0; 
        int reproducao = 0; 
        bool teveAjuda = false;  
    public:
        TesteOuvido(Instrumento* inst, int dif);
        void gerarSequencia();
        void reproduzirTeste();
        bool verificarResposta(std::vector<std::string> resposta);
        std::vector<string> gerarAjuda();   
        std::vector<std::string> getNotasGeradas();
        
};
#endif
