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

using namespace std;
//*************************************
struct triangulo{
  long double tri[3][3];
};

struct vertice{
  long double v[3];
};

struct cara{
  int c[3];
};
//**************************************
void identidad(triangulo*, int);
//*************************************
int main(){

  ifstream archivo;
  int vertex, faces;

  if (!archivo.is_open()) //check is file has been opened
  {
      archivo.open ("skull.obj", ios::in | ios::out);

      if (!archivo)
      {
          cerr << "Failed to open " << archivo << endl;
          exit(EXIT_FAILURE);  //abort program
      }
  }

  archivo >> vertex;
  archivo >> faces;
  vertice* ver= new vertice[vertex];
  cara* ca= new cara[faces];
  triangulo* t= new triangulo[faces];

  for (int i=0; i<vertex; i++){
    archivo >> ver[i].v[0];
    archivo >> ver[i].v[1];
    archivo >> ver[i].v[2];
  }

  for (int i=0; i<faces; i++){
    archivo >> ca[i].c[0];
    archivo >> ca[i].c[1];
    archivo >> ca[i].c[2];
  }
  archivo.close();

  for (int i=0; i<faces; i++){
    for(int j=0; j<3; j++){
      t[i].tri[0][j]=ver[ca[i].c[j]].v[0];
      t[i].tri[1][j]=ver[ca[i].c[j]].v[1];
      t[i].tri[2][j]=ver[ca[i].c[j]].v[2];
    }
  }

  //t[1].tri[0][0]=1;

  cout<<"\n\n";
  std::cout << "MATRIZ resultado:" << "\n";
  cout<<faces<<endl;
  for (int i=0; i<3 ; i++){
    std::cout << "| ";
    for (int j=0; j<3; j++){
      cout<<setw(15)<<t[faces-1].tri[i][j] << "  ";
    }
    std::cout << " |" << "\n\n";
  }


  ofstream outputFile;
  outputFile.open("skull.tri");

   for (int i=0; i<faces; i++){
     for(int j=0; j<3; j++){
       outputFile<<t[i].tri[0][j]<<" ";
       outputFile<<t[i].tri[1][j]<<" ";
       if(j<2)outputFile<<t[i].tri[2][j]<<" ";
       else outputFile<<t[i].tri[2][j]<<endl;
     }
   }

  outputFile.close();

  delete[] t;
  delete[] ca;
  delete[] ver;

  return 0;

}
//************************************************************
//************************************************************
