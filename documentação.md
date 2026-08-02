# Documentação de Arquitetura - Software Musical (Módulo: Teste Seu Ouvido)

Este documento descreve a estrutura inicial, as classes e as decisões de engenharia de software adotadas no desenvolvimento do backend em C++ do módulo "Teste Seu Ouvido".

## 1. Estrutura de Diretórios

O projeto segue a padronização clássica do C++ para separar as interfaces públicas (contratos) das implementações privadas (lógica), garantindo abstração e otimização de compilação.

` ` `text
software_musical/
├── include/
│   ├── Instrumento.h       # Classe abstrata (Interface)
│   ├── SaxofoneAlto.h      # Declaração do instrumento específico
│   └── TesteOuvido.h       # Declaração das regras de negócio do teste
├── src/
│   ├── SaxofoneAlto.cpp    # Implementação da emissão de som
│   ├── TesteOuvido.cpp     # Implementação da geração de notas e validação
│   └── main.cpp            # Ponto de entrada e injeção de dependências
` ` `

## 2. Diagrama de Classes (UML)

A modelagem foi feita visando o baixo acoplamento e o uso de polimorfismo, permitindo que novos instrumentos sejam adicionados no futuro sem a necessidade de alterar a lógica do teste de ouvido.

` ` `mermaid
classDiagram
    class Instrumento {
        <<abstract>>
        +virtual ~Instrumento()
        +virtual emitirSom(string nota)* void
        +virtual getNome()* string
    }

    class SaxofoneAlto {
        +emitirSom(string nota) void
        +getNome() string
    }

    class TesteOuvido {
        -Instrumento* instrumentoAtual
        -int dificuldade
        -vector~string~ notasGeradas
        +TesteOuvido(Instrumento* inst, int dif)
        +gerarSequencia() void
        +reproduzirTeste() void
        +verificarResposta(vector~string~ resposta) bool
    }

    Instrumento <|-- SaxofoneAlto : Implementa
    TesteOuvido --> Instrumento : Agregação (Usa)
` ` `

## 3. Decisões de Projeto e Padrões Aplicados

Durante o desenvolvimento, tomamos decisões arquiteturais focadas nas boas práticas de **Engenharia de Software** e **Orientação a Objetos**:

### 3.1. Polimorfismo e Inversão de Dependência
* **Decisão:** A classe `TesteOuvido` recebe um ponteiro genérico `Instrumento*` em vez de um instrumento específico (como `SaxofoneAlto*`).
* **Justificativa:** O núcleo do sistema não precisa saber qual instrumento está tocando. Ele apenas comanda a ação `emitirSom()`. Isso permite escalar o software para dezenas de instrumentos no futuro sem modificar a classe principal.

### 3.2. Encapsulamento (Segurança Anti-Cheat)
* **Decisão:** O método `gerarSequencia()` não possui retorno (`void`) e a variável `notasGeradas` é estritamente privada (`private`).
* **Justificativa:** O estado da resposta correta pertence exclusivamente ao modelo (Model). Se a função retornasse a sequência, a interface gráfica (View) teria acesso prematuro à resposta, violando a responsabilidade única e permitindo possíveis fraudes no teste.

### 3.3. Uso de `std::vector` (C++ Moderno vs. C Clássico)
* **Decisão:** Utilização de `std::vector<std::string>` para armazenar as notas em vez de arrays estáticos (ex: `string notas[]`).
* **Justificativa:** O `std::vector` gerencia sua própria alocação de memória (RAII) e permite tamanho dinâmico. Isso evita *memory leaks*, *buffer overflows* e permite que a dificuldade do jogo (quantidade de notas) seja variável.

### 3.4. Validação por Índice (Lógica de Domínio Musical)
* **Decisão:** No método `verificarResposta()`, a comparação é feita varrendo os índices equivalentes dos vetores (ex: `resposta[i] != notasGeradas[i]`), abandonando funções de busca soltas como `std::find`.
* **Justificativa:** Em um teste de ouvido de sequências, a **ordem** das notas é tão importante quanto as notas em si. Comparar posição por posição garante a integridade da teoria musical aplicada ao software, além de possibilitar um *early return* (retorno rápido) caso a primeira nota já esteja errada, otimizando o processamento.

### 3.5. Listas de Inicialização em Construtores
* **Decisão:** O construtor de `TesteOuvido` utiliza a sintaxe de dois pontos (lista de inicialização) em vez de atribuir valores dentro do escopo `{}`.
* **Justificativa:** Em C++, inicializar as variáveis antes do corpo do construtor executar evita a criação temporária de objetos com valores padrão (lixo de memória), resultando em um código de maior performance, adequado para sistemas que processam mídia/áudio.

### 3.6. Responsabilidade Única
* **Decisão:** O método `verificarResposta()` retorna apenas um `bool` (verdadeiro ou falso) e não imprime mensagens no console.
* **Justificativa:** A classe de regras de negócio (Model) não deve ditar a forma como o usuário interage. A responsabilidade de exibir a mensagem de "Você acertou!" ou "Você errou!" será delegada futuramente ao Controlador/View, mantendo o código agnóstico em relação à interface (seja ela Terminal, Web ou Desktop).

## 4. Arquitetura de Comunicação (Backend API e Frontend Web)

Com a evolução do projeto e a necessidade futura de processamento de áudio de baixa latência, o sistema foi refatorado para operar como um **Servidor Local (API REST)**.

### 4.1. Integração com `cpp-httplib`
* **Decisão:** Utilização da biblioteca `cpp-httplib` para o servidor web.
* **Justificativa:** É uma biblioteca *header-only*, facilitando o setup educacional sem sacrificar a capacidade de gerenciar requisições multithread de uma interface Web.

### 4.2. Build System com CMake
* **Decisão:** Migração da compilação manual (`g++`) para o **CMake**.
* **Justificativa:** Permite gerenciar as dependências do projeto (como `Threads` para o servidor web) de forma modular, multiplataforma e escalável.

### 4.3. Quebra Intencional de Encapsulamento na Rota `/gerar_teste`
* **Decisão:** Exposição temporária do array de notas em formato `JSON`.
* **Justificativa:** Embora viole o encapsulamento do Model para o View (conforme item 3.2), essa abordagem foi tomada exclusivamente para validar a comunicação entre o C++ e a web. No futuro, o servidor deve gerar o arquivo de áudio ou um token em vez de enviar as notas em texto (para evitar fraudes por parte do usuário final).