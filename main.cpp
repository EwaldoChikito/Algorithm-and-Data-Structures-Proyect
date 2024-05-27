//PROYECTO DE ALGORITMOS Y ESTRUCTURAS DE DATOS 
//MADE BY: RICARDO MEJIA & EDUARDO ROJAS

//CONSTANTES Y LIBRERIAS
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <string> 
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <time.h>

#define ARRIBA 72
#define ABAJO 80
#define ENTER 13
#define color SetConsoleTextAttribute
using namespace std;

//Declaración de Estructuras

struct Inventario{
    int agua;
    int metal;
    int piedra;
    int madera;
    int papel;
    int semilla;
    Inventario *prox;
};

struct Casillas{
    int id_casillas;
    string bioma;
    int recursoid=0;
    Inventario *inventario;
    Casillas *prox;
};

struct Jugadores{
    int pts;
    int equipo;
    int posicion;
    Casillas *ubicacion_casilla;
    string nombre_equipo;
    string nombre_jugador;
    Inventario *inventario;
    Jugadores *prox_jugador;
};

//INICIALIZACIÓN DE ESTRUCTURAS

void CrearInventario(Jugadores *&JugadorX){
    Inventario *NuevoInventario= new Inventario;
    JugadorX->inventario=NuevoInventario;
    NuevoInventario->agua=1;
    NuevoInventario->metal=1;
    NuevoInventario->piedra=1;
    NuevoInventario->madera=1;
    NuevoInventario->semilla=1;
    NuevoInventario->papel=1;
}

void CrearInventarioCasillas(Casillas *&Casillitas){
    Inventario *NuevoInventario= new Inventario;
    Casillitas->inventario=NuevoInventario;
    NuevoInventario->agua=0;
    NuevoInventario->metal=0;
    NuevoInventario->piedra=0;
    NuevoInventario->madera=0;
    NuevoInventario->semilla=0;
    NuevoInventario->papel=0;
}

Jugadores *CrearJugador(string nombre){
    Jugadores *NuevoJugador= new Jugadores;
    NuevoJugador->pts=5;
    NuevoJugador->nombre_jugador=nombre;
    NuevoJugador->inventario=NULL;
    NuevoJugador->prox_jugador=NULL;
    CrearInventario(NuevoJugador);
    return NuevoJugador;
};

Casillas* crearCasilla(int valor){
    Casillas *nuevo = new Casillas;
    nuevo->id_casillas = valor;
    CrearInventarioCasillas(nuevo);
    nuevo->prox = NULL;
    return nuevo;
}//funcion para crear los nodos del tablero(lista)

bool TableroVacio(Casillas *inicio){
    return inicio==NULL;
}

bool JugadoresVacio(Jugadores *inicio){
    return inicio==NULL;
}


//CONTROL DE GRÁFICOS

void delay(int secs) {
    for(int i = (time(NULL) + secs); time(NULL) != i; time(NULL));
}

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

void mostrarCursor(){
    //FUNCION  QUE OCULTA EL CURSOR QUE PARPADEA EN LA TERMINAL

    HANDLE hCon;
    hCon=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 4;
    cci.bVisible = true;

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
        gotoxy(30, 13 + opcionSeleccionada); cout << "==>" << endl;
        gotoxy(53, 13 + opcionSeleccionada); cout << "<==" << endl;

        // Imprime el título del menú
        ocultarCursor();
        color(hConsole, 6);
        gotoxy(29, 11); cout << "BIENVENIDO AL JUEGO AMBIENTAL"; //Hay que encontrar un mejor nombre
        color(hConsole, 8);
        gotoxy(8,19); cout<<"-Usar las Teclas de las ''FLECHAS DIRECCIONALES'' para moverse por el menu";
        gotoxy(20,20); cout<<"-Presione enter para seleccionar alguna opcion";
        gotoxy(12,21); cout<<"-Se recomienda aumentar el tamano de la ventana del compilador";
        // Imprime las opciones del menú

        for (int i = 0; i < n; ++i) {
            ocultarCursor();
            color(hConsole, 7);
            gotoxy(34, 14 + i); cout << i + 1 << ") " << opciones[i];
        }

      // Solo permite que se ingrese ARRIBA, ABAJO o ENTER

        do {
            ocultarCursor();
            tecla = getch();
        }while (tecla != ARRIBA && tecla != ABAJO && tecla != ENTER);
        
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
    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );//IMPLEMENTACIÓN DE COLORES EN LA TEMRMINAL
    cout<<"REGLAS PARA JUGAR"<<endl;
    color(hConsole,13);
    cout<<"1.Jugabilidad"<<endl;
    color(hConsole,10);
    cout<<"2.Recursos"<<endl;
    color(hConsole,11);
    cout<<"3.Obstaculos"<<endl;
    color(hConsole,12);
    cout<<"4.Tipos de casillas"<<endl;
    color(hConsole,14);
    cout<<"5.Volver al menu";
    int opcion;bool valido=false;
    cout<<"Indique que apartado desea ver"<<endl;
    while(valido==false){
        cin>>opcion;
        system("cls");
        switch(opcion){
            case 1:
                system("cls");
                cout<<"J U G A B I L I D A D"<<endl;
                color(hConsole,8);
                cout<<"1.La cantidad maxima de jugadores por partida es de 3"<<endl;
                cout<<"2.Cada jugador cuenta con la opcion de elegir su propio equipo, el cual cuenta con interacciones especiales en el enfrentamiento contra jefes"<<endl;
                cout<<"3.El juego se encuentra dividido en turnos y rondas, al terminar las rondas el jugador tendra la opcion de elegir si quiere seguir jugando o no"<<endl;
                cout<<"4.En cada turno se le preguntara al jugador si desea moverse o no, de querer hacerlo avanzara una casilla, de lo contrario se pasa al turno del siguiente jugador"<<endl;
                cout<<"5.El juego cuenta con 5 biomas, representado por colores, en el siguiente orden: [BOSQUE]->[CIUDAD]->[TUNDRA]->[MARITIMO]->[SABANA]"<<endl;
                cout<<"6.Existen 4 tipos de casillas: [CASILLA DE RECURSOS],[CASILLA DE TRIVIAS],[CASILLA DE INVESTIGACION/ACCION],[CASILLA DE JEFES]"<<endl;
                cout<<"7.Al superar jefes,trivias o investigaciones se obtendran recursos, bonificaciones o puntos"<<endl;
                cout<<"8.La partida finalizara en el momento que uno de los 3 jugadores llegue a la casilla 25"<<endl;
                cout<<"9.Si un jugador decide que ya no quiere seguir jugando la partida terminara para todos"<<endl;
                valido=true;
            break;
            case 2:
                system("cls");
                cout<<"R E C U R S O S"<<endl;
                color(hConsole,8);
                cout<<"1.El juego cuenta con 6 recursos: [AGUA],[METAL],[PAPEL],[SEMILLAS],[MADERA],[PIEDRA]"<<endl;
                cout<<"2.Todos los jugadores empiezan la partida con una unidad de cada recurso existente"<<endl;
                cout<<"3.Los jugadores podran completar diversos desafios para obtener recursos o multiplicadores de ellos"<<endl;
                cout<<"4.Los jugadores pueden obtener recursos gratis de ciertas casillas"<<endl;
                cout<<"5.Los puntos cuentan como la moneda del juego, es decir, si quieres invertir en algun proyecto o investigacion deberas donar puntos."<<endl;
                valido=true;
            break;
            case 3:
                system("cls");
                cout<<"O B S T A C U L O S"<<endl;
                color(hConsole,8);
                cout<<"1.El juego cuenta con jefes de zona/bioma, al llegar a las casillas que sean multiplo de 5 hasta el 25 se tendran que enfrentar a un jefe"<<endl;
                cout<<"a.JEFE BOSQUE= Incendio Forestal"<<endl;
                cout<<"b.JEFE CIUDAD= Contaminacion por C02"<<endl;
                cout<<"c.JEFE TUNDRA= Calentamiento global"<<endl;
                cout<<"d.JEFE MARITIMO= Contaminacion por residuos y desechos"<<endl;
                cout<<"e.JEFE SABANA= Perdida de biodiversidad (fauna y flora)"<<endl;
                cout<<"2.Si se vence al jefe de manera correcta, el jugador recibira recompensas(puntos,bonificaciones por equipo,recursos,logros), de lo contrario perdera puntos y recursos"<<endl;
                valido=true;
            break;
            case 4:
                system("cls");
                cout<<"T I P O S   D E   C A S I L L A S"<<endl;
                color(hConsole,8);
                cout<<"1.[CASILLA DE RECURSOS]= 2,6,9,11,14,16,19,21,24. En estas casillas el jugador obtendra de manera rapida recursos"<<endl;
                cout<<"2.[CASILLA DE TRIVIAS]= 4,8,13,17,22.En estas casillas el jugador debera responder una pregunta o situacion planteada, donde se dara una pista del jefe de zona y se podra ganar o perder recursos/puntos."<<endl;
                cout<<"3.[CASILLA DE JEFES]=5,10,15,20,25"<<endl;
                cout<<"4.[CASILLA DE INVESTIGACION/ACCION]=3,7,12,18,22"<<endl;
                valido=true;

            break;
            case 5:
            cout<<"Volviendo al menu"<<endl;
            valido=true;
            break;
            default:
            cout<<"Opcion invalida, ingrese de nuevo su opcion"<<endl;
            break;
        }
    }
    system("pause");
}

void imprimirflechas(){
    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );//IMPLEMENTACIÓN DE COLORES EN LA TEMRMINAL
    //FLECHAS DERECHA
    color(hConsole,12);
    gotoxy(54,2);
    cout<<"|";
    gotoxy(54,3);
    cout<<"|";
    gotoxy(54,4);//lista flecha 1
    cout<<"V";
    gotoxy(54,8);
    cout<<"|";
    gotoxy(54,9);
    cout<<"|";
    gotoxy(54,10);
    cout<<"V";
    //FLECHAS IZQUIERDA
    gotoxy(23,5);
    cout<<"|";
    gotoxy(23,6);
    cout<<"|";
    gotoxy(23,7);
    cout<<"V";
    gotoxy(23,11);
    cout<<"|";
    gotoxy(23,12);
    cout<<"|";
    gotoxy(23,13);
    cout<<"V";
    color(hConsole,15);
}    

void MostrarJugadores(Jugadores *listajugadores){
    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );//IMPLEMENTACIÓN DE COLORES EN LA TEMRMINAL
    Jugadores *mover=listajugadores;
    while (mover!=NULL){  //CICLO QUE APLICA COLOR A CADA PUNTO DE CADA JUGADOR
        if (mover->equipo==1){
            color(hConsole,12);
            if (mover->posicion==1){
                gotoxy( 24+mover->equipo,2 );
                cout<<"*";
            }
            if (mover->posicion==2){
                gotoxy( 30+mover->equipo,2 );
                cout<<"*";
            }
            if (mover->posicion==3){
                gotoxy( 36+mover->equipo,2 );
                cout<<"*";
            }
            if (mover->posicion==4){
                gotoxy( 42+mover->equipo,2 );
                cout<<"*";
            }
            if (mover->posicion==5){
                gotoxy( 48+mover->equipo,2 );
                cout<<"*";
            }
            if (mover->posicion==6){
                gotoxy( 48+mover->equipo,5 );
                cout<<"*";
            }
            if (mover->posicion==7){
                gotoxy( 42+mover->equipo,5 );
                cout<<"*";
            }
            if (mover->posicion==8){
                gotoxy( 36+mover->equipo,5 );
                cout<<"*";
            }
            if (mover->posicion==9){
                gotoxy( 30+mover->equipo,5 );
                cout<<"*";
            }
            if (mover->posicion==10){
                gotoxy( 24+mover->equipo,5 );
                cout<<"*";
            }
            if (mover->posicion==11){
                gotoxy( 24+mover->equipo,8 );
                cout<<"*";
            }
            if (mover->posicion==12){
                gotoxy( 30+mover->equipo,8 );
                cout<<"*";
            }
            if (mover->posicion==13){
                gotoxy( 36+mover->equipo,8 );
                cout<<"*";
            }
            if (mover->posicion==14){
                gotoxy( 42+mover->equipo,8 );
                cout<<"*";
            }
            if (mover->posicion==15){
                gotoxy( 48+mover->equipo,8 );
                cout<<"*";
            }
            if (mover->posicion==16){
                gotoxy( 48+mover->equipo,11 );
                cout<<"*";
            }
            if (mover->posicion==17){
                gotoxy( 42+mover->equipo,11 );
                cout<<"*";
            }
            if (mover->posicion==18){
                gotoxy( 36+mover->equipo,11 );
                cout<<"*";
            }
            if (mover->posicion==19){
                gotoxy( 30+mover->equipo,11 );
                cout<<"*";
            }
            if (mover->posicion==20){
                gotoxy( 24+mover->equipo,11 );
                cout<<"*";
            }
            if (mover->posicion==21){
                gotoxy( 24+mover->equipo,14 );
                cout<<"*";
            }
            if (mover->posicion==22){
                gotoxy( 30+mover->equipo,14 );
                cout<<"*";
            }
            if (mover->posicion==23){
                gotoxy( 36+mover->equipo,14 );
                cout<<"*";
            }
            if (mover->posicion==24){
                gotoxy( 42+mover->equipo,14 );
                cout<<"*";
            }
            if (mover->posicion==25){
                gotoxy( 48+mover->equipo,14 );
                cout<<"*";
            }
        }
        
        if (mover->equipo==2){
            color(hConsole,9);
            if (mover->posicion==1){
                gotoxy( 24+mover->equipo,2 );
                cout<<"*";
            }
            if (mover->posicion==2){
                gotoxy( 30+mover->equipo,2 );
                cout<<"*";
            }
            if (mover->posicion==3){
                gotoxy( 36+mover->equipo,2 );
                cout<<"*";
            }
            if (mover->posicion==4){
                gotoxy( 42+mover->equipo,2 );
                cout<<"*";
            }
            if (mover->posicion==5){
                gotoxy( 48+mover->equipo,2 );
                cout<<"*";
            }
            if (mover->posicion==6){
                gotoxy( 48+mover->equipo,5 );
                cout<<"*";
            }
            if (mover->posicion==7){
                gotoxy( 42+mover->equipo,5 );
                cout<<"*";
            }
            if (mover->posicion==8){
                gotoxy( 36+mover->equipo,5 );
                cout<<"*";
            }
            if (mover->posicion==9){
                gotoxy( 30+mover->equipo,5 );
                cout<<"*";
            }
            if (mover->posicion==10){
                gotoxy( 24+mover->equipo,5 );
                cout<<"*";
            }
            if (mover->posicion==11){
                gotoxy( 24+mover->equipo,8 );
                cout<<"*";
            }
            if (mover->posicion==12){
                gotoxy( 30+mover->equipo,8 );
                cout<<"*";
            }
            if (mover->posicion==13){
                gotoxy( 36+mover->equipo,8 );
                cout<<"*";
            }
            if (mover->posicion==14){
                gotoxy( 42+mover->equipo,8 );
                cout<<"*";
            }
            if (mover->posicion==15){
                gotoxy( 48+mover->equipo,8 );
                cout<<"*";
            }
            if (mover->posicion==16){
                gotoxy( 48+mover->equipo,11 );
                cout<<"*";
            }
            if (mover->posicion==17){
                gotoxy( 42+mover->equipo,11 );
                cout<<"*";
            }
            if (mover->posicion==18){
                gotoxy( 36+mover->equipo,11 );
                cout<<"*";
            }
            if (mover->posicion==19){
                gotoxy( 30+mover->equipo,11 );
                cout<<"*";
            }
            if (mover->posicion==20){
                gotoxy( 24+mover->equipo,11 );
                cout<<"*";
            }
            if (mover->posicion==21){
                gotoxy( 24+mover->equipo,14 );
                cout<<"*";
            }
            if (mover->posicion==22){
                gotoxy( 30+mover->equipo,14 );
                cout<<"*";
            }
            if (mover->posicion==23){
                gotoxy( 36+mover->equipo,14 );
                cout<<"*";
            }
            if (mover->posicion==24){
                gotoxy( 42+mover->equipo,14 );
                cout<<"*";
            }
            if (mover->posicion==25){
                gotoxy( 48+mover->equipo,14 );
                cout<<"*";
            }
        }
        
        if (mover->equipo==3){
            color(hConsole,10);
            if (mover->posicion==1){
                gotoxy( 24+mover->equipo,2 );
                cout<<"*";
            }
            if (mover->posicion==2){
                gotoxy( 30+mover->equipo,2 );
                cout<<"*";
            }
            if (mover->posicion==3){
                gotoxy( 36+mover->equipo,2 );
                cout<<"*";
            }
            if (mover->posicion==4){
                gotoxy( 42+mover->equipo,2 );
                cout<<"*";
            }
            if (mover->posicion==5){
                gotoxy( 48+mover->equipo,2 );
                cout<<"*";
            }
            if (mover->posicion==6){
                gotoxy( 48+mover->equipo,5 );
                cout<<"*";
            }
            if (mover->posicion==7){
                gotoxy( 42+mover->equipo,5 );
                cout<<"*";
            }
            if (mover->posicion==8){
                gotoxy( 36+mover->equipo,5 );
                cout<<"*";
            }
            if (mover->posicion==9){
                gotoxy( 30+mover->equipo,5 );
                cout<<"*";
            }
            if (mover->posicion==10){
                gotoxy( 24+mover->equipo,5 );
                cout<<"*";
            }
            if (mover->posicion==11){
                gotoxy( 24+mover->equipo,8 );
                cout<<"*";
            }
            if (mover->posicion==12){
                gotoxy( 30+mover->equipo,8 );
                cout<<"*";
            }
            if (mover->posicion==13){
                gotoxy( 36+mover->equipo,8 );
                cout<<"*";
            }
            if (mover->posicion==14){
                gotoxy( 42+mover->equipo,8 );
                cout<<"*";
            }
            if (mover->posicion==15){
                gotoxy( 48+mover->equipo,8 );
                cout<<"*";
            }
            if (mover->posicion==16){
                gotoxy( 48+mover->equipo,11 );
                cout<<"*";
            }
            if (mover->posicion==17){
                gotoxy( 42+mover->equipo,11 );
                cout<<"*";
            }
            if (mover->posicion==18){
                gotoxy( 36+mover->equipo,11 );
                cout<<"*";
            }
            if (mover->posicion==19){
                gotoxy( 30+mover->equipo,11 );
                cout<<"*";
            }
            if (mover->posicion==20){
                gotoxy( 24+mover->equipo,11 );
                cout<<"*";
            }
            if (mover->posicion==21){
                gotoxy( 24+mover->equipo,14 );
                cout<<"*";
            }
            if (mover->posicion==22){
                gotoxy( 30+mover->equipo,14 );
                cout<<"*";
            }
            if (mover->posicion==23){
                gotoxy( 36+mover->equipo,14 );
                cout<<"*";
            }
            if (mover->posicion==24){
                gotoxy( 42+mover->equipo,14 );
                cout<<"*";
            }
            if (mover->posicion==25){
                gotoxy( 48+mover->equipo,14 );
                cout<<"*";
            }
        }
        mover=mover->prox_jugador;
    }
    color(hConsole,15);
}

void mostrartablero(Casillas *Tablero){
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // IMPLEMENTACIÓN DE COLORES EN LA TERMINAL
    mostrarCursor();
    int columnas = 5, filas = 14;
    bool izquierdaADerecha = true;
    Casillas *mover = Tablero;

    for (int i = 1; i < filas; i += 3) {
        if (izquierdaADerecha) {
            for (int j = 0; j < columnas; j++) {
                if (mover->id_casillas < 10) { // ORDEN IZQUIERDA->DERECHA DE 1 DIGITO
                    // BOSQUE
                    if (mover->id_casillas > 0 && mover->id_casillas < 6) {
                        gotoxy((j * 6) + 5 + 20, i);
                        color(hConsole, 10);
                        cout << "|0" << mover->id_casillas << "|";
                        color(hConsole, 12);
                        cout << "->";
                        color(hConsole, 15);
                    }
                    // CIUDAD
                    if (mover->id_casillas > 10 && mover->id_casillas < 16) {
                        gotoxy((j * 6) + 5 + 20, i);
                        color(hConsole, 15);
                        cout << "|0" << mover->id_casillas << "|";
                        color(hConsole, 12);
                        cout << "->";
                        color(hConsole, 15);
                    }
                    // TUNDRA
                    if (mover->id_casillas > 20 && mover->id_casillas < 25) {
                        gotoxy((j * 6) + 5 + 18, i);
                        color(hConsole, 11);
                        cout << "|0" << mover->id_casillas << "|";
                        color(hConsole, 12);
                        cout << "->";
                        color(hConsole, 15);
                    }
                    if (mover->id_casillas==25) {
                        gotoxy((j * 6) + 5 + 20, i);
                        color(hConsole, 10);
                        cout << "|" << mover->id_casillas << "|";
                        color(hConsole, 15);
                    }
                } else { // ORDEN IZQUIERDA->DERECHA DE 2 DIGITOS
                    // BOSQUE
                    if (mover->id_casillas > 0 && mover->id_casillas < 6) {
                        gotoxy((j * 6) + 5 + 20, i);
                        color(hConsole, 10);
                        cout << "|" << mover->id_casillas << "|";
                        color(hConsole, 12);
                        cout << "->";
                        color(hConsole, 15);
                    }
                    // CIUDAD
                    if (mover->id_casillas > 10 && mover->id_casillas < 16) {
                        gotoxy((j * 6) + 5 + 20, i);
                        color(hConsole, 15);
                        cout << "|" << mover->id_casillas << "|";
                        color(hConsole, 12);
                        cout << "->";
                        color(hConsole, 15);
                    }
                    // TUNDRA
                    if (mover->id_casillas > 20 && mover->id_casillas < 25) {
                        gotoxy((j * 6) + 5 + 20, i);
                        color(hConsole, 11);
                        cout << "|" << mover->id_casillas << "|";
                        color(hConsole, 12);
                        cout << "->";
                        color(hConsole, 15);
                    }
                    if (mover->id_casillas==25) {
                        gotoxy((j * 6) + 5 + 20, i);
                        color(hConsole, 10);
                        cout << "|" << mover->id_casillas << "|";
                        color(hConsole, 15);
                    }
                }
                mover = mover->prox;
            }
        } else {
            for (int j = columnas - 1; j >= 0; j--) {
                if (mover->id_casillas < 10) { // ORDEN DERECHA->IZQUIERDA DE 1 DIGITO
                    // MARITIMO
                    if (mover->id_casillas >= 6 && mover->id_casillas <= 10) {
                        gotoxy((j * 6) + 3 + 20, i);
                        color(hConsole, 12);
                        cout << "<-";
                        color(hConsole, 9);
                        cout << "|0" << mover->id_casillas << "|";
                    }
                    // SABANA
                    if (mover->id_casillas > 15 && mover->id_casillas < 21) {
                        gotoxy((j * 6) + 3 + 20, i);
                        color(hConsole, 12);
                        cout << "<-";
                        color(hConsole, 14);
                        cout << "|0" << mover->id_casillas << "|";
                    }
                } else { // ORDEN DERECHA->IZQUIERDA DE 2 DIGITOS
                    // MARITIMO
                    if (mover->id_casillas >= 6 && mover->id_casillas <= 10) {
                        gotoxy((j * 6) + 3 + 20, i);
                        color(hConsole, 12);
                        cout << "<-";
                        color(hConsole, 9);
                        cout << "|" << mover->id_casillas << "|";
                    }
                    // SABANA
                    if (mover->id_casillas > 15 && mover->id_casillas < 21) {
                        gotoxy((j * 6) + 3 + 20, i);
                        color(hConsole, 12);
                        cout << "<-";
                        color(hConsole, 14);
                        cout << "|" << mover->id_casillas << "|";
                    }
                }
                mover = mover->prox;
            }
        }
        izquierdaADerecha = !izquierdaADerecha; 
    }
    
    imprimirflechas();
}

void MostrarInventario(Jugadores *&JugadorX){
    bool valido=true;
    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );//IMPLEMENTACIÓN DE COLORES EN LA TEMRMINAL
    while(valido==true){
            gotoxy(30,14);
            cout<<"El inventario de "<<JugadorX->nombre_jugador<< " es: "<<endl;
            color(hConsole,11);
            gotoxy(35,16);
            cout<<"Agua: "<<JugadorX->inventario->agua<<endl;
            color(hConsole,13);
            gotoxy(35,17);
            cout<<"Metal: "<<JugadorX->inventario->metal<<endl;
            color(hConsole,8);
            gotoxy(35,18);
            cout<<"Piedra: "<<JugadorX->inventario->piedra<<endl;
            color(hConsole,14);
            gotoxy(35,19);
            cout<<"Madera: "<<JugadorX->inventario->madera<<endl;
            color(hConsole,10);
            gotoxy(35,20);
            cout<<"Semilla: "<<JugadorX->inventario->semilla<<endl;
            color(hConsole,15);
            gotoxy(35,21);
            cout<<"Papel: "<<JugadorX->inventario->papel<<endl;
            valido=false;
            cout<<""<<endl;
            cout<<""<<endl;
            cout<<""<<endl;
            cout<<""<<endl;
        }
}

/*void mostrarjugadores(Jugadores *JugadorInicial){
    Jugadores *mover=JugadorInicial;
        while (mover != NULL){
            cout <<" | "<< mover->nombre_jugador<<" | " <<"->";
            mover = mover->prox_jugador;
        }
        cout<<"F I N"<<endl;
    }*/

//CONTROL DE ARCHIVOS

void ordenarJugadoresPorPuntos(Jugadores *&lista_jugadores) {
    if (!lista_jugadores) return;

    Jugadores *actual = lista_jugadores;
    while (actual) {
        Jugadores *maxJugador = actual;
        Jugadores *siguiente = actual->prox_jugador;

        while (siguiente!=NULL) {
            if (siguiente->pts > maxJugador->pts) {
                maxJugador = siguiente;
            }
            siguiente = siguiente->prox_jugador;
        }

        if (maxJugador != actual) {
            int tempPts = maxJugador->pts;
            maxJugador->pts = actual->pts;
            actual->pts = tempPts;

            int tempEquipo = maxJugador->equipo;
            maxJugador->equipo = actual->equipo;
            actual->equipo = tempEquipo;

            int tempPosicion = maxJugador->posicion;
            maxJugador->posicion = actual->posicion;
            actual->posicion = tempPosicion;

            Casillas *tempUbicacionCasilla = maxJugador->ubicacion_casilla;
            maxJugador->ubicacion_casilla = actual->ubicacion_casilla;
            actual->ubicacion_casilla = tempUbicacionCasilla;

            string tempNombreEquipo = maxJugador->nombre_equipo;
            maxJugador->nombre_equipo = actual->nombre_equipo;
            actual->nombre_equipo = tempNombreEquipo;

            string tempNombreJugador = maxJugador->nombre_jugador;
            maxJugador->nombre_jugador = actual->nombre_jugador;
            actual->nombre_jugador = tempNombreJugador;

            Inventario *tempInventario = maxJugador->inventario;
            maxJugador->inventario = actual->inventario;
            actual->inventario = tempInventario;
        }

        actual = actual->prox_jugador;
    }
}

void guardarTop(Jugadores *lista_jugadores) {
    ordenarJugadoresPorPuntos(lista_jugadores);

    ofstream archivo("top_ten.txt");
    if (archivo.is_open()) {
        archivo << "TOP MEJORES JUGADORES\n";
        archivo << "====================\n";

        Jugadores *actual = lista_jugadores;
        int contador = 0;
        while (actual && contador < 10) {
            archivo << contador + 1 << ". " << actual->nombre_jugador << " - Puntos: " << actual->pts << "\n";
            actual = actual->prox_jugador;
            contador++;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo para escribir el top 10.\n";
    }
}

//TABLERO
void CrearListadeJugadores(Jugadores *&JugadorInicial, Casillas *&Tablero,int numerodejugadores){
    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );//IMPLEMENTACIÓN DE COLORES EN LA TEMRMINAL
    mostrarCursor();
    int opcion_equipo;
    int i=1;
    string nombredejugador; 
    while(i<=numerodejugadores){
        gotoxy(20,15);
        cout<<"Indique el nombre del jugador numero "<<i<<" aqui: ";
        cin>>nombredejugador;
        Jugadores *JugadorNuevo=CrearJugador(nombredejugador);
        JugadorNuevo->ubicacion_casilla=Tablero;
        JugadorNuevo->posicion=Tablero->id_casillas;
        do {
            system("cls");
            gotoxy(20,12);
            cout<<"Indique a cual equipo quiere pertenecer: "<<endl;
            color(hConsole,12);
            gotoxy(9,15);
            cout<<"1. Equipo Rojo,son expertos en el uso de energias renovables";
            gotoxy(9,16);
            color(hConsole,9);
            cout<<"2. Equipo Azul,encargados del cuidado de ecosistemas maritimos";
            gotoxy(9,17);
            color(hConsole,10);
            cout<<"3. Equipo Verde,enfocados en la conservacion de la fauna y la deforestacion";
            color(hConsole,15);
            gotoxy(33,19);
            cin>>opcion_equipo;
            if (opcion_equipo<1 || opcion_equipo>3) {
                system("cls");
                gotoxy(20,15);
                color(hConsole,12);
                cout << "Opcion invalida,por favor  seleccione 1, 2 o 3." << endl;
                color(hConsole,15);
                gotoxy(22,18);system("pause");
            }
        }while(opcion_equipo < 1 || opcion_equipo > 3);
        switch(opcion_equipo){
            case 1:
                ocultarCursor();
                system("cls");
                gotoxy(20,15);
                color(hConsole,12);
                cout<<"Bienvenido al Equipo Rojo, "<<nombredejugador<<endl;
                color(hConsole,15);
                JugadorNuevo->nombre_equipo="Equipo Rojo";
                JugadorNuevo->equipo=1;
                delay(3);
                mostrarCursor();
            break;
            
            case 2:
                ocultarCursor();
                system("cls");
                gotoxy(20,15);
                color(hConsole,9);
                cout<<"Bienvenido al Equipo Azul, "<<nombredejugador<<endl;
                color(hConsole,15);
                JugadorNuevo->nombre_equipo="Equipo Azul";
                JugadorNuevo->equipo=2;
                delay(3);
                mostrarCursor();
            break;
            
            case 3:
                ocultarCursor();
                system("cls");
                gotoxy(20,15);
                color(hConsole,10);
                cout<<"Bienvenido al Equipo Verde, "<<nombredejugador<<endl;
                color(hConsole,15);
                JugadorNuevo->nombre_equipo="Equipo Verde";
                JugadorNuevo->equipo=3;
                delay(3);
                mostrarCursor();
            break;
        }
        if(JugadoresVacio(JugadorInicial)){
            JugadorInicial=JugadorNuevo;
        }
        else{
            Jugadores *auxiliar=JugadorInicial;
            while(auxiliar->prox_jugador != NULL){
                auxiliar=auxiliar->prox_jugador;
            }
            auxiliar->prox_jugador=JugadorNuevo;
        }   
        i++;
    }
}

void llenado_tablero(Casillas *&Tablero) {
    int i = 1;
    
    while (i <= 25) { 
        Casillas *CasillaNueva = crearCasilla(i);
        if (TableroVacio(Tablero)) {
            Tablero = CasillaNueva;
        }else {
            Casillas *auxiliar_mover = Tablero;
            while (auxiliar_mover->prox != NULL) {
                auxiliar_mover = auxiliar_mover->prox;
            }
            auxiliar_mover->prox = CasillaNueva;
        }
        i++;
    }
    Casillas *auxiliar = Tablero;
    while(auxiliar!=NULL){
        if(auxiliar->id_casillas==2){
            auxiliar->recursoid=1;
            auxiliar->inventario->agua=5;
            auxiliar->inventario->semilla=6;
            auxiliar->inventario->piedra=4;
            auxiliar->inventario->madera=4;
            auxiliar->inventario->metal=4;
            auxiliar->inventario->papel=3;
        }
        if(auxiliar->id_casillas==6){
            auxiliar->recursoid=1;
            auxiliar->inventario->agua=3;
            auxiliar->inventario->semilla=4;
            auxiliar->inventario->piedra=2;
            auxiliar->inventario->madera=6;
            auxiliar->inventario->metal=8;
            auxiliar->inventario->papel=2;
        }
        if(auxiliar->id_casillas==9){
            auxiliar->recursoid=1;
            auxiliar->inventario->agua=5;
            auxiliar->inventario->semilla=2;
            auxiliar->inventario->piedra=1;
            auxiliar->inventario->madera=2;
            auxiliar->inventario->metal=3;
            auxiliar->inventario->papel=0;
        }
        if(auxiliar->id_casillas==11){
            auxiliar->recursoid=1;
            auxiliar->inventario->agua=4;
            auxiliar->inventario->semilla=4;
            auxiliar->inventario->piedra=5;
            auxiliar->inventario->madera=1;
            auxiliar->inventario->metal=4;
            auxiliar->inventario->papel=2;
        }
        if(auxiliar->id_casillas==14){
            auxiliar->recursoid=1;
            auxiliar->inventario->agua=1;
            auxiliar->inventario->semilla=4;
            auxiliar->inventario->piedra=1;
            auxiliar->inventario->madera=3;
            auxiliar->inventario->metal=4;
            auxiliar->inventario->papel=1;
            }
        if(auxiliar->id_casillas==16){
            auxiliar->recursoid=1;
            auxiliar->inventario->agua=0;
            auxiliar->inventario->semilla=1;
            auxiliar->inventario->piedra=1;
            auxiliar->inventario->madera=2;
            auxiliar->inventario->metal=2;
            auxiliar->inventario->papel=0;
        }
        if(auxiliar->id_casillas==19){
            auxiliar->recursoid=1;
            auxiliar->inventario->agua=2;
            auxiliar->inventario->semilla=5;
            auxiliar->inventario->piedra=6;
            auxiliar->inventario->madera=0;
            auxiliar->inventario->metal=2;
            auxiliar->inventario->papel=1;
        }
        if(auxiliar->id_casillas==21){
            auxiliar->recursoid=1;
            auxiliar->inventario->agua=5;
            auxiliar->inventario->semilla=2;
            auxiliar->inventario->piedra=1;
            auxiliar->inventario->madera=2;
            auxiliar->inventario->metal=1;
            auxiliar->inventario->papel=0;
        }
        if(auxiliar->id_casillas==24){
            auxiliar->recursoid=1;
            auxiliar->inventario->agua=1;
            auxiliar->inventario->semilla=2;
            auxiliar->inventario->piedra=1;
            auxiliar->inventario->madera=2;
            auxiliar->inventario->metal=1;
            auxiliar->inventario->papel=2;
        }
        auxiliar=auxiliar->prox;
    }
}

void PickUp(Casillas *&Tablero, Jugadores *&Jugador){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // IMPLEMENTACIÓN DE COLORES EN LA TERMINAL
    Casillas *auxiliar=Tablero;
    while(auxiliar!=NULL && auxiliar->id_casillas!=Jugador->posicion){
        auxiliar=auxiliar->prox;
    }

    if(auxiliar!=NULL && auxiliar->recursoid==1){
        Jugador->inventario->agua=Jugador->inventario->agua + auxiliar->inventario->agua;
        Jugador->inventario->madera=Jugador->inventario->madera + auxiliar->inventario->madera;
        Jugador->inventario->metal=Jugador->inventario->metal+auxiliar->inventario->metal;
        Jugador->inventario->papel=Jugador->inventario->papel+ auxiliar->inventario->papel;
        Jugador->inventario->piedra=Jugador->inventario->piedra+ auxiliar->inventario->piedra;
        Jugador->inventario->semilla =Jugador->inventario->semilla+ auxiliar->inventario->semilla;
        gotoxy(19,13);
        cout<<"Has caido en una casilla con recursos, ahora ";
        MostrarInventario(Jugador);
        }
}

void puntosnegativos(Jugadores *&Jugador){
    if(Jugador->pts<0){
        cout<<"Los puntos de "<<Jugador->nombre_jugador<<" no pueden disminuir mas"<<endl;
        Jugador->pts=0;
    }
    
}

void recursosnegativos(Jugadores *&Jugador){
    
    if(Jugador->inventario->agua<0){
        cout<<"El agua de "<<Jugador->nombre_jugador<<" no puede disminuir mas"<<endl;
        Jugador->inventario->agua=0;
    }
    if(Jugador->inventario->metal<0){
        cout<<"El metal de "<<Jugador->nombre_jugador<<" no puede disminuir mas"<<endl;
        Jugador->inventario->metal=0;
    }
    if(Jugador->inventario->semilla<0){
        cout<<"Las semillas de "<<Jugador->nombre_jugador<<" no puede disminuir mas"<<endl;
        Jugador->inventario->semilla=0;
    }
    if(Jugador->inventario->papel<0){
        cout<<"El papel de "<<Jugador->nombre_jugador<<" no puede disminuir mas"<<endl;
        Jugador->inventario->papel=0;
    }
    if(Jugador->inventario->madera<0){
        cout<<"La madera de "<<Jugador->nombre_jugador<<" no puede disminuir mas"<<endl;
        Jugador->inventario->madera=0;
    }
    if(Jugador->inventario->piedra<0){
        cout<<"La piedra de "<<Jugador->nombre_jugador<<" no puede disminuir mas"<<endl;
        Jugador->inventario->piedra=0;
    }
}

void AccionesC_Investigacion(Jugadores *&Jugador){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // IMPLEMENTACIÓN DE COLORES EN LA TERMINAL
    if(Jugador->posicion==3){
        int opcion1;
        system("cls");
        gotoxy(30,9);
        cout<<Jugador->nombre_jugador<<" has entrado en una zona de conservacion"<<endl;
        gotoxy(23,10);
        cout<<"Te encuentras ubicado en un claro del bosque, donde se tiene un";
        gotoxy(26,11);
        cout<<"amplio terreno donde trabajar, al girar a tu izquierda";
        gotoxy(25,12);
        cout<<"te encuentras con una bolsa de semillas y una regadera.";
        gotoxy(33,13);
        cout<<"Sobre esto hay un cartel que dice:";
        gotoxy(23,14);
        cout<<"[SI LLEGASTE A ESTA ZONA,POR FAVOR AYUDA A SEMBRAR ESTOS ARBOLES]"<<endl;
        gotoxy(46,15);
        cout<<"Que decidiras?"<<endl;
        gotoxy(1,17);
        cout<<"1.Reforestar el claro"<<endl;
        gotoxy(1,18);
        cout<<"2.Seguir de largo"<<endl;
        bool decision=true;
        while(decision==true){
            cin>>opcion1;
            if(opcion1==1){
                system("cls");
                Jugador->inventario->agua=Jugador->inventario->agua*2;
                Jugador->inventario->madera=Jugador->inventario->madera*2;
                Jugador->inventario->metal=Jugador->inventario->metal*2;
                Jugador->inventario->papel=Jugador->inventario->papel*2;
                Jugador->inventario->piedra=Jugador->inventario->piedra*2;
                Jugador->inventario->semilla =Jugador->inventario->semilla*2;
                gotoxy(1,7);
                cout<<"Has empezado con la labor de reforestar este claro,con ayuda de tu regadera y las semillas que ya estaban en el lugar comienzas a plantarlas"<<endl;
                gotoxy(1,8);
                cout<<"Despues de unos minutos de arduo trabajo, la totalidad de la zona se encuentra con nuevas semillas plantadas y regadas"<<endl;
                gotoxy(1,9);
                cout<<"Gracias a tu accion se lograra recuperar esta zona del bosque, ademas has ganado un x2 de todos tus recursos actuales"<<endl;
                gotoxy(38,10);
                cout<<"Has duplicado tus recursos, ahora ";
                MostrarInventario(Jugador);
                decision=false;
            }else if(opcion1<1 || opcion1>3){
                system("cls");
                gotoxy(30,20);
                color(hConsole,12);
                cout<< "Opcion Invalida" << endl;
                color(hConsole,15);
            }else{
                system("cls");
                cout<<"Seguiras de largo y continuaras tu camino,reflexiona lo importante que es tener arboles en nuestro ecosistema, recuerda que son los capaces de purificar el aire que respiramos y nutren de alimentos a diversas especies."<<endl;
                decision=false;
            }
        }
    }   
    if(Jugador->posicion==7){
        int opcion2;
        cout<<Jugador->nombre_jugador<<" has entrado en una zona de investigacion"<<endl;
        system("cls");
        gotoxy(1,1);
        cout<<"Al entrar en la ciudad encuentras una manifestacion pacifica en contra del uso de combustibles contaminantes,planteando la implementacion de combustibles no contaminantes. Se te acerca el lider de este grupo promocionando su idea y te pregunta "<<endl;
        gotoxy(1,1);
        cout<<" [DESEAS COLABORAR ECONOMICAMENTE PARA LA FABRICACION DE COMBUSTIBLES NO CONTAMINANTES]"<<endl;
        gotoxy(1,1);
        cout<<"Que decidiras?"<<endl;
        gotoxy(1,1);
        cout<<"1.Donar 5 puntos, y adicionalmente 2 aguas"<<endl;
        gotoxy(1,1);
        cout<<"2.Seguir con tu camino"<<endl;
        bool decision2=true;
        while(decision2==true){
            cin>>opcion2;
            if(opcion2==1){
                system("cls");
                Jugador->pts=Jugador->pts-5;
                Jugador->inventario->agua=Jugador->inventario->agua-2;
                Jugador->inventario->agua=Jugador->inventario->agua*2;
                Jugador->inventario->madera=Jugador->inventario->madera*2;
                Jugador->inventario->piedra=Jugador->inventario->piedra*2;
                Jugador->pts=Jugador->pts+25;
                gotoxy(1,6);
                cout<<"Aceptas la propuesta del lider, decides contribuir economicamente a su causa"<<endl;
                gotoxy(1,7);
                cout<<"Te enteras que gracias a tu colaboracion ya pueden terminar la produccion de su nuevo combustible no contaminante, hecho en base a productos naturales y cierto tipo de energia"<<endl;
                gotoxy(1,8);
                cout<<"Gracias a tu accion se logro avanzar en el desarrollo en contra de la contaminacion por C02, seras recompensado con 25 puntos y un x2 de  tus recursos [PIEDRA],[AGUA],[MADERA]"<<endl;
                gotoxy(1,9);
                cout<<Jugador->nombre_jugador<<" tus puntos ahora son: "<<Jugador->pts;
                gotoxy(38,10);
                cout<<"Has duplicado tus recursos, ahora ";
                MostrarInventario(Jugador);
                decision2=false;
            }else if(opcion2<1 || opcion2>3){
                system("cls");
                gotoxy(30,20);
                color(hConsole,12);
                cout<< "Opcion Invalida" << endl;
                color(hConsole,15);
            }else{
                system("cls");
                cout<<"Seguiras de largo, pero ten en cuenta que al no aportar seguiran produciendo y utilizando combustibles que poco a poco acabaran con nuestro ecosistema"<<endl;
                decision2=false;
            }
        }
        
    }

    if(Jugador->posicion==12){
        int opcion3;
        system("cls");
        gotoxy(1,1);
        cout<<Jugador->nombre_jugador<<" has entrado en una zona de investigacion"<<endl;
        gotoxy(1,1);
        cout<<"En tu camino por la tundra entras en un CIA(Centro de Investigacion Ambiental), donde te proponen invertir en un proyecto, ";
        gotoxy(1,1);
        cout<<"el cual se trata de una [ACADEMIA DE CUIDADO AMBIENTAL],donde ademas de cursar la carga academica corriente, se anadirian varios modulos con respecto al cuidado ambiental, tales como: "<<endl;
        gotoxy(1,1);
        cout<<"El reciclaje y sus beneficios, energias no contaminantes, produccion agricola sostenible, entre otros diversos temas."<<endl;
        gotoxy(1,1);
        cout<<"Que decidiras?"<<endl;
        gotoxy(1,1);
        cout<<"1.Donar 5 puntos, y  3 papeles para los libros"<<endl;
        gotoxy(1,1);
        cout<<"2.Seguir con tu camino"<<endl;
        bool decision3=true;
        while(decision3==true){
            cin>>opcion3;
            if(opcion3==1){
                system("cls");
                Jugador->pts=Jugador->pts-5;
                Jugador->inventario->papel=Jugador->inventario->papel-3;
                Jugador->pts=Jugador->pts*2;
                gotoxy(1,6);
                cout<<"Aceptas el proyecto, y donas lo necesario"<<endl;
                gotoxy(1,7);
                cout<<"Debido a tu solidaridad con este nuevo proyecto muchos ninos y adolescentes aprenderan sobre el tema y se podra tener un mejor futuro"<<endl;
                gotoxy(1,8);
                cout<<"Gracias a tu accion se logro progresar academicamente, seras recompensado con x2 en tus puntos "<<endl;
                gotoxy(1,9);
                cout<<Jugador->nombre_jugador<<" tus puntos ahora son: "<<Jugador->pts;
                decision3=false;
            }else if(opcion3<1 || opcion3>3){
                system("cls");
                gotoxy(30,20);
                color(hConsole,12);
                cout<< "Opcion Invalida" << endl;
                color(hConsole,15);
            }else{
                system("cls");
                cout<<"Seguiras de largo y continuaras tu camino,recuerda que es importante siempre ayudar y aportar conocimiento a los mas jovenes. El conocimiento es poder, y el poder se traduce en buenas acciones al medio ambiente"<<endl;
                decision3=false;
            }
        }
    }
    if(Jugador->posicion==18){  //YA TERMINÉ SU IMPRESIÓN 
        int opcion4;
        system("cls");
        gotoxy(12,14);
        cout<<Jugador->nombre_jugador<<" has entrado en una zona de conservacion"<<endl;
        gotoxy(23,16);
        cout<<"Al entrar en la playa te encuentras con un cumulo de desechos"; 
        gotoxy(17,17);
        cout<<"sobretodo de productos fabricados por plastico,podrias seguir tu camino o"; 
        gotoxy(28,18);
        cout<<"usando tus recursos podrias ingeniarte una solucion";
        gotoxy(15,19);
        cout<<"Si tuvieses 1 madera y 1 de metal podrias elaborar un [RECOLECTOR DE PAPELES] "<<endl;
        gotoxy(46,21);
        cout<<"Que decidiras?"<<endl;
        gotoxy(30,23);
        cout<<"1.Invertir tiempo y recursos en limpiar la zona"<<endl;
        gotoxy(44,24);
        cout<<"2.Seguir de largo"<<endl;
        bool decision4=true;
        while(decision4==true){
            cin>>opcion4;
            if(opcion4==1){
                system("cls");
                Jugador->inventario->madera=Jugador->inventario->madera-1;
                Jugador->inventario->metal=Jugador->inventario->metal-1;
                Jugador->inventario->agua=Jugador->inventario->agua*2;
                Jugador->inventario->madera=Jugador->inventario->madera*2;
                Jugador->inventario->metal=Jugador->inventario->metal*2;
                Jugador->inventario->papel=Jugador->inventario->papel*2;
                Jugador->inventario->piedra=Jugador->inventario->piedra*2;
                Jugador->inventario->semilla =Jugador->inventario->semilla*2;
                Jugador->pts=Jugador->pts+5;
                gotoxy(23,3);
                cout<<"Con tus recursos logras obtener un [RECOLECTOR DE PAPELES],con"; 
                gotoxy(28,4);
                cout<<"el cual empiezas a retirar los desechos de la playa";
                gotoxy(21,6);
                cout<<"Despues de un tiempo, la totalidad de la playa se encuentra limpia"<<endl;
                gotoxy(23,7);
                cout<<"Gracias a tu accion se logro salvar esta zona, has ganado un x2";
                gotoxy(12,8);
                cout<<"de todos tus recursos actuales y 5 puntos";
                gotoxy(23+5,9);
                cout<<Jugador->nombre_jugador<<" tus puntos ahora son: "<<Jugador->pts;
                gotoxy(38,10);
                cout<<"Has duplicado tus recursos, ahora";
                MostrarInventario(Jugador);
                decision4=false;
            }else if(opcion4<1 || opcion4>3){
                system("cls");
                gotoxy(30,20);
                color(hConsole,12);
                cout<< "Opcion Invalida" << endl;
                color(hConsole,15);
            }else{
                system("cls");
                gotoxy(23+5,20);
                cout<<"Seguiras de largo,pero recuerda que debido a la contaminacion";
                gotoxy(1,20);
                cout<<"por plasticos y desechos es que la vida maritima se encuentra en peligro,considera tus acciones."<<endl;
                decision4=false;
            }
        }
        
    }
    if(Jugador->posicion==22){
        int opcion5;
        system("cls");
        gotoxy(1,1);
        cout<<Jugador->nombre_jugador<<" has entrado en una zona de investigacion"<<endl;
        gotoxy(1,1);
        cout<<"Te contacta un cientifico, el cual te propone invertir en un refugio para la cria y cuidado de especies en peligro extincion, lo cual traeria enormes beneficios a los ecosistemas donde ya no se encuentran"<<endl;
        gotoxy(1,1);
        cout<<"Que decidiras?"<<endl;
        gotoxy(1,1);
        cout<<"1.Invertir 10 puntos, 1 agua,1 metal,1 madera en la construccion del refugio"<<endl;
        gotoxy(1,1);
        cout<<"2.Seguir de largo"<<endl;
        bool decision5=true;
        while(decision5==true){
            cin>>opcion5;
            if(opcion5==1){
                system("cls");
                Jugador->inventario->madera=Jugador->inventario->madera-1;
                Jugador->inventario->metal=Jugador->inventario->metal-1;
                Jugador->inventario->agua=Jugador->inventario->agua-1;
                Jugador->inventario->agua=Jugador->inventario->agua+2;
                Jugador->inventario->madera=Jugador->inventario->madera+2;
                Jugador->inventario->metal=Jugador->inventario->metal+2;
                Jugador->inventario->papel=Jugador->inventario->papel+2;
                Jugador->inventario->piedra=Jugador->inventario->piedra+2;
                Jugador->inventario->semilla =Jugador->inventario->semilla+2;
                Jugador->pts=Jugador->pts*4;
                gotoxy(1,1);
                cout<<"Con tus recursos logras construir [REFUGIO DE ESPECIES EN PELIGRO DE EXTINCION],con el cual especies como la nutria,el jaguar, el caiman podran vivir tranquilos"<<endl;
                gotoxy(1,1);
                cout<<"El cientifico te da las gracias por salvar a diversas especies"<<endl;
                gotoxy(1,1);
                cout<<"Gracias a tu accion se logro salvar esta zona, has ganado un x4 en tus puntos y un +3 en recursos"<<endl;
                gotoxy(1,1);
                cout<<Jugador->nombre_jugador<<" tus puntos ahora son: "<<Jugador->pts<<endl;
                gotoxy(1,1);
                cout<<"Han aumentado tus recursos, ahora ";
                MostrarInventario(Jugador);
                decision5=false;
            }else if(opcion5<1 || opcion5>3){
                system("cls");
                gotoxy(30,20);
                color(hConsole,12);
                cout<< "Opcion Invalida" << endl;
                color(hConsole,15);
            }else{
                system("cls");
                cout<<"Seguiras de largo,pero recuerda que debido a la contaminacion por plasticos y desechos es que la vida maritima se encuentra en peligro,considera tus acciones."<<endl;
                decision5=false;
            }
        }
    }
}

void Trivias(Jugadores *&Jugador){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // IMPLEMENTACIÓN DE COLORES EN LA TERMINAL
    int casilladeljugador;
    casilladeljugador=Jugador->posicion;
        // trivia pre boss es incendio forestal
        if(Jugador->posicion==4){
            system("cls");
            cout<<Jugador->nombre_jugador<< " ha caido en una TRIVIA,responda bien la siguiente situacion y se le asignaran recursos y puntos "<<endl;
            cout<<" Te estas adentrando al final del bosque, en lo que entras te encuentras con un arbol empezando a quemarse";
            cout<<",que crees que deberias hacer?"<<endl;
            cout<<"1.Ver como empieza un incendio"<<endl;
            cout<<"2.Intentar apagar la pequena llama con un poco de agua"<<endl;
            cout<<"3.Tomarle una foto y enviarla a redes sociales"<<endl;
            int opcion1;
            bool correcto=true;
            while(correcto==true){
                cin>>opcion1;
                if(opcion1==2){
                    system("cls");
                    cout<<"Felicidades "<<Jugador->nombre_jugador<<" tu respuesta fue correcta!"<<endl;
                    cout<<Jugador->nombre_jugador<<" gano 10 puntos y 5 semillas"<<endl;
                    Jugador->pts=Jugador->pts+10;
                    cout<<"Ahora tienes : "<<Jugador->pts<<" puntos"<<endl;
                    Jugador->inventario->semilla=Jugador->inventario->semilla+5;
                    MostrarInventario(Jugador);
                    correcto=false;
                }else if(opcion1<1 ||opcion1>3) {
                    cout<<"Opcion invalida, vuelva a intentarlo: "<<endl;
                }else{
                    system("cls");
                    cout<<"Respuesta incorrecta, ha perdido 2 semillas y 1 agua"<<endl;
                    Jugador->inventario->semilla=Jugador->inventario->semilla-2;
                    Jugador->inventario->agua=Jugador->inventario->agua-1;
                    MostrarInventario(Jugador);
                    correcto=false;

                }

            }

        }

        // trivia pre boss es contaminacion por co2
        if(Jugador->posicion==8){
            system("cls");
            cout<<Jugador->nombre_jugador<< " ha caido en una TRIVIA,responda bien la siguiente situacion y se le asignaran recursos y puntos "<<endl;
            cout<<" Estas caminando cerca de una  ciudad grande y notas que la calidad del aire es muy mala, ¿a que crees que se deba esto?"<<endl;
            cout<<"1.Contaminacion de CO2 producidas de fabricas, combustibles y transportes"<<endl;
            cout<<"2.La atmosfera se encuentra triste"<<endl;
            cout<<"3.El espacio esta generando calor que afecta directamente al aire que respiramos"<<endl;
            int opcion2;
            bool correcto2=true;
            while(correcto2==true){
                cin>>opcion2;
                if(opcion2==1){
                    system("cls");
                    cout<<"Felicidades "<<Jugador->nombre_jugador<<" tu respuesta fue correcta!"<<endl;
                    cout<<Jugador->nombre_jugador<<" gano 15 puntos,2 semillas,1 papel y 3 metales"<<endl;
                    Jugador->pts=Jugador->pts+15;
                    cout<<"Ahora tienes : "<<Jugador->pts<<" puntos"<<endl;
                    Jugador->inventario->semilla=Jugador->inventario->semilla+2;
                    Jugador->inventario->papel=Jugador->inventario->papel+1;
                    Jugador->inventario->metal=Jugador->inventario->metal+3;
                    MostrarInventario(Jugador);
                    correcto2=false;
                }else if(opcion2<1 ||opcion2>3) {
                    cout<<"Opcion invalida, vuelva a intentarlo: "<<endl;
                }else{
                    system("cls");
                    cout<<"Respuesta incorrecta, ha perdido 1 semilla, 1 metal y 5 puntos"<<endl;
                    Jugador->pts=Jugador->pts-5;
                    puntosnegativos(Jugador);
                    cout<<"Ahora tienes: "<<Jugador->pts<<endl;
                    Jugador->inventario->semilla=Jugador->inventario->semilla-2;
                    Jugador->inventario->agua=Jugador->inventario->agua-1;
                    recursosnegativos(Jugador);
                    MostrarInventario(Jugador);
                    correcto2=false;
                }
                }
        }
          // trivia pre boss es deshielo por el calentamiento global
        if(Jugador->posicion==13){
            system("cls");
            cout<<Jugador->nombre_jugador<< " ha caido en una TRIVIA,responda bien la siguiente situacion y se le asignaran recursos y puntos "<<endl;
            cout<<"Estás explorando una tundra ártica y te das cuenta de que el hielo se están derritiendo rápidamente debido al calentamiento global, que opcion es mas adecuada para resolver este caso?"<<endl;
            cout<<"1.Encender un aire acondicionado en la tundra"<<endl;
            cout<<"2.Hacer edificios para aprovechar el terreno"<<endl;
            cout<<"3.Reducir el uso de combustibles fósiles y promover fuentes de energía renovable"<<endl;
            int opcion3;
            bool correcto3=true;
            while(correcto3==true){
                cin>>opcion3;
                if(opcion3==3){
                    system("cls");
                    cout<<"Felicidades "<<Jugador->nombre_jugador<<" tu respuesta fue correcta!"<<endl;
                    cout<<Jugador->nombre_jugador<<" gano 10 puntos,3 maderas,2 aguas y 4 piedras"<<endl;
                    Jugador->pts=Jugador->pts+10;
                    cout<<"Ahora tienes : "<<Jugador->pts<<" puntos"<<endl;
                    Jugador->inventario->agua=Jugador->inventario->agua+2;
                    Jugador->inventario->piedra=Jugador->inventario->piedra+4;
                    Jugador->inventario->madera=Jugador->inventario->madera+3;
                    MostrarInventario(Jugador);
                    correcto3=false;
                }else if(opcion3<1 ||opcion3>3) {
                    cout<<"Opcion invalida, vuelva a intentarlo: "<<endl;
                }else{
                    system("cls");
                    cout<<"Respuesta incorrecta, ha perdido 3 piedras y 5 puntos"<<endl;
                    Jugador->pts=Jugador->pts-5;
                    puntosnegativos(Jugador);
                    cout<<"Ahora tienes: "<<Jugador->pts<<endl;
                    Jugador->inventario->piedra=Jugador->inventario->piedra-3;
                    recursosnegativos(Jugador);
                    MostrarInventario(Jugador);
                    correcto3=false;
                }
                }
        }
        if(Jugador->posicion==17){
            // trivia pre boss contaminacion de las aguas
            system("cls");
            cout<<Jugador->nombre_jugador<< " ha caido en una TRIVIA,responda bien la siguiente situacion y se le asignaran recursos y puntos "<<endl;
            cout<<"Te encuentras en una bella costa paradisiaca, donde se realizan diversas actividades recreativas,pero tambien donde se encuentras muchos residuos toxicos para el ecosistema maritimo, que haras para resolver esto?"<<endl;
            cout<<"1.No sumergirme al agua "<<endl;
            cout<<"2.Implementar programas de limpieza y recogida de residuos en la costa y en áreas submarinas."<<endl;
            cout<<"3.Limpiar el mar con una cubeta"<<endl;
            int opcion4;
            bool correcto4=true;
            while(correcto4==true){
                cin>>opcion4;
                if(opcion4==2){
                    system("cls");
                    cout<<"Felicidades "<<Jugador->nombre_jugador<<" tu respuesta fue correcta!"<<endl;
                    cout<<Jugador->nombre_jugador<<" gano 20 puntos,5 aguas, y 2 piedras"<<endl;
                    Jugador->pts=Jugador->pts+20;
                    cout<<"Ahora tienes : "<<Jugador->pts<<" puntos"<<endl;
                    Jugador->inventario->agua=Jugador->inventario->agua+5;
                    Jugador->inventario->piedra=Jugador->inventario->piedra+2;
                    MostrarInventario(Jugador);
                    correcto4=false;
                }else if(opcion4<1 ||opcion4>3) {
                    cout<<"Opcion invalida, vuelva a intentarlo: "<<endl;
                }else{
                    system("cls");
                    cout<<"Respuesta incorrecta, ha perdido 2 aguas y 10 puntos"<<endl;
                    Jugador->pts=Jugador->pts-10;
                    puntosnegativos(Jugador);
                    cout<<"Ahora tienes: "<<Jugador->pts<<endl;
                    Jugador->inventario->agua=Jugador->inventario->agua-2;
                    recursosnegativos(Jugador);
                    MostrarInventario(Jugador);
                    correcto4=false;
                }
                }

        }

        if(Jugador->posicion==23){
            //trivia pre boss perdida desfauna y flora en la sabana
            system("cls");
            cout<<Jugador->nombre_jugador<< " ha caido en una TRIVIA,responda bien la siguiente situacion y se le asignaran recursos y puntos "<<endl;
            cout<<"LLegaste a una zona nueva en la sabana, segun registros anteriores era una zona con mucha fauna y flora, pero en la actualidad no se encuentra asi,a que se debe?"<<endl;
            cout<<"1.A la inflacion "<<endl;
            cout<<"2.Omar"<<endl;
            cout<<"3.Caza furtiva y deforestacion para hallar especies y terrenos"<<endl;
            int opcion5;
            bool correcto5=true;
            while(correcto5==true){
                cin>>opcion5;
                if(opcion5==3){
                    system("cls");
                    cout<<"Felicidades "<<Jugador->nombre_jugador<<" tu respuesta fue correcta!"<<endl;
                    cout<<Jugador->nombre_jugador<<" gano 10 puntos,10 maderas,2 semillas y 3 piedras"<<endl;
                    Jugador->pts=Jugador->pts+10;
                    cout<<"Ahora tienes : "<<Jugador->pts<<" puntos"<<endl;
                    Jugador->inventario->semilla=Jugador->inventario->semilla+2;
                    Jugador->inventario->madera=Jugador->inventario->madera+10;
                    Jugador->inventario->piedra=Jugador->inventario->piedra+3;
                    MostrarInventario(Jugador);
                    correcto5=false;
                }else if(opcion5<1 ||opcion5>3) {
                    cout<<"Opcion invalida, vuelva a intentarlo: "<<endl;
                }else{
                    system("cls");
                    cout<<"Respuesta incorrecta, ha perdido 2 aguas y 10 puntos"<<endl;
                    Jugador->pts=Jugador->pts-10; 
                    puntosnegativos(Jugador);
                    cout<<"Ahora tienes: "<<Jugador->pts<<endl;
                    Jugador->inventario->agua=Jugador->inventario->agua-2;
                    recursosnegativos(Jugador);
                    MostrarInventario(Jugador);
                    correcto5=false;
                }
                }
        }
    
}

//procedimientos para verificar si hay cantidad de recursos necesarios para los jefes

void bonificacionequipo(Jugadores *&Jugador){
    if(Jugador->equipo==1){
        cout<<Jugador->nombre_jugador<<" supero el reto, y al ser del [EQUIPO ROJO] obtuvo un X4 de sus puntos actuales"<<endl;
        Jugador->pts=Jugador->pts*4;
        cout<<Jugador->nombre_jugador<<" tus puntos ahora son: "<<Jugador->pts;

    }//equipo rojo
    if(Jugador->equipo==2){
        cout<<Jugador->nombre_jugador<<" supero el reto, y al ser del [EQUIPO AZUL] obtuvo 10 aguas y X3 de sus puntos actuales"<<endl;
        Jugador->pts=Jugador->pts*3;
        cout<<Jugador->nombre_jugador<<" tus puntos ahora son: "<<Jugador->pts<<endl;
        Jugador->inventario->agua=Jugador->inventario->agua+10;
        MostrarInventario(Jugador);

    }//equipo azul
    if(Jugador->equipo==3){
        cout<<Jugador->nombre_jugador<<" supero el reto, y al ser del [EQUIPO VERDE] obtuvo un X2 de sus puntos actuales y un X2 en los recursos [PIEDRA],[METAL],[SEMILLAS],[MADERA]"<<endl;
        Jugador->pts=Jugador->pts*2;
        cout<<Jugador->nombre_jugador<<" tus puntos ahora son: "<<Jugador->pts<<endl;
        Jugador->inventario->piedra=Jugador->inventario->piedra*2;
        Jugador->inventario->semilla=Jugador->inventario->semilla*2;
        Jugador->inventario->metal=Jugador->inventario->metal*2;
        Jugador->inventario->madera=Jugador->inventario->madera*2;
        MostrarInventario(Jugador);

    }//equipo verde

}

bool verificaragua(Jugadores *&Jugador,int cantidadnecesaria){
    bool sihay=false;
    if(Jugador->inventario->agua>=cantidadnecesaria){
        cout<<Jugador->nombre_jugador<<" posee los recursos necesarios"<<endl;
        sihay=true;
        return true;
    }else{
        cout<<Jugador->nombre_jugador<<" no posee los recursos necesarios"<<endl;
        return false;
    }
}

bool verificarmetal(Jugadores *&Jugador,int cantidadnecesaria){
    bool sihay=false;
    if(Jugador->inventario->metal>=cantidadnecesaria){
        cout<<Jugador->nombre_jugador<<" posee los recursos necesarios"<<endl;
        sihay=true;
        return true;
    }else{
        cout<<Jugador->nombre_jugador<<" no posee los recursos necesarios"<<endl;
        return false;
    }
}

bool verificarmadera(Jugadores *&Jugador,int cantidadnecesaria){
    bool sihay=false;
    if(Jugador->inventario->madera>=cantidadnecesaria){
        cout<<Jugador->nombre_jugador<<" posee los recursos necesarios"<<endl;
        sihay=true;
        return true;
    }else{
        cout<<Jugador->nombre_jugador<<" no posee los recursos necesarios"<<endl;
        return false;
    }
}

bool verificarpiedra(Jugadores *&Jugador,int cantidadnecesaria){
    bool sihay=false;
    if(Jugador->inventario->madera>=cantidadnecesaria){
        cout<<Jugador->nombre_jugador<<" posee los recursos necesarios"<<endl;
        sihay=true;
        return true;
    }else{
        cout<<Jugador->nombre_jugador<<" no posee los recursos necesarios"<<endl;
        return false;
    }
}

bool verificarpapel(Jugadores *&Jugador,int cantidadnecesaria){
    bool sihay=false;
    if(Jugador->inventario->papel>=cantidadnecesaria){
        cout<<Jugador->nombre_jugador<<" posee los recursos necesarios"<<endl;
        sihay=true;
        return true;
    }else{
        cout<<Jugador->nombre_jugador<<" no posee los recursos necesarios"<<endl;
        return false;
    }
}

bool verificarsemillas(Jugadores *&Jugador,int cantidadnecesaria){
    bool sihay=false;
    if(Jugador->inventario->semilla>=cantidadnecesaria){
        cout<<Jugador->nombre_jugador<<" posee los recursos necesarios"<<endl;
        sihay=true;
        return true;
    }else{
        cout<<Jugador->nombre_jugador<<" no posee los recursos necesarios"<<endl;
        return false;
    }
}

//CICLOS MENU/JUEGO/RONDA/TURNO

void Jefes(Jugadores *&Jugador){
    if(Jugador->posicion==5){
        //boss jefe final
        system("cls");
        int opcion1; 
        cout<<Jugador->nombre_jugador<<" SE ENCUENTRA EN EL JEFE DE LA ZONA [BOSQUE]"<<endl;
        cout<<"----------------------------------------------"<<endl;
        cout<<"Te encuentras al final del bosque, sientes la vista pesada y te empieza a costar respirar, al seguir caminando te encuentras"<<endl;
        cout<<" con un escenario desolador, un [INCENDIO FORESTAL],que esta acabando con la zona.Necesitas tomar una accion inmediata que pueda ayudar en la zona con los recursos necesarios"<<endl;
        cout<<"----------------------------------------------"<<endl;
        cout<<"Se necesitan 2 maderas y 2 metales para construir [BARRERAS IGNIFUGAS]"<<endl;
        cout<<"Se necesita 2 aguas para extingir las llamas"<<endl;
        cout<<"Se necesita 2 piedras y 1 madera para construir una [PALA]"<<endl;
        cout<<"Quieres invertir tus recursos en la solucion?"<<endl;
        cout<<"1. Si"<<endl;
        cout<<"2. No"<<endl;
        bool aceptar=true;
        while(aceptar==true){
                cin>>opcion1;
                if(opcion1==1){
                    bool nocuenta=false;
                    if(verificaragua(Jugador,2)==true){
                        Jugador->inventario->agua=Jugador->inventario->agua-2;
                        cout<<Jugador->nombre_jugador<<" ha donado 2 aguas"<<endl;
                    }else{
                        cout<<"No cuenta con los recursos necesarios"<<endl;
                        nocuenta=true;
                    }
                    if(verificarmadera(Jugador,3)==true){
                        Jugador->inventario->madera=Jugador->inventario->madera-3;
                        cout<<Jugador->nombre_jugador<<" ha donado 3 maderas"<<endl;
                    }else{
                        cout<<"No cuenta con los recursos necesarios"<<endl;
                        nocuenta=true;
                    }
                    if(verificarmetal(Jugador,2)==true){
                        Jugador->inventario->metal=Jugador->inventario->metal-2;
                        cout<<Jugador->nombre_jugador<<" ha donado 2 metales"<<endl;
                    }else{
                        cout<<"No cuenta con los recursos necesarios"<<endl;
                        nocuenta=true;
                    }
                    if(verificarpiedra(Jugador,2)==true){
                        Jugador->inventario->piedra=Jugador->inventario->piedra-2;
                        cout<<Jugador->nombre_jugador<<" ha donado 2 piedras"<<endl;
                    }else{
                        cout<<"No cuenta con los recursos necesarios"<<endl;
                        nocuenta=true;
                    }

                    if(nocuenta==true){
                        cout<<"El jugador "<<Jugador->nombre_jugador<<" no cuenta con uno de los recursos,por lo tanto no podra ayudar";
                        aceptar=false;
                    }

                    if(nocuenta==false){
                        cout<<"Gracias a la ayuda de "<<Jugador->nombre_jugador<<" se logro calmar el incendio y poner a salvo la fauna del bosque"<<endl;
                        cout<<"Despues de extinguir el incendio, se uso la [PALA] para cavar y sembrar las semillas de arbol"<<endl;
                        bonificacionequipo(Jugador);
                        aceptar=false;
                    }

                    

                }else if(opcion1<1 ||opcion1>2) {
                    cout<<"Opcion invalida, vuelva a intentarlo: "<<endl;
                }else{
                    cout<<Jugador->nombre_jugador<<" decidio no donar sus recursos"<<endl;
                    cout<<"A raiz de que el jugador "<<Jugador->nombre_jugador<<" no ayudo al bosque, el perdio su trofeo [APAGUE EL FUEGO], su bonificacion de equipo, 2 semillas y 1 agua";
                    Jugador->inventario->semilla=Jugador->inventario->semilla-2;
                    Jugador->inventario->agua=Jugador->inventario->agua-1;
                    MostrarInventario(Jugador);
                    aceptar=false;
                }
            }
        
    }

    
    if(Jugador->posicion==10){
        //boss jefe final
        system("cls");
        int opcion2; 
        cout<<Jugador->nombre_jugador<<" SE ENCUENTRA EN EL JEFE DE LA ZONA [CIUDAD]"<<endl;
        cout<<"----------------------------------------------"<<endl;
        cout<<"Notas que al proseguir caminando por la ciudad el aire se empieza a espesar, el ambiente se vuelve tenso y tu vista empieza a ser cegada por el humo. "<<endl;
        cout<<"El jugador "<<Jugador->nombre_jugador<<" logra abrir los ojos y al visualizar encima de el se encuentra con una nube gigante producida por la contaminacion de C02 de las empresas contaminantes y la autopista "<<endl;
        cout<<"Necesitas tomar una accion decisiva para neutralizar la nube y detener la contaminacion del aire en la ciudad."<<endl;
        cout<<"Utilizando los siguientes recursos podrias superar este problema: "<<endl;
        cout<<"----------------------------------------------"<<endl;
        cout<<"Se necesitan 3 metales y 1 papel para construir [ASPIRADORA DE CO2]"<<endl;
        cout<<"Se necesita 1 agua y 2 semillas para plantar nuevos arboles en la zona y mantenerla a salvo"<<endl;
        cout<<"Quieres invertir tus recursos en la solucion?"<<endl;
        cout<<"1. Si"<<endl;
        cout<<"2. No"<<endl;
        bool aceptar2=true;
        while(aceptar2==true){
                cin>>opcion2;
                if(opcion2==1){
                    bool nocuenta2=false;
                    if(verificarmetal(Jugador,3)==true){
                        Jugador->inventario->metal=Jugador->inventario->metal-3;
                        cout<<Jugador->nombre_jugador<<" ha donado 3 metales"<<endl;
                    }else{
                        cout<<"No cuenta con los recursos necesarios"<<endl;
                        nocuenta2=true;
                    }
                    if(verificarpapel(Jugador,1)==true){
                        Jugador->inventario->papel=Jugador->inventario->papel-1;
                        cout<<Jugador->nombre_jugador<<" ha donado 1 papel"<<endl;
                    }else{
                        cout<<"No cuenta con los recursos necesarios"<<endl;
                        nocuenta2=true;
                    }
                    if(verificaragua(Jugador,1)==true){
                        Jugador->inventario->agua=Jugador->inventario->agua-1;
                        cout<<Jugador->nombre_jugador<<" ha donado 1 agua"<<endl;
                    }else{
                        cout<<"No cuenta con los recursos necesarios"<<endl;
                        nocuenta2=true;
                    }
                    if(verificarsemillas(Jugador,2)==true){
                        Jugador->inventario->semilla=Jugador->inventario->semilla-2;
                        cout<<Jugador->nombre_jugador<<" ha donado 2 semillas"<<endl;
                    }else{
                        cout<<"No cuenta con los recursos necesarios"<<endl;
                        nocuenta2=true;
                    }

                    if(nocuenta2==true){
                        cout<<"El jugador "<<Jugador->nombre_jugador<<" no cuenta con uno de los recursos,por lo tanto no podra ayudar";
                        aceptar2=false;
                    }

                    if(nocuenta2==false){
                        cout<<"Gracias a la ayuda de "<<Jugador->nombre_jugador<<" se logro eliminar la nube que estaba contaminando y poner a salvo la ciudad"<<endl;
                        cout<<"Ya se puede respirar con normalidad"<<endl;
                        bonificacionequipo(Jugador);
                        aceptar2=false;
                    }

                    

                }else if(opcion2<1 ||opcion2>2) {
                    cout<<"Opcion invalida, vuelva a intentarlo: "<<endl;
                }else{
                    cout<<Jugador->nombre_jugador<<" decidio no donar sus recursos"<<endl;
                    cout<<"A raiz de que el jugador "<<Jugador->nombre_jugador<<" no ayudo a la ciudad, el perdio su trofeo [SUAVIZADO DE NUBES], su bonificacion de equipo y 2 piedras";
                    Jugador->inventario->piedra=Jugador->inventario->piedra-2;
                    MostrarInventario(Jugador);
                    aceptar2=false;
                }
            }
    }
    if(Jugador->posicion==15){
        system("cls");
        int opcion3; 
        cout<<Jugador->nombre_jugador<<" SE ENCUENTRA EN EL JEFE DE LA ZONA [TUNDRA]"<<endl;
        cout<<"----------------------------------------------"<<endl;
        cout<<"Te encuentras llegando al final de la tundra, donde deberias sentir un frio atroz,sin embargo cuando estas a punto de salir sientes un calor poco comun,al desviar tu vista hacia abajo te percatas de que "<<endl;
        cout<<"el hielo y permafrost se encuentra en su mayoria derretido y en poca densidad, esto es debido al calentamiento global producido por acciones humanas. "<<endl;
        cout<<"Necesitas tomar accion en este caso para detener la perdida de hielo en la zona y evitar consecuencias mayores."<<endl;
        cout<<"Utilizando los siguientes recursos solucionarias esta situacion: "<<endl;
        cout<<"----------------------------------------------"<<endl;
        cout<<"Se necesitan 2 madera,1 metal y 2 agua para construir [CONGELADOR DE AGUA] para ayudar a enfriar la zona"<<endl;
        cout<<"Quieres invertir tus recursos en la solucion?"<<endl;
        cout<<"1. Si"<<endl;
        cout<<"2. No"<<endl;
        bool aceptar3=true;
        while(aceptar3==true){
                cin>>opcion3;
                if(opcion3==1){
                    bool nocuenta3=false;
                    if(verificarmetal(Jugador,1)==true){
                        Jugador->inventario->metal=Jugador->inventario->metal-1;
                        cout<<Jugador->nombre_jugador<<" ha donado 1 metal"<<endl;
                    }else{
                        cout<<"No cuenta con los recursos necesarios"<<endl;
                        nocuenta3=true;
                    }
                    if(verificaragua(Jugador,2)==true){
                        Jugador->inventario->agua=Jugador->inventario->agua-2;
                        cout<<Jugador->nombre_jugador<<" ha donado 2 aguas"<<endl;
                    }else{
                        cout<<"No cuenta con los recursos necesarios"<<endl;
                        nocuenta3=true;
                    }
                    if(verificarmadera(Jugador,2)==true){
                        Jugador->inventario->madera=Jugador->inventario->madera-2;
                        cout<<Jugador->nombre_jugador<<" ha donado 2 madera"<<endl;
                    }else{
                        cout<<"No cuenta con los recursos necesarios"<<endl;
                        nocuenta3=true;
                    }

                    if(nocuenta3==true){
                        cout<<"El jugador "<<Jugador->nombre_jugador<<" no cuenta con uno de los recursos,por lo tanto no podra ayudar";
                        aceptar3=false;
                    }

                    if(nocuenta3==false){
                        cout<<"Gracias a la ayuda de "<<Jugador->nombre_jugador<<" se logro enfriar la tundra y recuperar su hielo"<<endl;
                        cout<<"El frio volvio a ser el habitual en este ecosistema"<<endl;
                        bonificacionequipo(Jugador);
                        aceptar3=false;
                    }

                    

                }else if(opcion3<1 ||opcion3>2) {
                    cout<<"Opcion invalida, vuelva a intentarlo: "<<endl;
                }else{
                    cout<<Jugador->nombre_jugador<<" decidio no donar sus recursos"<<endl;
                    cout<<"A raiz de que el jugador "<<Jugador->nombre_jugador<<" no ayudo a la tundra, el perdio su trofeo [FRIO COMO PINGUINO], su bonificacion de equipo y 10 puntos";
                    Jugador->pts=Jugador->pts-10;
                    puntosnegativos(Jugador);
                    aceptar3=false;
                }
            }
    }
    if(Jugador->posicion==20){
        system("cls");
        int opcion4; 
        cout<<Jugador->nombre_jugador<<" SE ENCUENTRA EN EL JEFE DE LA ZONA [MARITIMA]"<<endl;
        cout<<"----------------------------------------------"<<endl;
        cout<<"Te encuentras saliendo del profundo y lejano mar, donde a poca distancia ves tierra firme, pero un fuerte movimiento te despierta,te das cuenta que tu barco se ha detenido porque te encuentras atrapado entre basura y residuos"<<endl;
        cout<<".La contaminacion por plasticos,petroleo y basura ha llegado a un punto critico. "<<endl;
        cout<<"Necesitas tomar accion en este caso para detener la perdida de flora y fauna marina"<<endl;
        cout<<"Utilizando los siguientes recursos solucionarias esta situacion: "<<endl;
        cout<<"----------------------------------------------"<<endl;
        cout<<"Se necesitan 2 semillas y 2 maderas para construir [VIVERO ACUATICO] para ayudar a enfriar la zona"<<endl;
        cout<<"Quieres invertir tus recursos en la solucion?"<<endl;
        cout<<"1. Si"<<endl;
        cout<<"2. No"<<endl;
        bool aceptar4=true;
        while(aceptar4==true){
                cin>>opcion4;
                if(opcion4==1){
                    bool nocuenta4=false;
                    if(verificarsemillas(Jugador,2)==true){
                        Jugador->inventario->semilla=Jugador->inventario->semilla-2;
                        cout<<Jugador->nombre_jugador<<" ha donado 1 metal"<<endl;
                    }else{
                        cout<<"No cuenta con los recursos necesarios"<<endl;
                        nocuenta4=true;
                    }
                    if(verificarmadera(Jugador,2)==true){
                        Jugador->inventario->madera=Jugador->inventario->madera-2;
                        cout<<Jugador->nombre_jugador<<" ha donado 2 madera"<<endl;
                    }else{
                        cout<<"No cuenta con los recursos necesarios"<<endl;
                        nocuenta4=true;
                    }
                    if(nocuenta4==true){
                        cout<<"El jugador "<<Jugador->nombre_jugador<<" no cuenta con uno de los recursos,por lo tanto no podra ayudar";
                        aceptar4=false;
                    }

                    if(nocuenta4==false){
                        cout<<"Gracias a la ayuda de "<<Jugador->nombre_jugador<<" se logro limpiar el mar con ayuda del vivero limpiador y volverlo a su estado natural"<<endl;
                        cout<<"El mar volvio a su color habitual"<<endl;
                        bonificacionequipo(Jugador);
                        aceptar4=false;
                    }

                    

                }else if(opcion4<1 ||opcion4>2) {
                    cout<<"Opcion invalida, vuelva a intentarlo: "<<endl;
                }else{
                    cout<<Jugador->nombre_jugador<<" decidio no donar sus recursos"<<endl;
                    cout<<"A raiz de que el jugador "<<Jugador->nombre_jugador<<" no ayudo al espacio maritimo, perdio su trofeo [TRAPEANDO EL MAR], su bonificacion de equipo y 1 papel";
                    Jugador->inventario->papel=Jugador->inventario->papel-1;
                    puntosnegativos(Jugador);
                    aceptar4=false;
                }
            }
    }

    if(Jugador->posicion==25){
        system("cls");
        int opcion5; 
        cout<<Jugador->nombre_jugador<<" SE ENCUENTRA EN EL JEFE DE LA ZONA [SABANA]"<<endl;
        cout<<"----------------------------------------------"<<endl;
        cout<<"En una ultima parada,te encuentras paseando por la sabana, donde te percatas de la poca fauna que hay en el lugar."<<endl;
        cout<<"Despues de un breve recorrido te encuentras a la distancia un grupo de cazadores,los cuales estan acabando con el habitat y las especies de la sabana "<<endl;
        cout<<"Necesitas tomar accion en este caso para detener el deterioro de este ecosistema"<<endl;
        cout<<"Utilizando los siguientes recursos solucionarias esta situacion: "<<endl;
        cout<<"----------------------------------------------"<<endl;
        cout<<"Se necesitan 4 metales,2 maderas,1 agua,2 semillas para construir [REFUGIO DE LA VIDA SALVAJE] para ayudar a enfriar la zona"<<endl;
        cout<<"Quieres invertir tus recursos en la solucion?"<<endl;
        cout<<"1. Si"<<endl;
        cout<<"2. No"<<endl;
        bool aceptar5=true;
        while(aceptar5==true){
                cin>>opcion5;
                if(opcion5==1){
                    bool nocuenta5=false;
                    if(verificarsemillas(Jugador,2)==true){
                        Jugador->inventario->semilla=Jugador->inventario->semilla-2;
                        cout<<Jugador->nombre_jugador<<" ha donado 1 metal"<<endl;
                    }else{
                        cout<<"No cuenta con los recursos necesarios"<<endl;
                        nocuenta5=true;
                    }
                    if(verificarmadera(Jugador,2)==true){
                        Jugador->inventario->madera=Jugador->inventario->madera-2;
                        cout<<Jugador->nombre_jugador<<" ha donado 2 madera"<<endl;
                    }else{
                        cout<<"No cuenta con los recursos necesarios"<<endl;
                        nocuenta5=true;
                    }
                    if(verificarmetal(Jugador,4)==true){
                        Jugador->inventario->metal=Jugador->inventario->metal-4;
                        cout<<Jugador->nombre_jugador<<" ha donado 4 metales"<<endl;
                    }else{
                        cout<<"No cuenta con los recursos necesarios"<<endl;
                        nocuenta5=true;
                        }
                    if(verificaragua(Jugador,1)==true){
                        Jugador->inventario->agua=Jugador->inventario->agua-1;
                        cout<<Jugador->nombre_jugador<<" ha donado 1 metales"<<endl;
                        }else{
                            cout<<"No cuenta con los recursos necesarios"<<endl;
                            nocuenta5=true;
                        }

                        if(nocuenta5==true){
                            cout<<"El jugador "<<Jugador->nombre_jugador<<" no cuenta con uno de los recursos,por lo tanto no podra ayudar";
                            aceptar5=false;
                        }

                        if(nocuenta5==false){
                            cout<<"Gracias a la ayuda de "<<Jugador->nombre_jugador<<" se logro salvar las especies restantes,conservando su vida y procurando su desarollo gracias al refugio"<<endl;
                            cout<<"Los cazadores abandonaron la zona luego de esto"<<endl;
                            bonificacionequipo(Jugador);
                            aceptar5=false;
                    }
                }else if(opcion5<1 ||opcion5>2) {
                    cout<<"Opcion invalida, vuelva a intentarlo: "<<endl;
                }else{
                    cout<<Jugador->nombre_jugador<<" decidio no donar sus recursos"<<endl;
                    cout<<"A raiz de que el jugador "<<Jugador->nombre_jugador<<" no ayudo a la sabana, perdio su trofeo [MASCOTAS], su bonificacion de equipo y 20 puntos";
                    Jugador->pts=Jugador->pts-20;
                    puntosnegativos(Jugador);
                    aceptar5=false;
                }
            }
    }
}

void mover_jugador(Jugadores *&JugadorInicial, Casillas *& Tablero){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // IMPLEMENTACIÓN DE COLORES EN LA TERMINAL
    Jugadores *Jugador = JugadorInicial;
    int opcion;
    
    bool valido;
    valido=false;
    while(valido==false){
            system("cls");
            mostrartablero(Tablero);
            MostrarJugadores(JugadorInicial);
            gotoxy(21,18);
            cout<< "''"<<Jugador->nombre_jugador << "'', Que opcion deseas realizar?";
            gotoxy(18,20);
            cout<<"0- Para permanecer en la casilla actual";
            gotoxy(18,21);
            cout<<"1- Para moverte una casilla hacia adelante";
            gotoxy(24,22);
            cout<<"2- Para abrir tu inventario" << endl;
            gotoxy(39,24);
            cin>>opcion;
            if (opcion == 1) {
                if (Jugador->ubicacion_casilla!=NULL) {
                    Jugador->ubicacion_casilla=Jugador->ubicacion_casilla->prox;
                    Jugador->posicion=Jugador->ubicacion_casilla->id_casillas;
                    cout<<Jugador->nombre_jugador<<" del equipo "<<Jugador->nombre_equipo << " se movio a la casilla "<<Jugador->posicion<<endl;
                    system("cls");
                    PickUp(Tablero,Jugador);
                    Trivias(Jugador);
                    Jefes(Jugador);
                    AccionesC_Investigacion(Jugador);
                    valido=true;
                } else {
                    cout<<Jugador->nombre_jugador<<" ha llegado al final del tablero"<<endl;
                    valido=true;
                }
            }

            if(opcion==0){
                gotoxy(21,26);
                cout<< Jugador->nombre_jugador<<" No ha realizado movimiento..."<<endl;
                valido=true;
            }
            if(opcion==2){
                system("cls");
                MostrarInventario(Jugador);
                valido=false;
            }
            if(opcion<0 || opcion>2){
                system("cls");
                gotoxy(30,20);
                color(hConsole,12);
                cout<< "Opcion Invalida" << endl;
                valido=false;
                color(hConsole,15);
            }

        system("pause");  // Pausa después de cada turno para que el usuario vea el resultado
        mostrartablero(Tablero);
    }
}

void Turno(Casillas *&Tablero, Jugadores *&jugador, bool &fin_partida) {
    mover_jugador(jugador, Tablero);
    if (jugador->posicion == 25) {
        cout << "FELICIDADES " << jugador->nombre_jugador << " has llegado al final del juego, sigue cuidando el ambiente y aprendiendo de él!" << endl;
        fin_partida = true;  
        system("pause");
    }
}

void Ronda(Casillas *&Tablero, Jugadores *&lista_jugadores, bool &fin_partida) {
    Jugadores *auxiliar_jugadores = lista_jugadores;
    while (auxiliar_jugadores != NULL && !fin_partida) {
        Turno(Tablero, auxiliar_jugadores, fin_partida);
        auxiliar_jugadores = auxiliar_jugadores->prox_jugador; 
    }
}

void Partida(Casillas *&Tablero, Jugadores *&lista_jugadores) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // IMPLEMENTACIÓN DE COLORES EN LA TERMINAL
    bool fin_partida = false;
    bool cantidadvalida = false;
    int cantidad_jugadores;
    system("cls");
    mostrarCursor();
    while (!cantidadvalida) {
        gotoxy(20,15);
        cout << "Ingrese la cantidad de jugadores de la partida: ";
        cin >> cantidad_jugadores;
        if (cantidad_jugadores <= 0 || cantidad_jugadores > 3) {
            cout << "La cantidad máxima de jugadores es de 3, intente de nuevo" << endl;
        } else {
            cantidadvalida = true;
        }
    }
    system("cls");
    CrearListadeJugadores(lista_jugadores, Tablero, cantidad_jugadores);

    int ronda_contador = 1;
    
    do {
        system("cls");
        gotoxy(30,15);
        color(hConsole,12);
        cout << "INICIO DE LA RONDA: " << ronda_contador;
        gotoxy(30,17);
        cout << "   BUENA SUERTE" << endl;
        delay(2);
        color(hConsole,15);
        Ronda(Tablero, lista_jugadores, fin_partida);
        
        if (fin_partida) {
            system("cls");
            color(hConsole,14);
            gotoxy(30,15);
            cout << "LA PARTIDA HA FINALIZADO";
            gotoxy(30,17);
            cout << "  GRACIAS POR JUGAR ;)";
            delay(3);
        }
        
        int respuesta;
        gotoxy(25,18);
        cout << "Desea continuar la partida?" << endl;
        gotoxy(36,20);
        cout << "1. Si" << endl;
        gotoxy(36,21);
        cout << "2. No" << endl;
        gotoxy(36,23);
        cin >> respuesta;
        if (respuesta == 1) {
            fin_partida = false;
        } else if (respuesta == 2) {
            system("cls");
            color(hConsole,14);
            gotoxy(30,15);
            cout << "LA PARTIDA HA FINALIZADO";
            gotoxy(30,17);
            cout << "  GRACIAS POR JUGAR ;)";
            delay(3);
            fin_partida = true;
        } else {
            cout << "Ingrese una opción válida" << endl;
        }
        ronda_contador++;
    } while (!fin_partida);
    
    // TOP TEN
    guardarTop(lista_jugadores);

    // VACIADO DE LISTA DE JUGADORES
    lista_jugadores = NULL;
}

void MainMenu(Casillas **Tablero, Jugadores **lista_jugadores) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // IMPLEMENTACIÓN DE COLORES EN LA TERMINAL
    bool fin_menu = false;
    while (!fin_menu) {
        int opcion;
        int n = 3; // número de opciones del Menú
        const char *opciones[] = {"INICIAR PARTIDA", "REGLAS/TUTORIAL", "SALIR DEL JUEGO"};
        opcion = flechas_menu(opciones, n);

        switch (opcion) {
            case 1: // INICIA PARTIDA
                Partida(*Tablero, *lista_jugadores); // Inicia la partida
                break;
            
            case 2: // INICIA INSTRUCCIONES/REGLAS/TUTORIAL
                system("cls");
                imprime_instrucciones();
                break;

            case 3:
                system("cls");
                gotoxy(30, 15);
                color(hConsole,14);
                cout << "Ha salido con exito del juego, Hasta luego!" << endl;
                fin_menu = true;
                break;   
                
            default:
                cout << "Opción inválida..." << endl;   
                break;
        }
    }
}

//PROGRAMA PRINCIPAL

main(){
    Jugadores *jugador1=NULL;
    Casillas *Tablero=NULL;
    int k=1;
    llenado_tablero(Tablero);
    MainMenu(&Tablero,&jugador1);  //Llamamos al ciclo general de la partida
    
}