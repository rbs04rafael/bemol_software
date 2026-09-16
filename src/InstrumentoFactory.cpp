#include "../include/InstrumentoFactory.h"
#include "../include/SaxofoneAlto.h"
#include "../include/FlautaTransversal.h"
#include "../include/Trombone.h"
#include <stdexcept>

Instrumento* InstrumentoFactory::criar(std::string nome){
    if (nome == "flauta_transversal"){
        return new FlautaTransversal();
    }
    else if(nome == "saxofone_alto"){
        return new SaxofoneAlto();
    }
    else if(nome == "trombone"){
        return new Trombone();
    }

    throw std::invalid_argument("Instrumento '" + nome + "' não é suportado ou não existe!");
}