#ifndef INSTRUMENTO_FACTORY_H
#define INSTRUMENTO_FACTORY_H

#include <string>
#include "Instrumento.h"

class InstrumentoFactory {
    public:
        static Instrumento* criar(std::string nome);
    };

#endif