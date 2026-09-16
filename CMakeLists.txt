cmake_minimum_required(VERSION 3.10)

project(BemolSoftware)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(
    teste_ouvido
    src/main.cpp
    src/SaxofoneAlto.cpp
    src/FlautaTransversal.cpp
    src/Trombone.cpp
    src/InstrumentoFactory.cpp
    src/TesteOuvido.cpp
    src/Sintetizador.cpp
)

find_package(Threads REQUIRED)
target_link_libraries(teste_ouvido PRIVATE Threads::Threads fluidsynth)
