#include "../include/SaxofoneAlto.h"
#include <iostream>

void SaxofoneAlto::emitirSom(string nota) {
    // Futuramente, esta função carregará o arquivo de áudio (.wav/.mp3) correspondente à nota.
    // Para testar a lógica inicial, usaremos a saída no console.
    cout << "Reproduzindo Saxofone Alto: " << nota << endl;
}

string SaxofoneAlto::getNome() {
    return "Saxofone Alto";
}

