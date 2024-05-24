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
#define ARRIBA 72
#define ABAJO 80
#define ENTER 13
#define color SetConsoleTextAttribute

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
    cout<<"gabriel marica";
}

void imprimirflechas(){
    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );//IMPLEMENTACIÓN DE COLORES EN LA TEMRMINAL
    //FLECHAS DERECHA
    color(hConsole,12);
    gotoxy(34,2);
    cout<<"|";
    gotoxy(34,3);
    cout<<"V";
    gotoxy(34,6);
    cout<<"|";
    gotoxy(34,7);
    cout<<"V";
    //FLECHAS IZQUIERDA
    gotoxy(3,4);
    cout<<"|";
    gotoxy(3,5);
    cout<<"V";
    gotoxy(3,8);
    cout<<"|";
    gotoxy(3,9);
    cout<<"V";
    color(hConsole,15);
}    

void mostrartablero(Casillas *Tablero){
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // IMPLEMENTACIÓN DE COLORES EN LA TERMINAL
    mostrarCursor();
    int columnas = 5, filas = 10;
    bool izquierdaADerecha = true;
    Casillas *mover = Tablero;

    for (int i = 1; i < filas; i += 2) {
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
    gotoxy(36, 9);
    cout << " F I N" << endl;
}

void MostrarInventario(Jugadores *&JugadorX,int opcion){
    bool valido=true;
    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );//IMPLEMENTACIÓN DE COLORES EN LA TEMRMINAL
    while(valido==true)
        if(opcion==1){
            cout<<"El inventario de "<<JugadorX->nombre_jugador<< " es: "<<endl;
            color(hConsole,11);
            cout<<"Agua: "<<JugadorX->inventario->agua<<endl;
            color(hConsole,13);
            cout<<"Metal: "<<JugadorX->inventario->metal<<endl;
            color(hConsole,8);
            cout<<"Piedra: "<<JugadorX->inventario->piedra<<endl;
            color(hConsole,14);
            cout<<"Madera: "<<JugadorX->inventario->madera<<endl;
            color(hConsole,10);
            cout<<"Semilla: "<<JugadorX->inventario->semilla<<endl;
            color(hConsole,15);
            cout<<"Papel: "<<JugadorX->inventario->papel<<endl;
            valido=false;
        }else if(opcion==2){
            cout<<"Su inventario no fue abierto "<<JugadorX->nombre_jugador<<endl;
            valido=false;

        }else{
            cout << "Opcion invalida,por favor  seleccione 1 o 2" << endl;
        }
        }

void MostrarJugadores(Jugadores *JugadorInicial){
    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );//IMPLEMENTACIÓN DE COLORES EN LA TEMRMINAL
    Jugadores *mover=JugadorInicial;
        while (mover != NULL){
            if (mover->equipo==1){
                cout <<" | "<< mover->nombre_jugador<<" | " <<"->";
                color(hConsole,12);
            }
            if (mover->equipo==2)
            {
                color(hConsole,9);
                cout <<" | "<< mover->nombre_jugador<<" | " <<"->";
            }
            if (mover->equipo==3)
            {
                color(hConsole,15);
                cout <<" | "<< mover->nombre_jugador<<" | " <<"->";
            }
            cout <<" | "<< mover->nombre_jugador<<" | " <<"->";
            mover = mover->prox_jugador;
        }
        cout<<"FIN"<<endl;
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

//TABLERO
void CrearListadeJugadores(Jugadores *&JugadorInicial, Casillas *&Tablero,int numerodejugadores){
    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );//IMPLEMENTACIÓN DE COLORES EN LA TEMRMINAL
    mostrarCursor();
    int opcion_equipo;
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
            color(hConsole,12);
            cout<<"\n1. Equipo Rojo,son expertos en el uso de energias renovables"<<endl;
            color(hConsole,9);
            cout<<"2. Equipo Azul,encargados del cuidado de ecosistemas maritimos"<<endl;
            color(hConsole,10);
            cout<<"3. Equipo Verde,enfocados en la conservacion de la fauna y la deforestacion"<<endl;
            color(hConsole,15);
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

void PickUp(Casillas *&Tablero, Jugadores *&Jugador){
    Casillas *auxiliar=Tablero;
    while(auxiliar!=NULL && auxiliar->id_casillas!=Jugador->posicion){
        auxiliar=auxiliar->prox;
    }

    if(auxiliar!=NULL && auxiliar->recursoid==1){
        Jugador->inventario->agua += auxiliar->inventario->agua;
        Jugador->inventario->madera += auxiliar->inventario->madera;
        Jugador->inventario->metal += auxiliar->inventario->metal;
        Jugador->inventario->papel += auxiliar->inventario->papel;
        Jugador->inventario->piedra += auxiliar->inventario->piedra;
        Jugador->inventario->semilla += auxiliar->inventario->semilla;
        }

    MostrarInventario(Jugador,1);
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
void Trivias(Jugadores *&Jugador){
    int casilladeljugador;
    casilladeljugador=Jugador->posicion;
    
        // trivia pre boss es incendio forestal
        if(Jugador->posicion==4){
            cout<<Jugador->nombre_jugador<< "ha caido en una TRIVIA,responda bien la siguiente situacion y se le asignaran recursos y puntos "<<endl;
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
                    cout<<"¡Felicidades "<<Jugador->nombre_jugador<<" tu respuesta fue correcta!"<<endl;
                    cout<<Jugador->nombre_jugador<<" gano 10 puntos y 5 semillas"<<endl;
                    Jugador->pts=Jugador->pts+10;
                    cout<<"Ahora tienes : "<<Jugador->pts<<" puntos"<<endl;
                    Jugador->inventario->semilla=Jugador->inventario->semilla+5;
                    MostrarInventario(Jugador,1);
                    correcto=false;
                }else if(opcion1<1 ||opcion1>3) {
                    cout<<"Opcion invalida, vuelva a intentarlo: "<<endl;
                }else{
                    cout<<"Respuesta incorrecta, ha perdido 2 semillas y 1 agua"<<endl;
                    Jugador->inventario->semilla=Jugador->inventario->semilla-2;
                    Jugador->inventario->agua=Jugador->inventario->agua-1;
                    MostrarInventario(Jugador,1);
                    correcto=false;

                }

            }

        }

        // trivia pre boss es contaminacion por co2
        if(Jugador->posicion==8){
            cout<<Jugador->nombre_jugador<< "ha caido en una TRIVIA,responda bien la siguiente situacion y se le asignaran recursos y puntos "<<endl;
            cout<<" Estás caminando cerca de una  ciudad grande y notas que la calidad del aire es muy mala, ¿a que crees que se deba esto?"<<endl;
            cout<<"1.Contaminacion de CO2 producidas de fabricas, combustibles y transportes"<<endl;
            cout<<"2.La atmosfera se encuentra triste"<<endl;
            cout<<"3.El espacio esta generando calor que afecta directamente al aire que respiramos"<<endl;
            int opcion2;
            bool correcto2=true;
            while(correcto2==true){
                cin>>opcion2;
                if(opcion2==1){
                    cout<<"¡Felicidades "<<Jugador->nombre_jugador<<" tu respuesta fue correcta!"<<endl;
                    cout<<Jugador->nombre_jugador<<" gano 15 puntos,2 semillas,1 papel y 3 metales"<<endl;
                    Jugador->pts=Jugador->pts+15;
                    cout<<"Ahora tienes : "<<Jugador->pts<<" puntos"<<endl;
                    Jugador->inventario->semilla=Jugador->inventario->semilla+2;
                    Jugador->inventario->papel=Jugador->inventario->papel+1;
                    Jugador->inventario->metal=Jugador->inventario->metal+3;
                    MostrarInventario(Jugador,1);
                    correcto2=false;
                }else if(opcion2<1 ||opcion2>3) {
                    cout<<"Opcion invalida, vuelva a intentarlo: "<<endl;
                }else{
                    cout<<"Respuesta incorrecta, ha perdido 1 semilla, 1 metal y 5 puntos"<<endl;
                    Jugador->pts=Jugador->pts-5;
                    puntosnegativos(Jugador);
                    cout<<"Ahora tienes: "<<Jugador->pts<<endl;
                    Jugador->inventario->semilla=Jugador->inventario->semilla-2;
                    Jugador->inventario->agua=Jugador->inventario->agua-1;
                    recursosnegativos(Jugador);
                    MostrarInventario(Jugador,1);
                    correcto2=false;
                }
                }
        }
   
       //case 13:// trivia pre boss es deshielo por el calentamiento global

       //    break;
       //case 17:// trivia pre boss contaminacion de las aguas

       //    break;
       //case 23:// trivia pre boss es perdida de biodiversidad tanto fauna como flora

       //    break;
    
}

void mover_jugador(Jugadores *&JugadorInicial, Casillas *& Tablero, bool fin_partida) {
    Jugadores *Jugador = JugadorInicial;
    int opcion;
    
    bool valido;

    while(valido==false){
            valido=false;
            gotoxy(3,12);
            cout<< "''"<<Jugador->nombre_jugador << "'', Que opcion deseas realizar?" << endl;
            cout<<"\n0- Para permanecer en la casilla actual" << endl;
            cout<<"1- Para moverte una casilla hacia adelante" << endl;
            cout<<"2- Para abrir tu inventario" << endl;
            cin>>opcion;
            if (opcion == 1) {
                if (Jugador->ubicacion_casilla!=NULL) {
                    Jugador->ubicacion_casilla=Jugador->ubicacion_casilla->prox;
                    Jugador->posicion=Jugador->ubicacion_casilla->id_casillas;
                    cout<<Jugador->nombre_jugador<<" del equipo "<<Jugador->nombre_equipo << " se movio a la casilla "<<Jugador->posicion<<endl;
                    PickUp(Tablero,Jugador);
                    Trivias(Jugador);
                    valido=true;
                } else {
                    cout<<Jugador->nombre_jugador<<" ha llegado al final del tablero"<<endl;
                    fin_partida=true;
                    valido=true;
                }
            }

            if(opcion==0){
                cout<< Jugador->nombre_jugador<<" no realizo ningun movimiento, esta ubicado en la casilla:"<<Jugador->posicion<<endl;
                valido=true;
            }
            if(opcion==2){
                MostrarInventario(Jugador,1);
                valido=false;
            }
            if(opcion<0 || opcion>2){
                cout<< "Opcion Invalida" << endl;
                valido=false;
            }

        system("pause");  // Pausa después de cada turno para que el usuario vea el resultado
        system("cls");
        mostrartablero(Tablero);
    }
}


void Inserta_Ultimo_Jugadores(Jugadores *&ListaLlenar, Jugadores ListaOrigen){
    ListaLlenar->equipo;
    //FALTA TERMINAR ESTA FUNCION LLAMADA EN ronda()
}


//CICLOS MENU/JUEGO/RONDA/TURNO

void Turno(Casillas *&Tablero, Jugadores *&lista_jugadores, bool *fin_partida){ //acaba cuando el jugador elija su acción
        mover_jugador(lista_jugadores,Tablero,fin_partida);
    }

void Ronda(Casillas *&Tablero, Jugadores *&lista_jugadores, bool *fin_partida){ //acaba al haber terminado el Turno de cada jugador
    bool fin_jugadores;
    Jugadores *avanza_jugadores=lista_jugadores, *devuelve=NULL; 
    while (avanza_jugadores!=NULL){
        Turno(Tablero, avanza_jugadores,fin_partida);
        Inserta_Ultimo_Jugadores(devuelve,*avanza_jugadores);
        avanza_jugadores=avanza_jugadores->prox_jugador;
    }
    lista_jugadores=devuelve;
    
}

void Partida(Casillas *&Tablero, Jugadores *&lista_jugadores){ //acaba cuando se cumple la condicion de fin de partida, ya sea victoria o salida forzada
    bool fin_partida=false, cantidadvalida=false;
    int cantidad_jugadores;//jugadores xd;
    system("cls");
    mostrarCursor();
    while(cantidadvalida==false){//while para pedir el numero de jugadores verificando que no sea mayor a 3 ni menores a 0
        cout<<"Ingrese la cantidad de jugadores de la partida: ";
        cin>>cantidad_jugadores;
        if(cantidad_jugadores<=0 || cantidad_jugadores>3){
            cout<<"LA CANTIDAD MAXIMA DE JUGADORES ES 3.Intente de nuevo"<<endl;
            cantidadvalida=false;
        }else{
            cantidadvalida=true;
        }
    }
    //UNA VEZ INGRESADA LA CANTIDAD DE JUGADORES EMPIEZA LA PARTIDA

    CrearListadeJugadores(lista_jugadores,Tablero,cantidad_jugadores);
    mostrartablero(Tablero);
    do{
        //Ronda(Tablero, lista_jugadores, fin_partida);
    } while (fin_partida);
    //SALIR DE ESTE CICLO IMPLIA QUE YA NO HAY PARTIDA TRANSCURRIENDO Y TOCA VOLVER AAL MENÚ

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
                Partida(*Tablero,*lista_jugadores); //Inicia la partida
                fin_juego=true;
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