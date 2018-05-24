/*
* 22 de mayo del 2018
* Programa que lee los puntos de triangulos de un archivo
* y los almacena en estructuras tipo triangulo para graficarlos.

    mingw32-make.exe
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <new>
#include <iomanip>
//#include <SDL2/SDL.h>
#include <SDL.h>
#include <windows.h>
#include <math.h>

using namespace std;
//*****************************************************************
struct Punto{
    double x;
    double y;
    double z;
};

struct Paq{
    Punto B,C;
};
//*******************************************************************
void viewport(Punto* P, int cantidad, int caso);
void POrtograficaXY(SDL_Renderer* renderer, Punto* p, int cantidad);
void POrtograficaXZ(SDL_Renderer* renderer, Punto* p, int cantidad);
void POrtograficaYZ(SDL_Renderer* renderer, Punto* p, int cantidad);
void PAxonometrica(SDL_Renderer* renderer, Punto* p, int cantidad);
Paq calcularMaxMin(Punto* A, int cantidad);
int menu(void);
//********************************************************************
int main(int argc, char* args[]){
    ifstream archivo;
    int puntos;
    SDL_Event e;
    int limite=800;

    int op = menu();

    if (op==0) return 0;

    if (!archivo.is_open()) //check is file has been opened
    {
        if(op==1) archivo.open ("itokawa_f0049152.tri", ios::in | ios::out);
        if(op==2) archivo.open ("skull.tri", ios::in | ios::out);

        if (!archivo)
        {
            cerr << "Failed to open " << archivo << endl;
            exit(EXIT_FAILURE);  //abort program
        }
    }

    archivo >> puntos;
    Punto* p = new Punto[puntos*3];

    for (int i=0; i<puntos *3; i++){
        archivo >> p[i].x;
        archivo >> p[i].y;
        archivo >> p[i].z;
    }
    archivo.close();

    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Event event;
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;
        if (SDL_CreateWindowAndRenderer(limite, limite, 0, &window, &renderer) == 0) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawLine(renderer, 400, 0, 400,800); // linea vertical
            SDL_RenderDrawLine(renderer, 0,400,800,400); // linea horizontal
            SDL_SetRenderDrawColor(renderer, 255, 0,0, 0);

            // itokawa
            POrtograficaXY(renderer, p, puntos*3);
            POrtograficaXZ(renderer, p, puntos*3);
            POrtograficaYZ(renderer, p, puntos*3);
            PAxonometrica(renderer, p, puntos*3);
            //************

            SDL_RenderPresent(renderer);
            while (1) {
                if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
                break;
            }

            if (renderer) {
                SDL_DestroyRenderer(renderer);
            }
            if (window) {
                SDL_DestroyWindow(window);
            }
        }
    }

    SDL_Quit();

    delete[] p;

    return 0;
}
//**************************************************************
Paq calcularMaxMin(Punto* A, int cantidad){
    Paq H;
    Punto B;
    Punto C;

    double max_x=A->x;
    double max_y=A->y;
    double max_z=A->z;
    double min_x=A->x;
    double min_y=A->y;
    double min_z=A->z;
    A++;
    for(int i=1; i<cantidad; i++, A++){
        if(A->x > max_x) max_x = A->x;
        if(A->y > max_y) max_y = A->y;
        if(A->z > max_z) max_z = A->z;
        if(A->x < min_x) min_x = A->x;
        if(A->y < min_y) min_y = A->y;
        if(A->z < min_z) min_z = A->z;
    }

    B.x = max_x;
    B.y = max_y;
    B.z = max_z;

    C.x = min_x;
    C.y = min_y;
    C.z = min_z;

    H.B = B;
    H.C = C;
    return H;
}
//********************************************************************************
void copiar(Punto* P, Punto* Q,int cantidad){
    for(int i=0; i < cantidad; i++, Q++, P++){
        Q->x = P->x;
        Q->y = P->y;
        Q->z = P->z;
    }
}
//********************************************************************************
void viewport(Punto* P, int cantidad, int caso){
    Paq X = calcularMaxMin(P, cantidad);

    double Rx = X.B.x - X.C.x;
    double Ry = X.B.y - X.C.y;
    double Rz = X.B.z - X.C.z;
    double Cx, Cy, Cz;

    switch(caso){
        case 0: //xy
            if(Rx>Ry) Ry=Rx;
            else Rx=Ry;
            Cx = 360*X.C.x/Rx;
            Cy = 360*X.C.y/Ry;

            for(int i=0; i <cantidad; i++, P++){
                P->x = P->x*360/Rx - Cx + 20;
                P->y = P->y*360/Ry - Cy + 20;
            }
            break;
        case 1: //xz
            if(Rx>Rz) Rz=Rx;
            else Rx=Rz;
            Cx = 360*X.C.x/Rx;
            Cz = 360*X.C.z/Rz;
            for(int i=0; i <cantidad; i++, P++){
                P->x = P->x*360/Rx - Cx + 20;
                P->z = P->z*360/Rz - Cz + 420;
            }
            break;
        case 2: //yz
            if(Ry>Rz) Rz=Ry;
            else Ry=Rz;
            Cy = 360*X.C.y/Ry;
            Cz = 360*X.C.z/Rz;
            for(int i=0; i <cantidad; i++, P++){
                P->y = P->y*360/Ry -Cy + 420;
                P->z = P->z*360/Rz -Cz + 20;
            }
            break;
        case 3://axonometrica

            if(Rx>Ry) Ry=Rx;
            else Rx=Ry;
            Cx = 360*X.C.x/Rx;
            Cy = 360*X.C.y/Ry;
            for(int i=0; i <cantidad; i++, P++){
                P->x = P->x*360/Rx - Cx + 420;
                P->y = P->y*360/Ry - Cy + 420;
            }

    }

}
//********************************************************************************
void pintarPuntos(SDL_Renderer* renderer, Punto* P, int cantidad, int caso){
    switch(caso){
        case 0: // xy
            for(int i=0; i <cantidad; i++, P++){
                SDL_RenderDrawPoint(renderer, int(P->x), int(P->y));
            }
            break;
        case 1: // xz
            for(int i=0; i <cantidad; i++, P++){
                SDL_RenderDrawPoint(renderer, int(P->x), int(P->z));
            }
            break;
        case 2: // yz
            for(int i=0; i <cantidad; i++, P++){
                SDL_RenderDrawPoint(renderer, int(P->y), int(P->z));
            }
            break;
    }
}

void POrtograficaXY( SDL_Renderer* renderer, Punto* p, int cantidad){
    //graficar entre los pixeles 0-400 en x y 0-400 en y
    Punto *q = new Punto[cantidad];
    copiar(p,q,cantidad);

    viewport(q,cantidad,0); //guarda en q los nuevos puntos
    pintarPuntos(renderer, q, cantidad, 0);
}

void POrtograficaXZ(SDL_Renderer* renderer, Punto* p, int cantidad){
    //graficar entre los pixeles 0-400 en x y 400-800 en z
    Punto *q = new Punto[cantidad];
    copiar(p, q, cantidad);
    viewport(q, cantidad, 1); //guarda en q los nuevos puntos
    pintarPuntos(renderer, q, cantidad, 1);
}

void POrtograficaYZ( SDL_Renderer* renderer, Punto* p, int cantidad){
    //graficar entre los pixeles 400-800 en x y 0-400 en z
    Punto *q = new Punto[cantidad];
    copiar(p, q, cantidad);
    viewport(q, cantidad, 2); //guarda en q los nuevos puntos
    pintarPuntos(renderer, q, cantidad, 2);
}


void PAxonometrica(SDL_Renderer* renderer, Punto* p, int cantidad){
    //graficar entre los pixeles 400-800 en x y 400-800 en y
    Punto *q,*q2;

    q = new Punto[cantidad]; //nuevo arreglo de puntos modificados por la proyección
    q2 = q;

    //CALCULO DE PROYECCION
    for(int i=0; i<cantidad ; i++,q2++,p++){
        q2->x = p->x*(1/sqrt(2)) - p->z/sqrt(2);
        q2->y = p->x*-1/(sqrt(2)*sqrt(3)) + p->y*(sqrt(2))/(sqrt(3)) - p->z/(sqrt(2)*sqrt(3));
        q2->z = 0;
    }

    viewport(q, cantidad, 3);
    pintarPuntos(renderer, q, cantidad, 0);
}

//********************************************************************************************
int menu(){
    int op;

    do{
        cout<<"Elige una opci\xA2n:\n";
        cout<<"1) Itokawa\n";
        cout<<"2) Craneo\n";
        cout<<"0) Salir\n";
        cout<<"\n Opci\xA2n: ";
        cin>>op;
    }while(op != 1 && op!= 2 && op!=0);

    return (op);
}
