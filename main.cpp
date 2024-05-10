//PROYECTO DE ALGORITMOS Y ESTRUCTURAS DE DATOS 
//MADE BY: RICARDO MEJIA & EDUARDO ROJAS


//#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <string> 
#include <windows.h>
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
    int posicion
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

//TABLERO

Casillas* crearCasilla(int valor) {
  Casillas *nuevo = new Casillas;
  nuevo->id_casillas = valor;
  nuevo->prox = NULL;
  return nuevo;
}//funcion para crear los nodos del tablero(lista)

bool TableroVacio(Casillas *inicio){
    return inicio==NULL;
}

void mostrartablero(Casillas *Tablero){
   Casillas *mover=Tablero;
      while (mover != NULL)
        {
           cout <<" | "<< mover->id_casillas<<" | " <<"->";
           mover = mover->prox;
         }
         cout<<"F I N"<<endl;
   }  

void llenado_tablero(Casillas *&Tablero,int iddelacasilla){ //llenado de archivo de forma manual sin uso de archivos
    Casillas *CasillaNueva=crearCasilla(iddelacasilla);
    if(TableroVacio(Tablero)){
        Tablero=CasillaNueva;
    }else{
        Casillas *auxiliar_mover=Tablero;
        while(auxiliar_mover->prox!=NULL){
            auxiliar_mover=auxiliar_mover->prox;
        }
        auxiliar_mover->prox=CasillaNueva;
    }
}

//CICLOS MENU/JUEGO/RONDA/TURNO

void imprime_opciones_menu(){
    cout<<"A:  Iniciar Partida"<<endl;
    cout<<"C:  Tutorial/Instrucciones"<<endl;
    cout<<"B:  Salir del Juego"<<endl;
}

void imprime_instrucciones(){

}

void Turno(/*parámetros*/){ //acaba cuando el jugador elija su acción

}

void Ronda(/*parámetros*/){ //acaba al haber terminado el Turno de cada jugador

}

void Partida(/*parámetros*/){ //acaba cuando se cumple la condicion de fin de partida, ya sea victoria o salida forzada

}

void MainMenu(/*parámetros*/){// acaba cuando se decida cerrar el juego(programa) por completo
    bool fin_partida=false;
    int opcion;
    cout<<"Que opcion desea escoger?";
    imprime_opciones_menu();
    cin>>opcion;
    switch (opcion){
    case 1: //INICIA PARTIDA
        Partida(); //In
    break;
    
    case 2: //INICIA INSTRUCCIONES/REGLAS/TURORIAL
        imprime_instrucciones();
    break;
    
    default:
        cout<<"Opcion Inválida..."<<endl;
    break;
    }
}
void Mover_Jugador(Jugadores jugador){
    Jugadores *JugadorN= CrearJugador()

}

//PROGRAMA PRINCIPAL
main(){
    int idtablero=1,i=0;
    Casillas *Tablero=NULL;
    while(i<25){
        llenado_tablero(Tablero,idtablero);
        idtablero++;
        i++;
    };
    mostrartablero(Tablero);

   /// MainMenu(/*parámetros*/);  //Llamamos al ciclo general de la partida
    
}
