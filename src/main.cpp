#include "../include/SaxofoneAlto.h"
#include "../include/TesteOuvido.h"
#include "../include/Instrumento.h"
#include "../include/InstrumentoFactory.h"
#include "../include/httplib.h"
#include "../include/json.hpp"
#include "../include/Sintetizador.h" 
using json = nlohmann::json;
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fluidsynth.h>

int main(){
    srand(time(NULL));
    Instrumento* sax_inicial = new SaxofoneAlto();
    TesteOuvido teste = TesteOuvido(sax_inicial,5);

    //instancia o servidor
    httplib::Server servidor;


    servidor.Post("/configurar_teste", [&teste](const httplib::Request& req, httplib::Response& res){
        try{
            json config_recebida = json::parse(req.body);
            std::string inst_escolhido = config_recebida["instrumento"];
        
            Instrumento* inst_novo = InstrumentoFactory::criar(inst_escolhido);
            teste.setInstrumento(inst_novo);
            teste.setDificuldade(config_recebida["dificuldade"]);

            json aviso;
            aviso["mensagem"] = "Configurações realizadas com sucesso!";

            res.set_header("Acess-Control-Allow-Origin", "*");            
            res.set_content(aviso.dump(), "Application/json");

        }
        catch(const std::invalid_argument erro){
            json erro_json;
            erro_json["erro"] = erro.what();

            res.set_header("Acess-Control-Allow-Origin", "*");            
            res.set_content(erro_json.dump(), "Application/json");
            res.status = 400;
        }
    });

    servidor.Get("/gerar_teste", [&teste](const httplib::Request& req, httplib::Response& res){
        teste.gerarSequencia();
        std::vector<std::string> notas = teste.getNotasGeradas();

        std::string json = "{\n \"notas\": [\n";
        for(size_t i = 0; i < notas.size(); i++){
            json += "   \"" + notas[i] + "\"";
            if(i < notas.size() - 1) json += ",\n";
            else json += "\n";
        }
        json += "   ]\n}";

        // 3. CORS: Regra de segurança fundamental da web! avisa o navegador
        // que qualquer interface gráfica (Frontend) tem permissão para ler essa resposta.
        res.set_header("Acess-Control-Allow-Origin", "*");

        //responde enviando a string 'json' e avisando q o tipo é "application/json"
        res.set_content(json, "application/json");

        std::cout << "Sequencia gerada e enviada para o front" << endl;
    });

    servidor.Get("/reproduzir_teste", [&teste](const httplib::Request& req, httplib::Response& res){
        teste.reproduzirTeste();

        std::ifstream arquivo("audio.wav", std::ios::binary);

        if(arquivo){
            std::string conteudo((std::istreambuf_iterator<char>(arquivo)), std::istreambuf_iterator<char>());
        
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_header("Cache-Control", "no-store, no-cache, must-revalidate, max-age=0");
            res.set_content(conteudo, "audio/wav");
        }
        else{
            res.status = 500;
            res.set_content("Erro ao ler arquivo de audio", "text/plain");
        }
    });

    servidor.Get("/pedir_ajuda", [&teste](const httplib::Request& req, httplib::Response& res){
        try{
            std::vector<std::string> resultado_ajuda = teste.gerarAjuda();

            json ajuda_json;

            ajuda_json["resultado_ajuda"] = resultado_ajuda; 

            std::string texto_final = ajuda_json.dump();

            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_content(texto_final, "application/json");
        }
        catch(const std::runtime_error& erro){
            json erro_json;
            erro_json["erro"] = erro.what(); //pega a mensagem de erro do throw

            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_content(erro_json.dump(), "application/json");
            res.status = 400;
        }

    });

    servidor.Post("/verificar_resposta", [&teste](const httplib::Request& req, httplib::Response& res){
        std::string req_body = req.body;

        //transforma a resposta, que é uma string, em um "json"
        json objeto_json = json::parse(req_body);

        /*pego apenas as notas da resposta do usuario em formato de json
        e transoformo para o formato de vector de string*/
        std::vector<std::string> notas_recebidas = objeto_json["resposta"].get<std::vector<std::string>>();

        std::vector<TesteOuvido::ErroDeNota> resultado = teste.verificarResposta(notas_recebidas);

        //transformo o resultado em formato json
        json resultado_json;
        json array_de_erros = json::array();

        int pontosGanhos = teste.processarPontuacao(resultado.size());

        if(resultado.size() == 0){
            resultado_json["resultado"] = "Você acertou tudo!! Parabéns!!";
        }
        else{
            resultado_json["resultado"] = "Você se enganou um pouco, mas não desanime!";
        }

        for(int i = 0; i < resultado.size(); i++){
            json erro_atual;
            erro_atual["enviada"] = resultado[i].enviada;
            erro_atual["esperada"] = resultado[i].esperada;
            erro_atual["posicao"] = resultado[i].posicao;
            array_de_erros.push_back(erro_atual);
        }

        resultado_json["detalhes_erro"] = array_de_erros;
        resultado_json["pontos_ganhos_rodada"] = pontosGanhos;
        resultado_json["pontuacao_total"] = teste.getPontuacaoTotal();
        resultado_json["combo_atual"] = teste.getComboAtual();
        //transformo o resultado_json em string para eviar ao front-end
        std::string resultado_texto = resultado_json.dump();
        
        res.set_header("Access-Control-Allow-Origin","*");
        res.set_content(resultado_texto, "application/json");
    });

    std::cout << "Servidor na porta 8080. Acesse: localhost:8080/ping" << std::endl;
    
    //trava o programa, matem servidor ouvindo os acessos
    servidor.listen("0.0.0.0", 8080);

    return 0;
}
