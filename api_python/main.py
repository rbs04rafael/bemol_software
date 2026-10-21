from fastapi import FastAPI, HTTPException, Response
from pydantic import BaseModel
import httpx

app = FastAPI(
    title="Bemol Software API",
    description="O gerente feral do sistema bemol software",
    version="1.0.0"
)

@app.get("/")
def pagina_inicial():
    return {
        "status": "online",
        "mensagem": "Olá, Rafael! O gerente do bemo software está no ar." 
    }

class ConfiguracaoTeste(BaseModel):
    instrumento: str = "saxofone_alto"
    dificuldade: int = 3

@app.post("/configurar_teste")
def configurar_teste(config: ConfiguracaoTeste):
    try:
        resposta_cpp = httpx.post(
            "http://localhost:8080/configurar_teste",
            json=config.model_dump())
    except httpx.RequestError: #para quando o servidor c++ está desligado
        raise HTTPException(
            status_code=503,
            detail="O motor de áudio c++ está offline no momento."
        )
    if resposta_cpp.status_code != 200: #para quando os parâmetros do usuário para o c++ estão errados
        raise HTTPException(
            status_code=resposta_cpp.status_code,
            detail=resposta_cpp.json()
        )
    return resposta_cpp.json()

class Resposta(BaseModel):
    resposta: list[str] = ["A", "B", "C"] 

@app.post("/verificar_resposta")
def verificar_resposta(resp: Resposta):
    try:
        resposta_cpp=httpx.post(
            "http://localhost:8080/verificar_resposta",
            json=resp.model_dump())
    except httpx.RequestError:
        raise HTTPException(
            status_code=503,
            detail="O motor de áudio c++ está offline no momento."
        )
    return resposta_cpp.json()

@app.get("/gerar_teste")
def gerar_teste():
    try:
        resposta_cpp=httpx.get("http://localhost:8080/gerar_teste")
    except httpx.RequestError:
        raise HTTPException(
            status_code=503,
            detail="O motor de áudio c++ está offline no momento."
        )
    return resposta_cpp.json()

@app.get("/pedir_ajuda")
def pedir_ajuda():
    try:
        resposta_cpp=httpx.get("http://localhost:8080/pedir_ajuda")
    except httpx.RequestError:
        raise HTTPException(
            status_code=503,
            detail="O motor de áudio c++ está offline no momento."
        )
    if resposta_cpp.status_code != 200: #para quando as ajudas tiverem acabado
        raise HTTPException(
            status_code=resposta_cpp.status_code,
            detail=resposta_cpp.json()
        )
    return resposta_cpp.json()

@app.get("/reproduzir_teste")
def reproduzir_teste():
    try:
        resposta_cpp=httpx.get("http://localhost:8080/reproduzir_teste")
    except httpx.RequestError:
        raise HTTPException(
            status_code=503,
            detail="O motor de áudio c++ está offline no momento."
        )
    return Response(
        content=resposta_cpp.content,
        media_type="audio/wav",
        headers={"Cache-Control": "no-store, no-cache, must-revalidate, max-age=0"}
    )