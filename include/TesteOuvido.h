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
        int pontuacaoTotal = 0;
        int comboAtual = 0;
    public:
        struct ErroDeNota {
            std::string enviada;
            std::string esperada;
            int posicao;
        };
        TesteOuvido(Instrumento* inst, int dif);
        void gerarSequencia();
        void reproduzirTeste();
        void setInstrumento(Instrumento* novoInstrumento);
        void setDificuldade(int novaDificuldade);
        int processarPontuacao(int quantidade_erros);
        int getPontuacaoTotal();
        int getComboAtual();
        std::vector<ErroDeNota> verificarResposta(std::vector<std::string> resposta);
        std::vector<string> gerarAjuda();   
        std::vector<std::string> getNotasGeradas();
        
};
#endif
