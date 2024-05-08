//PROYECTO DE ALGORITMOS Y ESTRUCTURAS DE DATOS 
//MADE BY: RICARDO MEJIA & EDUARDO ROJAS

#include <iostream>
using namespace std;

//Declaración de Estructuras

struct Recursos{
    int id;
    string nombre;
    Recursos *prox;
};

struct Jugadores{
    int pts;
    string nombre;
    Recursos *Inventario;
    Jugadores *prox;
};

struct Casillas{
    int id;
    string bioma;
    Recursos *RLista;
    Jugadores *Jlista;
    Casillas *prox;
};

Recursos *CrearRecurso(int id, string nombre){
    Recursos *NuevoRecurso= new Recursos;
    NuevoRecurso->id=id;
    NuevoRecurso->nombre=nombre;
    NuevoRecurso->prox=NULL;
    return NuevoRecurso;
}

Jugadores *CrearJugador(string nombre){
    Jugadores *NuevoJugador= new Jugadores;
    NuevoJugador->pts=0;
    NuevoJugador->nombre=nombre;
    NuevoJugador->Inventario=NULL;
    NuevoJugador->prox=NULL;
    return NuevoJugador;
}

//CONTROL DE GRÁFICOS

//CONTROL DE ARCHIVOS

//INTERACCIONES USUARIO-PROGRAMA

//CICLOS MENU/JUEGO/RONDA/TURNO

//PROGRAMA PRINCIPAL

void main(){
    
}