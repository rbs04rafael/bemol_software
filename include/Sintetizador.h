#ifndef SINTETIZADOR_H
#define SINTETIZADOR_H
#include <string>
#include "Instrumento.h"

class Sintetizador {
    public:
    static void gerarAudio(std::vector<std::string> notas, Instrumento *inst, double tempo);
    static int notaParaMidi(std::string notaStr);
};

#endif