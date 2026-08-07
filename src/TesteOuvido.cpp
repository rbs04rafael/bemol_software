#include "../include/TesteOuvido.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "../include/Instrumento.h"

TesteOuvido::TesteOuvido(Instrumento* inst, int dif):
    instrumentoAtual(inst), dificuldade(dif) {
    
        /*gero um vetor para saber quais notas foram geradas em O(1)
        quando for pedir ajuda*/
        notaFoiGerada.assign(instrumentoAtual->getNotas().size(), false);
}

void TesteOuvido::gerarSequencia(){
    //limpa as notas da rodada anteriore
    notasGeradas.clear();
    teveAjuda = false;
    std::fill(notaFoiGerada.begin(), notaFoiGerada.end(), false);
    reproducao = 0;

    //especifica as notas que podem ser sorteadas
    vector<string> notasPossiveis = instrumentoAtual->getNotas();
    
    //sorteia as notas aleatoriamente
    for(int i = 0; i < dificuldade; i++){
        int indicieAleatorio = rand() % notasPossiveis.size();
        notasGeradas.push_back(notasPossiveis[indicieAleatorio]);        
        notaFoiGerada[indicieAleatorio] = true;
    }
}

bool TesteOuvido::verificarResposta(std::vector<std::string> resposta) {
    //verifica se a quantidade de notas é correta
    if (resposta.size() != dificuldade){
        return false;
    }

    for(int i = 0; i < resposta.size(); i++){
        if(notasGeradas[i] != resposta[i]){
            return false;
        }
    }
    return true;
}

void TesteOuvido::reproduzirTeste(){
    /*reproduz as notas geradas de acordo com o instrumento
    selecionado*/
    double tempo = 0.0;
    /*limita a quantidade de vez que o usuário pode ouvir
    uma rodada*/

    switch(dificuldade){
        case 1:
            tempo = 2.0;
            break;
        case 2: 
            tempo = 1.0;
            break;
        case 3:
            tempo = 0.5;
            break;
    }
    
    if(reproducao < 3){
        for(const string& nota : notasGeradas){
            instrumentoAtual->emitirSom(nota, tempo);
        }
        reproducao++;
    }
}

std::vector<string> TesteOuvido::gerarAjuda(){
    if(teveAjuda == false){
        teveAjuda = true;
        std::vector<string> notasPossiveis = instrumentoAtual->getNotas();
        std::vector<string> notasFinais;

        for(int i = 0; i < (notasPossiveis.size()/2) ; i++){
            int indicieAleatorio = rand() % notasPossiveis.size();        
            if(notaFoiGerada[indicieAleatorio] == false){
                notasFinais.push_back(notasPossiveis[indicieAleatorio]);
                notaFoiGerada[indicieAleatorio] = true;
            }
            else{
                i--;
            }
        }

        notasFinais.insert(notasFinais.end(), notasGeradas.begin(), notasGeradas.end());

        return notasFinais;
    }
}

std::vector<std::string> TesteOuvido::getNotasGeradas(){
    return notasGeradas;
}
