#include "../include/Sintetizador.h"
#include "../include/Instrumento.h"
#include <fluidsynth.h>
#include <iostream>


void Sintetizador::gerarAudio(std::vector<std::string> notas, Instrumento *inst, double tempo)
{
    //Cria as configurações
    fluid_settings_t *configuracoes = new_fluid_settings();
    fluid_settings_setstr(configuracoes, "audio.file.name", "audio.wav"); // Nome do arquivo de saída

    //Cria o sintetizador
    fluid_synth_t *synth = new_fluid_synth(configuracoes);

    //Carrega o Banco de Sons
    fluid_synth_sfload(synth, "/usr/share/sounds/sf2/FluidR3_GM.sf2", 1);

    //Seleciona o Instrumento
    fluid_synth_program_change(synth, 0, inst->getMidiProgram());

    //Cria o Gravador 
    fluid_file_renderer_t *gravador = new_fluid_file_renderer(synth);

    std::cout<< "notas: ";

    for(std::string n : notas){
        std::cout << n << " ";
    }

    std::cout << "---------------------------" << std::endl;

    for(std::string notaStr : notas){
        std::cout << "notaStr: " << notaStr << std::endl;
        int notaMidi = notaParaMidi(notaStr);
        std::cout << "notaMidi: " << notaMidi << std::endl;

        fluid_synth_noteon(synth, 0, notaMidi, 100);

        for(double i = 0.0; i < 600*tempo; i = i + 1.0){
            fluid_file_renderer_process_block(gravador);    
        }

        fluid_synth_noteoff(synth, 0, notaMidi);

        for (int i = 0; i < 40; i++) {
            fluid_file_renderer_process_block(gravador);
        }

    }

    //esmaecer
    for (int i = 0; i < 150; i++)
    {
        fluid_file_renderer_process_block(gravador);
    }

    delete_fluid_file_renderer(gravador);
    delete_fluid_synth(synth);
    delete_fluid_settings(configuracoes);
    std::cout << "Fim da formacao de audio" << std::endl;
}

int Sintetizador::notaParaMidi(std::string notaStr){
    int base = 0;
    int oitava = 0;
    int alteracao = 0;
    char letra = notaStr[0];

    switch (letra){
        case 'C' : base = 0; break;
        case 'D': base = 2; break;
        case 'E': base = 4; break;
        case 'F': base = 5; break;
        case 'G': base = 7; break;
        case 'A': base = 9; break;
        case 'B': base = 11; break;
        default: base = 0; break;
    } 
    
    if(notaStr.length() == 3){
        char acidente = notaStr[1];
        if(acidente == '#'){
            alteracao = 1;
        }
        else{
            alteracao = -1;
        }

        oitava = notaStr[2] - '0';
    }
    else{
        oitava = notaStr[1] - '0';
    }

    return (oitava + 1)*12 + base + alteracao;

}