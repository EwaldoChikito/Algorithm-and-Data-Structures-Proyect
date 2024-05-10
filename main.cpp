//PROYECTO DE ALGORITMOS Y ESTRUCTURAS DE DATOS 
//MADE BY: RICARDO MEJIA & EDUARDO ROJAS


//#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

//Declaración de Estructuras

struct Recursos{
    int id_recurso;
    string nombre_recurso;
    Recursos *prox_recurso;
};

struct Jugadores{
    int pts;
    int equipo;
    string nombre_equipo;
    string nombre_jugador;
    Recursos *inventario;
    Jugadores *prox_jugador;
};

struct Casillas{
    int id_casillas;
    string bioma;
    Recursos *RLista;
    Jugadores *Jlista;
    Casillas *prox;
};

Recursos *CrearRecurso(int id, string nombre){
    Recursos *NuevoRecurso= new Recursos;
    NuevoRecurso->id_recurso=id;
    NuevoRecurso->nombre_recurso=nombre;
    NuevoRecurso->prox_recurso=NULL;
    return NuevoRecurso;
}

Jugadores *CrearJugador(string nombre){
    Jugadores *NuevoJugador= new Jugadores;
    NuevoJugador->pts=0;
    NuevoJugador->nombre_jugador=nombre;
    NuevoJugador->inventario=NULL;
    NuevoJugador->prox_jugador=NULL;
    return NuevoJugador;
}

//CONTROL DE GRÁFICOS

//CONTROL DE ARCHIVOS

//INTERACCIONES USUARIO-PROGRAMA

//CICLOS MENU/JUEGO/RONDA/TURNO

//PROGRAMA PRINCIPAL
main(){
    string palabra;
    cout<<"digalo ";
    cin>>palabra;
    
}
