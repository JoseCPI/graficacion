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

using namespace std;
//*************************************
struct triangulo{
  float tri[4][4];
};

struct punto{
    float x;
    float y;
};
//**************************************
void identidad(triangulo*, int);
punto viewport ( float, float, float, float, float, float);
void Linea(SDL_Renderer* ,int);
//*************************************
int main(int argc, char* args[]){

  ifstream itokawa;
  int puntos;
  SDL_Event e;
  int limite=800;

  if (!itokawa.is_open()) //check is file has been opened
  {
      itokawa.open ("itokawa_f0049152.tri", ios::in | ios::out);

      if (!itokawa)
      {
          cerr << "Failed to open " << itokawa << endl;
          exit(EXIT_FAILURE);  //abort program
      }
  }

  itokawa >> puntos;
  triangulo* t= new triangulo[puntos];
  float trash;
  identidad(t, puntos);

  for (int i=0; i<puntos; i++){
    for(int j=0; j<3; j++){
      for(int k=0; k<3;k++){
        itokawa >> t[i].tri[k][j];
      }
    }
  }
  itokawa.close();

  punto p1, p2;

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
    return 0;
}

  delete[] t;

  return 0;

}
//************************************************************
//************************************************************

void identidad(triangulo *t, int n) {
  for(int k=0; k<n;k++){
    for (int i=0; i<4 ; i++){
      for (int j=0; j<4; j++){
        if(i==j) t[k].tri[i][j]=1;
        else t[k].tri[i][j]=0;
      }
    }
  }
}
//************************************************************
punto viewport ( float xmin, float ymin, float xmax, float, ymax, float x, float y){
    punto p;
    float umax, vmax, umin, vmin;
    umax=vmax=800;
    umin=vmin=0;

    p.x= ((umax - umin) / (xmax - xmin)) * (x - xmin) + umin;
    p.y= vmax - ((vmax - vmin) / (ymax - ymin)) * (y- tmin);

    return p;
}
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
