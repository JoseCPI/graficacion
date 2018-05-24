/*
* 22 de mayo del 2018
* Programa que lee los puntos de triangulos de un archivo
* y los almacena en estructuras tipo triangulo para graficarlos.
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <new>
#include <iomanip>
#include <SDL.h>
#include <windows.h>

using namespace std;
//*************************************

struct punto{
    double x;
    double y;
    double z;
};
//**************************************
punto viewport ( float, float, float, float, float, float);
void Linea(SDL_Renderer* ,int);
//*************************************
int main(int argc, char* args[]){

  ifstream archivo;
  int puntos;
  SDL_Event e;
  int limite=800;

  if (!archivo.is_open()) //check is file has been opened
  {
      archivo.open ("itokawa_f0049152.tri", ios::in | ios::out);

      if (!archivo)
      {
          cerr << "Failed to open " << archivo << endl;
          exit(EXIT_FAILURE);  //abort program
      }
  }

  archivo >> puntos;
  punto* p= new punto[puntos*3];

  for (int i=0; i<puntos *3; i++){
        archivo >> p[i].x;
        archivo >> p[i].y;
        archivo >> p[i].z;
  }
  archivo.close();

  cout<<p[(puntos*3)-1].x<<endl;
  cout<<p[(puntos*3)-1].y<<endl;
  cout<<p[(puntos*3)-1].z<<endl;


    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Event event;
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;
      if (SDL_CreateWindowAndRenderer(limite,limite, 0, &window, &renderer) == 0) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                SDL_RenderClear(renderer);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderDrawLine(renderer, 300,0,300,600);
                SDL_RenderDrawLine(renderer, 0,300,600,300);
                SDL_SetRenderDrawColor(renderer, 255, 0,0, 0);


                for (int i=0; i<puntos; i++){
                //    p1= viewport() ///  CONTINUAR AQUI
                }


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
//************************************************************
//************************************************************

//************************************************************

//**********************************************************************
void Linea(SDL_Renderer* renderer,int limite){

    int X1,Y1,X2,Y2,aux;
    double dY, dX,k,X,Y,av,avR,avI;
    int IncYi,IncXi,IncXr,IncYr;

    cout << endl << "Linea (algoritmo punto medio)" << endl;
    do{
        cout << "Ingrese valor de x1: ";
        cin >> X1;
        if(X1>limite){
            cout << endl << "El valor de x1 excede el rango";
            Sleep(1200);
            system("cls");
        }

    }while(X1>limite);

    do{
        cout << "Ingrese valor de y1: ";
        cin >> Y1;
        if(Y1>limite){
            cout << endl << "El valor de y1 excede el rango";
            Sleep(1200);
            system("cls");
        }

    }while(Y1>limite);

    do{
        cout << "Ingrese valor de x2: ";
        cin >> X2;
        if(X2>limite){
            cout << endl << "El valor de x2 excede el rango";
            Sleep(1200);
            system("cls");
        }

    }while(X2>limite);

    do{
        cout << "Ingrese valor de y2: ";
        cin >> Y2;
        if(Y2>limite){
            cout << endl << "El valor de y2 excede el rango";
            Sleep(1200);
            system("cls");
        }

    }while(Y2>limite);

    if(X2<X1){

        aux=X2;
        X2=X1;
        X1=aux;

        aux=Y2;
        Y2=Y1;
        Y1=aux;
    }

    dY=(Y2-Y1);
    dX=(X2-X1);
     // 1 - Incrementos para las secciones con avance inclinado
    if(dY>=0) IncYi = 1;
    else IncYi = -1;

    if(dX>=0)IncXi = 1;
    else IncXi = -1;

    // 2 - Incrementos para las secciones con avance recto:
    if(dX>=dY){
        IncYr = 0;
        IncXr = IncXi;
    }else{
        IncXr = 0;
        IncYr = IncYi;
        // Cuando dy es mayor que dx, se intercambian, para reutilizar el mismo bucle.
        k = dX;
        dX = dY;
        dY = k;
    }

    // 3  - Inicializar valores (y de error).
    X = X1;
    Y = Y1;
    avR = (2 * dY);
    av = (avR - dX);
    avI = (av - dX);

    // 4  - Bucle para el trazado de las l�nea
        while(X<=X2){
            SDL_RenderDrawPoint(renderer, X+300, -Y+300);
            if(av>=0){
                X = (X + IncXi);     // X aumenta en inclinado.
                Y = (Y + IncYi);     // Y aumenta en inclinado.
                av = (av + avI);     // Avance Inclinado
            }else{
                X = (X + IncXr);     // X aumenta en recto.
                Y = (Y + IncYr);     // Y aumenta en recto.
                av = (av + avR);     // Avance Recto
            }
        }

}
