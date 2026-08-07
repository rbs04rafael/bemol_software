#include "../include/SaxofoneAlto.h"
#include "../include/TesteOuvido.h"
#include "../include/Instrumento.h"
#include "../include/httplib.h"
#include "../include/json.hpp" 
using json = nlohmann::json;
#include <iostream>
#include <cstdlib>
#include <ctime>

int main(){
    srand(time(NULL));
    SaxofoneAlto sax = SaxofoneAlto();
    TesteOuvido teste = TesteOuvido(&sax,5);

    //instancia o servidor
    httplib::Server servidor;


    servidor.Get("/gerar_teste", [&teste](const httplib::Request& req, 
        httplib::Response& res){
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

    servidor.Post("/verificar_resposta", [&teste](const httplib::Request& req, httplib::Response& res){
        std::string notas_recebidas = req.body;

        //transforma a resposta, que é uma string, em um "json"
        json objeto_json = json::parse(notas_recebidas);

        /*pego apenas as notas da resposta do usuario em formato de json
        e transoformo para o formato de vector de string*/
        std::vector<std::string> resposta_usuario = objeto_json["resposta"].get<std::vector<std::string>>();

        bool resultado = teste.verificarResposta(resposta_usuario);

        //transformo o resultado em formato json
        json resultado_json;
        if(resultado == true){
            resultado_json["resultado"] = "Você acertou!";
            resultado_json["pontos"] = "10";
        }
        else{
            resultado_json["resultado"] = "Você errou :(";
            resultado_json["pontos"] = "0";
        }

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
