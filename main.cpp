//PROYECTO DE ALGORITMOS Y ESTRUCTURAS DE DATOS 
//MADE BY: RICARDO MEJIA & EDUARDO ROJAS

//CONSTANTES Y LIBRERIAS
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <string> 
#include <windows.h>

using namespace std;
#define ARRIBA 'i'
#define ABAJO 'k'
#define ENTER 13
#define color SetConsoleTextAttribute

//Declaración de Estructuras

struct Recursos{
    int id_recurso;
    string nombre_recurso;
    Recursos *prox_recurso;
};

struct Casillas{
    int id_casillas;
    string bioma;
    Recursos *RLista;
    Casillas *prox;
};

struct Jugadores{
    int pts;
    int equipo;
    int posicion;
    Casillas *ubicacion_casilla;
    string nombre_equipo;
    string nombre_jugador;
    Recursos *inventario;
    Jugadores *prox_jugador;
};

Recursos *CrearRecurso(int id, string nombre){
    Recursos *NuevoRecurso= new Recursos;
    NuevoRecurso->id_recurso=id;
    NuevoRecurso->nombre_recurso=nombre;
    NuevoRecurso->prox_recurso=NULL;
    return NuevoRecurso;
};

Jugadores *CrearJugador(string nombre){
    Jugadores *NuevoJugador= new Jugadores;
    NuevoJugador->pts=0;
    NuevoJugador->nombre_jugador=nombre;
    NuevoJugador->inventario=NULL;
    NuevoJugador->prox_jugador=NULL;
    return NuevoJugador;
};

//CONTROL DE GRÁFICOS

char getch2 (){
   //FUNCIÓN QUE DETECTA LA TECLA PRESIONADA EN EL TECLADO EN TIEMPO REAL
   
   char c=0;
   DWORD modo, contador;
   HANDLE ih = GetStdHandle(STD_INPUT_HANDLE);
 
   // Desactivamos escritura en terminal
   SetConsoleMode (ih, modo & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));
 
   ReadConsoleA (ih, &c, 1, &contador, NULL);
 
   if (c == 0) {
      ReadConsoleA (ih, &c, 1, &contador, NULL);
   }
 
   SetConsoleMode (ih, modo); // Devolvemos control normal
   return c;
}

void gotoxy(int x, int y){
    //FUNCION QUE IMPRIME UN TEXTO DESEADO EN UNAS COORDENADAS (X,Y) ESPECÍFICAS

    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

void ocultarCursor(){
    //FUNCION  QUE OCULTA EL CURSOR QUE PARPADEA EN LA TERMINAL

    HANDLE hCon;
    hCon=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1;
    cci.bVisible = FALSE;

    SetConsoleCursorInfo(hCon,&cci);
}

int flechas_menu(const char *opciones[], int n){
    int opcionSeleccionada = 1; 
    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );//IMPLEMENTACIÓN DE COLORES EN LA TEMRMINAL
 
    int tecla;
    bool repite = true;
 
    do{
        ocultarCursor();
        system("cls");
        color(hConsole, 12);
        gotoxy(15, 3 + opcionSeleccionada); cout << "==>" << endl;
 
        // Imprime el título del menú
        ocultarCursor();
        color(hConsole, 6);
        gotoxy(15, 2); cout << "BIENVENIDO AL JUEGO AMBIENTAL"; //Hay que encontrar un mejor nombre
        color(hConsole, 8);
        gotoxy(8,9); cout<<"Usar las teclas I y K para moverse por el menu";
        gotoxy(8,10); cout<<"Presione enter para seleccionar alguna opcion";
        // Imprime las opciones del menú

        for (int i = 0; i < n; ++i) {
            ocultarCursor();
            color(hConsole, 7);
            gotoxy(19, 4 + i); cout << i + 1 << ") " << opciones[i];
        }
 
      // Solo permite que se ingrese ARRIBA, ABAJO o ENTER
 
        do {
            ocultarCursor();
            tecla = getch2();} 
        while (tecla != ARRIBA && tecla != ABAJO && tecla != ENTER);
        
        switch (tecla) {
 
            case ARRIBA:   // En caso que se presione ARRIBA 
                opcionSeleccionada--;
                if (opcionSeleccionada < 1) {
                    opcionSeleccionada = n;
                }
            break;
 
         case ABAJO:
            opcionSeleccionada++;
 
            if (opcionSeleccionada > n) {
               opcionSeleccionada = 1;
            }
 
            break;
 
         case ENTER:
            repite = false;
            break;
      }
   } while (repite);
 
   return opcionSeleccionada;
}

void imprime_opciones_menu(){
    cout<<"A:  Iniciar Partida"<<endl;
    cout<<"C:  Tutorial/Instrucciones"<<endl;
    cout<<"B:  Salir del Juego"<<endl;
}

void imprime_instrucciones(){

}

//CONTROL DE ARCHIVOS

//TABLERO

Casillas* crearCasilla(int valor){
  Casillas *nuevo = new Casillas;
  nuevo->id_casillas = valor;
  nuevo->prox = NULL;
  return nuevo;
}//funcion para crear los nodos del tablero(lista)

bool TableroVacio(Casillas *inicio){
    return inicio==NULL;
}

bool JugadoresVacio(Jugadores *inicio){
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

void llenado_tablero(Casillas *&Tablero) {
    int i = 1;
    while (i <= 25) { 
        Casillas *CasillaNueva = crearCasilla(i);
        if (TableroVacio(Tablero)) {
            Tablero = CasillaNueva;
        } else {
            Casillas *auxiliar_mover = Tablero;
            while (auxiliar_mover->prox != NULL) {
                auxiliar_mover = auxiliar_mover->prox;
            }
            auxiliar_mover->prox = CasillaNueva;
        }
        i++;
    }
}

void CrearListadeJugadores(Jugadores *&JugadorInicial, Casillas *&Tablero){
    int numerodejugadores;
    cout<<"Indique la cantidad de jugadores: ";
    cin>>numerodejugadores;
    int i=1;
    string nombredejugador; 
    while(i<=numerodejugadores){
        cout<<"Indique el nombre del jugador numero "<<i<<" aqui: ";
        cin>>nombredejugador;
        Jugadores *JugadorNuevo=CrearJugador(nombredejugador);
        JugadorNuevo->ubicacion_casilla=Tablero;
        JugadorNuevo->posicion=Tablero->id_casillas;

        if(JugadoresVacio(JugadorInicial)){
            JugadorInicial=JugadorNuevo;
        }else{
            Jugadores *auxiliar=JugadorInicial;
            while(auxiliar->prox_jugador != NULL){
                auxiliar=auxiliar->prox_jugador;
            }
            auxiliar->prox_jugador=JugadorNuevo;
        }
        
        i++;
    }
}


void mostrarjugadores(Jugadores *JugadorInicial){
    Jugadores *mover=JugadorInicial;
      while (mover != NULL){
           cout <<" | "<< mover->nombre_jugador<<" | " <<"->";
           mover = mover->prox_jugador;
        }
        cout<<"F I N"<<endl;
   }



void mover_jugador(Jugadores *&JugadorInicial, Casillas *&Tablero){//esto iria en turno y luego en ronda
    Jugadores *Auxiliar=JugadorInicial;
    int contador=1,opcion;


    while(Auxiliar!=NULL){
        cout<<Auxiliar->nombre_jugador<<" quieres moverte una casilla hacia adelante?"<<endl;
        cout<<"1 para SI"<<endl;
        cout<<"0 para NO"<<endl;
        cin>>opcion;
        if(opcion==1){
            if(Auxiliar->ubicacion_casilla->prox!=NULL){
                Auxiliar->ubicacion_casilla=Auxiliar->ubicacion_casilla->prox;
                Auxiliar->posicion=Auxiliar->ubicacion_casilla->id_casillas;
                cout<<Auxiliar->nombre_jugador<<" se movio a la casilla "<<Auxiliar->posicion<<endl;
            }else{
                cout<< Auxiliar->nombre_jugador << " ha llegado al final del tablero" << endl;
            }
        }else if(opcion==0){
        cout<< Auxiliar->nombre_jugador<<" no realizo ningun movimiento,esta ubicado en la casilla: "<<Auxiliar->posicion;
        }else{
            cout<<"Opcion Invalida"<<endl;
        }
        Auxiliar = Auxiliar->prox_jugador;
        }
}

//CICLOS MENU/JUEGO/RONDA/TURNO

void Turno(/*parámetros*/){ //acaba cuando el jugador elija su acción

}

void Ronda(/*parámetros*/){ //acaba al haber terminado el Turno de cada jugador

}

void Partida(){ //acaba cuando se cumple la condicion de fin de partida, ya sea victoria o salida forzada

}

void MainMenu(/*parámetros*/){// acaba cuando se decida cerrar el juego(programa) por completo
    bool fin_partida=false;
    int opcion;
    int n=3; //numero de opciones del Menú
    const char *opciones[] = {"INICIAR PARTIDA", "REGLAS/TUTORIAL", "SALIR DEL JUEGO"};
    opcion=flechas_menu(opciones,n);
    while(fin_partida!=true){

        switch (opcion){
        case 1: //INICIA PARTIDA
            Partida(); //Inicia la partida
        break;
        
        case 2: //INICIA INSTRUCCIONES/REGLAS/TURORIAL
            imprime_instrucciones();
        break;

        case 3:
            system("cls");
            gotoxy(15,2);cout<<"\n\nHa Salido con exito del Juego, Hasta luego!"<<endl;
            fin_partida=true;
        break;   
        default:
            cout<<"Opcion Inválida..."<<endl;
        break;
        }
    }
}


//PROGRAMA PRINCIPAL
main(){
    Jugadores *jugador1=NULL;
    Casillas *Tablero=NULL;
    int k=1;
    //MainMenu();  //Llamamos al ciclo general de la partida
    
    llenado_tablero(Tablero);
    mostrartablero(Tablero);
 	CrearListadeJugadores(jugador1,Tablero);
    mostrarjugadores(jugador1);
    mover_jugador(jugador1,Tablero);

    
}

