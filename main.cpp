//PROYECTO DE ALGORITMOS Y ESTRUCTURAS DE DATOS 
//MADE BY: RICARDO MEJIA & EDUARDO ROJAS

//CONSTANTES Y LIBRERIAS
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <string> 
#include <windows.h>
#include <conio.h>

using namespace std;
//#define ARRIBA 'i'
//#define ABAJO 'k'
#define ARRIBA 72
#define ABAJO 80
#define ENTER 13
#define color SetConsoleTextAttribute

//Declaración de Estructuras

struct Recursos{
    int id_recurso;
    string nombre_recurso;
    Recursos *prox_recurso;
};

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

void MostrarInventario(Jugadores *&JugadorX){
    int opcion;
    cout<<" Hola! "<<JugadorX->nombre_jugador<<" desea ver su inventario? "<<endl;
    cout<<"1- Si "<<endl;
    cout<<"2- No "<<endl;
    cin>>opcion;
    bool valido=true;

    while(valido==true)

        if(opcion==1){
            cout<<"El inventario de "<<JugadorX->nombre_jugador<< " es: "<<endl;
            cout<<"Agua: "<<JugadorX->inventario->agua<<endl;
            cout<<"Metal: "<<JugadorX->inventario->metal<<endl;
            cout<<"Piedra: "<<JugadorX->inventario->piedra<<endl;
            cout<<"Madera: "<<JugadorX->inventario->madera<<endl;
            cout<<"Semilla: "<<JugadorX->inventario->semilla<<endl;
            cout<<"Papel: "<<JugadorX->inventario->papel<<endl;
            valido=false;
        }else if(opcion==2){
            cout<<"Su inventario no fue abierto "<<JugadorX->nombre_jugador<<endl;
            valido=false;
        }else{
            cout << "Opcion invalida,por favor  seleccione 1 o 2" << endl;
        }
        }

Jugadores *CrearJugador(string nombre){
    Jugadores *NuevoJugador= new Jugadores;
    NuevoJugador->pts=0;
    NuevoJugador->nombre_jugador=nombre;
    NuevoJugador->inventario=NULL;
    NuevoJugador->prox_jugador=NULL;
    CrearInventario(NuevoJugador);
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
        gotoxy(28, 3 + opcionSeleccionada); cout << "==>" << endl;
        gotoxy(51, 3 + opcionSeleccionada); cout << "<==" << endl;

        // Imprime el título del menú
        ocultarCursor();
        color(hConsole, 6);
        gotoxy(26, 2); cout << "BIENVENIDO AL JUEGO AMBIENTAL"; //Hay que encontrar un mejor nombre
        color(hConsole, 8);
        gotoxy(6,9); cout<<"Usar las Teclas de las ''FLECHAS DIRECCIONALES'' para moverse por el menu";
        gotoxy(18,10); cout<<"Presione enter para seleccionar alguna opcion";
        // Imprime las opciones del menú

        for (int i = 0; i < n; ++i) {
            ocultarCursor();
            color(hConsole, 7);
            gotoxy(32, 4 + i); cout << i + 1 << ") " << opciones[i];
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

}

//CONTROL DE ARCHIVOS

//TABLERO

Casillas* crearCasilla(int valor){
    Casillas *nuevo = new Casillas;
    nuevo->id_casillas = valor;
    nuevo->prox = NULL;
    return nuevo;
}//funcion para crear los nodos del tablero(lista)
// Casillas *BuscaCasilla(Casillas *Tablero, int numcasilla){
//     Casillas *aux=NULL;

    
//     while(Tablero!=NULL){
//         if(Tablero->id_casillas==numcasilla){
//             crearCasilla()
//         } 
//     }
    
//     return xxx;
// }

void PickUp(Casillas *Tablero, Jugadores **Jugador){
    Casillas *auxiliar=Tablero;
    while(auxiliar->id_casillas!=(*Jugador)->posicion){
        if(auxiliar->recursoid==1){
            (*Jugador)->inventario->agua=(*Jugador)->inventario->agua+auxiliar->inventario->agua;
            (*Jugador)->inventario->madera=(*Jugador)->inventario->madera+auxiliar->inventario->madera;
            (*Jugador)->inventario->metal=(*Jugador)->inventario->metal+auxiliar->inventario->metal;
            (*Jugador)->inventario->papel=(*Jugador)->inventario->papel+auxiliar->inventario->papel;
            (*Jugador)->inventario->piedra=(*Jugador)->inventario->piedra+auxiliar->inventario->piedra;
            (*Jugador)->inventario->semilla=(*Jugador)->inventario->semilla+auxiliar->inventario->semilla;
        }

    }

    MostrarInventario(*Jugador);
}


bool TableroVacio(Casillas *inicio){
    return inicio==NULL;
}

bool JugadoresVacio(Jugadores *inicio){
    return inicio==NULL;
}

void imprimirflechas(){
    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );//IMPLEMENTACIÓN DE COLORES EN LA TEMRMINAL
    //FLECHAS DERECHA
    color(hConsole,12);
    gotoxy(34,1);
    cout<<"|";
    gotoxy(34,2);
    cout<<"V";
    gotoxy(34,5);
    cout<<"|";
    gotoxy(34,6);
    cout<<"V";
    //FLECHAS IZQUIERDA
    gotoxy(3,3);
    cout<<"|";
    gotoxy(3,4);
    cout<<"V";
    gotoxy(3,7);
    cout<<"|";
    gotoxy(3,8);
    cout<<"V";
    color(hConsole,15);
}    

void mostrartablero(Casillas *Tablero){
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // IMPLEMENTACIÓN DE COLORES EN LA TERMINAL
    mostrarCursor();
    int columnas = 5, filas = 9;
    bool izquierdaADerecha = true;
    Casillas *mover = Tablero;

    for (int i = 0; i < filas; i += 2) {
        if (izquierdaADerecha) {
            for (int j = 0; j < columnas; j++) {
                if (mover->id_casillas < 10) { // ORDEN IZQUIERDA->DERECHA DE 1 DIGITO
                    // BOSQUE
                    if (mover->id_casillas > 0 && mover->id_casillas < 6) {
                        gotoxy((j * 6) + 5, i);
                        color(hConsole, 10);
                        cout << "|0" << mover->id_casillas << "|";
                        color(hConsole, 12);
                        cout << "->";
                        color(hConsole, 15);
                    }
                    // CIUDAD
                    if (mover->id_casillas > 10 && mover->id_casillas < 16) {
                        gotoxy((j * 6) + 5, i);
                        color(hConsole, 15);
                        cout << "|0" << mover->id_casillas << "|";
                        color(hConsole, 12);
                        cout << "->";
                        color(hConsole, 15);
                    }
                    // TUNDRA
                    if (mover->id_casillas > 20 && mover->id_casillas < 26) {
                        gotoxy((j * 6) + 5, i);
                        color(hConsole, 11);
                        cout << "|0" << mover->id_casillas << "|";
                        color(hConsole, 12);
                        cout << "->";
                        color(hConsole, 15);
                    }
                } else { // ORDEN IZQUIERDA->DERECHA DE 2 DIGITOS
                    // BOSQUE
                    if (mover->id_casillas > 0 && mover->id_casillas < 6) {
                        gotoxy((j * 6) + 5, i);
                        color(hConsole, 10);
                        cout << "|" << mover->id_casillas << "|";
                        color(hConsole, 12);
                        cout << "->";
                        color(hConsole, 15);
                    }
                    // CIUDAD
                    if (mover->id_casillas > 10 && mover->id_casillas < 16) {
                        gotoxy((j * 6) + 5, i);
                        color(hConsole, 15);
                        cout << "|" << mover->id_casillas << "|";
                        color(hConsole, 12);
                        cout << "->";
                        color(hConsole, 15);
                    }
                    // TUNDRA
                    if (mover->id_casillas > 20 && mover->id_casillas < 26) {
                        gotoxy((j * 6) + 5, i);
                        color(hConsole, 11);
                        cout << "|" << mover->id_casillas << "|";
                        color(hConsole, 12);
                        cout << "->";
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
                        gotoxy((j * 6) + 3, i);
                        color(hConsole, 12);
                        cout << "<-";
                        color(hConsole, 9);
                        cout << "|0" << mover->id_casillas << "|";
                    }
                    // SABANA
                    if (mover->id_casillas > 15 && mover->id_casillas < 21) {
                        gotoxy((j * 6) + 3, i);
                        color(hConsole, 12);
                        cout << "<-";
                        color(hConsole, 14);
                        cout << "|0" << mover->id_casillas << "|";
                    }
                } else { // ORDEN DERECHA->IZQUIERDA DE 2 DIGITOS
                    // MARITIMO
                    if (mover->id_casillas >= 6 && mover->id_casillas <= 10) {
                        gotoxy((j * 6) + 3, i);
                        color(hConsole, 12);
                        cout << "<-";
                        color(hConsole, 9);
                        cout << "|" << mover->id_casillas << "|";
                    }
                    // SABANA
                    if (mover->id_casillas > 15 && mover->id_casillas < 21) {
                        gotoxy((j * 6) + 3, i);
                        color(hConsole, 12);
                        cout << "<-";
                        color(hConsole, 14);
                        cout << "|" << mover->id_casillas << "|";
                    }
                }
                mover = mover->prox; // Move to the next cell regardless of the condition
            }
        }
        izquierdaADerecha = !izquierdaADerecha; // Switch the direction
    }
    
    imprimirflechas();
    gotoxy(36, 8);
    cout << " F I N" << endl;
}

void llenado_tablero(Casillas *&Tablero) {
    int i = 1;
    Casillas *auxiliar=Tablero;
    while (i <= 25) { 
        Casillas *CasillaNueva = crearCasilla(i);
        if (TableroVacio(Tablero)) {
            Tablero = CasillaNueva;
        } 
        else {
            Casillas *auxiliar_mover = Tablero;
            while (auxiliar_mover->prox != NULL) {
                auxiliar_mover = auxiliar_mover->prox;
            }
            auxiliar_mover->prox = CasillaNueva;
        }
        i++;
    }

    while(auxiliar!=NULL){
        if(auxiliar->id_casillas==2){
            auxiliar->recursoid=1;
            auxiliar->inventario->agua=5;
            auxiliar->inventario->semilla=6;
            auxiliar->inventario->piedra=2;
            auxiliar->inventario->madera=0;
            auxiliar->inventario->metal=0;
            auxiliar->inventario->papel=0;
        }
        if(auxiliar->id_casillas==6){
            auxiliar->recursoid=1;
            auxiliar->inventario->agua=0;
            auxiliar->inventario->semilla=3;
            auxiliar->inventario->piedra=2;
            auxiliar->inventario->madera=4;
            auxiliar->inventario->metal=2;
            auxiliar->inventario->papel=1;
        }
        if(auxiliar->id_casillas==9){
            auxiliar->recursoid=1;
            auxiliar->inventario->agua=1;
            auxiliar->inventario->semilla=2;
            auxiliar->inventario->piedra=1;
            auxiliar->inventario->madera=2;
            auxiliar->inventario->metal=0;
            auxiliar->inventario->papel=0;
        }
        if(auxiliar->id_casillas==11){
            auxiliar->recursoid=1;
            auxiliar->inventario->agua=0;
            auxiliar->inventario->semilla=0;
            auxiliar->inventario->piedra=5;
            auxiliar->inventario->madera=1;
            auxiliar->inventario->metal=4;
            auxiliar->inventario->papel=2;
        }
        if(auxiliar->id_casillas==14){
                auxiliar->recursoid=1;
                auxiliar->inventario->agua=1;
                auxiliar->inventario->semilla=0;
                auxiliar->inventario->piedra=1;
                auxiliar->inventario->madera=3;
                auxiliar->inventario->metal=0;
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

void CrearListadeJugadores(Jugadores *&JugadorInicial, Casillas *&Tablero){
    int numerodejugadores,opcion_equipo;
    cout<<"\n\nIndique la cantidad de jugadores: ";

    //FALTA IMPLEMENTAR MAXIMO DE JUGADORES ==3

    cin>>numerodejugadores;
    int i=1;
    string nombredejugador; 
    while(i<=numerodejugadores){
        cout<<"Indique el nombre del jugador numero "<<i<<" aqui: ";
        cin>>nombredejugador;
        Jugadores *JugadorNuevo=CrearJugador(nombredejugador);
        JugadorNuevo->ubicacion_casilla=Tablero;
        JugadorNuevo->posicion=Tablero->id_casillas;
        do {
            cout<<"Indique a cual equipo quiere pertenecer: "<<endl;
            cout<<"1. Equipo Rojo,son expertos en el uso de energias renovables"<<endl;
            cout<<"2. Equipo Azul,encargados del cuidado de ecosistemas maritimos"<<endl;
            cout<<"3. Equipo Verde,enfocados en la conservacion de la fauna y la deforestacion"<<endl;
            cin>>opcion_equipo;
            if (opcion_equipo<1 || opcion_equipo>3) {
                cout << "Opcion invalida,por favor  seleccione 1, 2 o 3." << endl;
            }
        }while(opcion_equipo < 1 || opcion_equipo > 3);
        
        switch(opcion_equipo){
            case 1:
                cout<<"Bienvenido al Equipo Rojo, "<<nombredejugador<<endl;
                JugadorNuevo->nombre_equipo="Equipo Rojo";
                JugadorNuevo->equipo=1;
            break;
            
            case 2:
                cout<<"Bienvenido al Equipo Azul, "<<nombredejugador<<endl;
                JugadorNuevo->nombre_equipo="Equipo Azul";
                JugadorNuevo->equipo=2;
            break;
            
            case 3:
                cout<<"Bienvenido al Equipo Verde, "<<nombredejugador<<endl;
                JugadorNuevo->nombre_equipo="Equipo Verde";
                JugadorNuevo->equipo=3;
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

void mostrarjugadores(Jugadores *JugadorInicial){
    Jugadores *mover=JugadorInicial;
        while (mover != NULL){
            cout <<" | "<< mover->nombre_jugador<<" | " <<"->";
            mover = mover->prox_jugador;
        }
        cout<<"F I N"<<endl;
    }

void mover_jugador(Jugadores *&JugadorInicial, Casillas *&Tablero) {
    Jugadores *Auxiliar = JugadorInicial;
    int opcion;
    
    while (Auxiliar != NULL) {
        system("cls");
        cout << Auxiliar->nombre_jugador << " quieres moverte una casilla hacia adelante?" << endl;
        cout << "0- Para permanecer en la casilla actual" << endl;
        cout << "1- Para moverte una casilla hacia adelante" << endl;
        cout << "2- Para abrir tu inventario" << endl;
        cin >> opcion;

        if (opcion == 1) {
            if (Auxiliar->ubicacion_casilla->prox != NULL) {
                Auxiliar->ubicacion_casilla = Auxiliar->ubicacion_casilla->prox;
                Auxiliar->posicion = Auxiliar->ubicacion_casilla->id_casillas;
                cout << Auxiliar->nombre_jugador << " del equipo " << Auxiliar->nombre_equipo << " se movio a la casilla " << Auxiliar->posicion << endl;
                PickUp(Tablero,&JugadorInicial);
            } else {
                cout << Auxiliar->nombre_jugador << " ha llegado al final del tablero" << endl;
            }
        } else if (opcion == 0) {
            cout << Auxiliar->nombre_jugador << " no realizo ningun movimiento, esta ubicado en la casilla: " << Auxiliar->posicion << endl;
        }else {
            cout << "Opcion Invalida" << endl;
        }

        if (opcion == 2) {
            MostrarInventario(Auxiliar);
        } 

        Auxiliar = Auxiliar->prox_jugador;
    }
}
//CICLOS MENU/JUEGO/RONDA/TURNO

void Turno(/*parámetros*/){ //acaba cuando el jugador elija su acción
}

void Ronda(/*parámetros*/){ //acaba al haber terminado el Turno de cada jugador

}

void Partida(Casillas **Tablero, Jugadores *lista_jugadores){ //acaba cuando se cumple la condicion de fin de partida, ya sea victoria o salida forzada
    bool fin_partida;
    
    mostrartablero(*Tablero);
    CrearListadeJugadores(lista_jugadores,*Tablero);
    mover_jugador(lista_jugadores,*Tablero);
    MostrarInventario(lista_jugadores);


}

void MainMenu(Casillas **Tablero, Jugadores **lista_jugadores){// acaba cuando se decida cerrar el juego(programa) por completo
    bool fin_juego=false;
    int opcion;
    int n=3; //numero de opciones del Menú
    const char *opciones[] = {"INICIAR PARTIDA", "REGLAS/TUTORIAL", "SALIR DEL JUEGO"};
    opcion=flechas_menu(opciones,n);
    while(fin_juego!=true){

        switch (opcion){
            case 1: //INICIA PARTIDA
                Partida(*&Tablero,*lista_jugadores); //Inicia la partida
            break;
            
            case 2: //INICIA INSTRUCCIONES/REGLAS/TURORIAL
                imprime_instrucciones();
            break;

            case 3:
                system("cls");
                gotoxy(15,2);cout<<"\n\nHa Salido con exito del Juego, Hasta luego!"<<endl;
                fin_juego=true;
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
    llenado_tablero(Tablero);
    MainMenu(&Tablero,&jugador1);  //Llamamos al ciclo general de la partida
    
}