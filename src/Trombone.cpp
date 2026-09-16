#include "../include/Trombone.h"
#include <iostream>
#include <vector>

void Trombone::emitirSom(string nota, double tempo) {
    // Futuramente, esta função carregará o arquivo de áudio (.wav/.mp3) correspondente à nota.
    // Para testar a lógica inicial, usaremos a saída no console.
    cout << "Reproduzindo Trombone: " << nota << "com tempo" << tempo << endl;
}

string Trombone::getNome() {
    return "Flauta trombone";
}

vector<string> Trombone::getNotas() {
    vector<string> notas = {
        // Oitava 2 (Grave)
            "E2", "F2", "F#2", "Gb2", "G2", "G#2", "Ab2", "A2", "A#2", "Bb2", "B2",

            // Oitava 3 (Média)
            "C3", "C#3", "Db3", "D3", "D#3", "Eb3", "E3", "F3", "F#3", "Gb3",
            "G3", "G#3", "Ab3", "A3", "A#3", "Bb3", "B3",

            // Oitava 4 (Aguda)
            "C4", "C#4", "Db4", "D4", "D#4", "Eb4", "E4", "F4", "F#4", "Gb4",
            "G4", "G#4", "Ab4", "A4", "A#4", "Bb4"     
    };
    return notas;
}

int Trombone::getMidiProgram(){
    return 57;
}
