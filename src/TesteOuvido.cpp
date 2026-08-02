#include "../include/TesteOuvido.h"
#include <iostream>

#include <vector>
#include <string>
#include "../include/Instrumento.h"

TesteOuvido::TesteOuvido(Instrumento* inst, int dif):
 instrumentoAtual(inst), dificuldade(dif) {

}

void TesteOuvido::gerarSequencia(){
    //limpa as notas da rodada anteriore
    notasGeradas.clear();
    
    //especifica as notas que podem ser sorteadas
    std::string notasPossiveis[] = {"C", "C#", "D", "D#",
         "E", "F", "F#", "G", "G#", "A", "A#", "B"};
    
    //sorteia as notas aleatoriamente
        for(int i = 0; i < dificuldade; i++){
        int indicieAleatorio = rand() % 12;
        notasGeradas.push_back(notasPossiveis[indicieAleatorio]);
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
    for(const string& nota : notasGeradas){
        instrumentoAtual->emitirSom(nota);
    }
}

std::vector<std::string> TesteOuvido::getNotasGeradas(){
    return notasGeradas;
}
