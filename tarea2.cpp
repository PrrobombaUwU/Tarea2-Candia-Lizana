#include <iostream>
#include <string>

using namespace std;

class Linea {

struct Nodo {
Nodo * izquierda , * derecha , * padre ;
std :: string texto ;
unsigned int peso ;
};
Nodo* raiz ;
int w ;

public :

Linea ( std :: string str , int w ) ;
~Linea ( void ) ;
void insertar (int posicion , char caracter ) ;
void eliminar (int posicion ) ;
void concatenar ( Linea * raiz ) ;
void invertir ( void ) ;
int print ( void ) ;

//Funciones auxiliares

Nodo* buscarhoja(Nodo* actual, int posicion, int& posicionLocal);
void borrarChar(Nodo* hoja, int posicionLocal);
void actualizarPesos(Nodo* nodo);
void eliminarHoja(Nodo* hoja);
};

Linea::Nodo* Linea::buscarhoja(Nodo* actual, int posicion, int& posicionLocal){
    if(actual->izquierda == NULL && actual->derecha == NULL){
        posicionLocal = posicion;
        return actual;
    }
    if(posicion<actual->peso){
        return buscarhoja(actual->izquierda, posicion, posicionLocal);
        }
    else {
        return buscarhoja(actual->derecha, posicion - actual->peso, posicionLocal);
    }   
}

void Linea::borrarChar(Nodo* hoja, int posicionLocal) {
    
        hoja->texto.erase(posicionLocal, 1);
    
}

void Linea::actualizarPesos(Nodo* nodo){

    Nodo* padre = nodo->padre;

    while(padre != NULL){
        if(nodo==padre->izquierda){
            padre->peso--;
        }
    
    nodo = padre;
    padre = padre->padre;
    }
}

void Linea::eliminarHoja(Nodo* hoja){

    Nodo* padre = hoja->padre;
    Nodo* abuelo = padre->padre;
    Nodo* hermano = NULL;

    if(padre->izquierda==hoja){
        hermano = padre->derecha;
    } else {
        hermano = padre->izquierda;
    }

    if (abuelo==NULL){
        raiz = hermano;
            if(hermano!=NULL){hermano->padre = NULL;}
    } else {
        if (abuelo->izquierda==padre){
            abuelo->izquierda = hermano;
        } else {
            abuelo->derecha = hermano;
        }
        if(hermano!=NULL){hermano->padre = abuelo;}
        
    }   


    delete hoja;
    delete padre;
    
}

void Linea::eliminar(int posicion){

    int posicionLocal = 0;
    Nodo* nodo = raiz;
    Nodo* hoja = buscarhoja(nodo, posicion, posicionLocal);

    borrarChar(hoja, posicionLocal);
    actualizarPesos(hoja);
    
    if(hoja->texto.length() == 0){
        eliminarHoja(hoja);
    }

}
