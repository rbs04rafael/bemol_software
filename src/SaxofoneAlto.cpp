#include "../include/SaxofoneAlto.h"
#include <iostream>
#include <vector>

void SaxofoneAlto::emitirSom(string nota, double tempo) {
    // Futuramente, esta função carregará o arquivo de áudio (.wav/.mp3) correspondente à nota.
    // Para testar a lógica inicial, usaremos a saída no console.
    cout << "Reproduzindo Saxofone Alto: " << nota << "com tempo" << tempo << endl;
}

string SaxofoneAlto::getNome() {
    return "Saxofone Alto";
}

vector<string> SaxofoneAlto::getNotas() {
    vector<string> notas = {
        "Bb3","B3", "C4", "C#4", "Db4", "D4", "D#4", "Eb4", "E4", "F4", "F#4", "Gb4",
        "G4", "G#4",  "Ab4", "A4", "A#4", "Bb4", "B4", "C5", "C#5", "Db5", "D5", "D#5",
        "Eb5", "E5", "F5", "F#5", "Gb5", "G5", "G#5", "Ab5", "A5","A#5", "Bb5", "B5",
         "C6", "C#6"     
    };
    //"Db6", "D6", "D#6", "Eb6", "E6", "F6", "F#6" notas removidas pq midi n suporta
    return notas;
}

int SaxofoneAlto::getMidiProgram(){
    return 65;
}

