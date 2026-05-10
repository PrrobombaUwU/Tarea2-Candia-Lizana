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

//Funciones auxiliares para eliminar

Nodo* buscarhoja(Nodo* actual, int posicion, int& posicionLocal);
void borrarChar(Nodo* hoja, int posicionLocal);
void actualizarPesos(Nodo* nodo);
void eliminarHoja(Nodo* hoja);

//Funciones auxiliares para invertir

void invertirHoja(Nodo* hoja);
void ArbolEspejo(Nodo* nodo);
void recorridoArbol(Nodo* raiz);

};

/* ****
* TipoFuncion NombreFuncion
    Nodo*       buscarhoja
******
* Resumen Función
Busca una hoja de forma recursiva, si el hijo izquierdo y derecho del nodo son nulos entonces la posicion local, sería la posición
que se está buscando, y el nodo sería una hoja. Y si la posicion actual es menor al peso del nodo significa que es un nodo interior y 
la posicion se encuentra en el nodo izquierdo, en el caso contrario, el nodo será el de la derecha y la posicion será esta menos el peso 
actual del nodo.
******
* Input :
* tipoParámetro NombreParámetro : Descripción Parámetro
    Nodo*           actual : el nodo que vamos a leer
    int         posicion  :  La posición que queremos encontrar
    int&       posicionLocal : La posición del string del nodo
* .......
******
* Returns :
* TipoRetorno , Descripción retorno
    Nodo* : Retorna un nodo que es hoja.
**** */

Linea::Nodo* Linea::buscarhoja(Nodo* actual, int posicion, int& posicionLocal){
    if(actual->izquierda == NULL && actual->derecha == NULL){ //si es hoja
        posicionLocal = posicion; //la posicion local es igual a la posicion
        return actual; //retorna el nodo actual
    }
    if(posicion<actual->peso){ //si la posicion es menor al peso
        return buscarhoja(actual->izquierda, posicion, posicionLocal); //entonces busca en el nodo izquierdo
        }
    else {
        return buscarhoja(actual->derecha, posicion - actual->peso, posicionLocal); //Y si no busca en el izquierdo y la posicion del caracter será la posicion-el peso del nodo actual

    }   
}

/* ****
* TipoFuncion NombreFuncion
    void      borrarChar
******
* Resumen Función
Elimina un caracter del string en la posicion asignada.
******
* Input :
* tipoParámetro NombreParámetro : Descripción Parámetro
    Nodo*      hoja : el nodo que vamos a borrar el caracter.
    int&       posicionLocal : La posición del caracter del string que hay que borrar.
* .......
******
* Returns :
* TipoRetorno , Descripción retorno
    void : no retorna nada, solo modifica un nodo.
**** */

void Linea::borrarChar(Nodo* hoja, int posicionLocal) {
    
        hoja->texto.erase(posicionLocal, 1); //elimina el caracter del string en la posicion encontrada.
    
}

/* ****
* TipoFuncion NombreFuncion
    void       actualizarPesos
******
* Resumen Función
Mientras el padre exista, entonces si el nodo se encuentra a la izquierda, el peso del padre se actualizará y se reducirá en uno.
Finalmente el nodo quedará como el padre, y el padre como el abuelo, para ir actualizando el peso hacia arriba.
******
* Input :
* tipoParámetro NombreParámetro : Descripción Parámetro
    Nodo*       nodo : el nodo del cual partiremos actualizando el peso.
* .......
******
* Returns :
* TipoRetorno , Descripción retorno
    void: No retorna nada, solo modifica el valor peso del nodo.
**** */

void Linea::actualizarPesos(Nodo* nodo){

    Nodo* padre = nodo->padre; //definimos al padre

    while(padre != NULL){ //si el padre existe, se repite hasta llegar a la raiz
        if(nodo==padre->izquierda){ //y es igual al nodo
            padre->peso--; //entonces reduce el peso
        }
    
    nodo = padre; //el nodo será el padre
    padre = padre->padre; //y el padre será el abuelo
    }
}

/* ****
* TipoFuncion NombreFuncion
    void       eliminarHoja
******
* Resumen Función
    reasigna los nodos, para poder eliminar una hoja que no tiene texto y no perder el arbol, el hermano se vuelve padre y el padre se vuelve abuelo.
    Después elimina los nodos.
******
* Input :
* tipoParámetro NombreParámetro : Descripción Parámetro
    Nodo*           hoja : un nodo hoja.
* .......
******
* Returns :
* TipoRetorno , Descripción retorno
    void: no retorna nada, solo modifica el arbol eliminando una hoja.
**** */

void Linea::eliminarHoja(Nodo* hoja){

    Nodo* padre = hoja->padre; //definimos al padre
    Nodo* abuelo = padre->padre; // y definimos al abuelo
    Nodo* hermano = NULL;

    if(padre->izquierda==hoja){ //si el nodo izquierdo del padre es la hoja que buscamos
        hermano = padre->derecha; // entonces el hermano es el nodo de la derecha del padre
    } else {
        hermano = padre->izquierda; // y si no el hermano es el de la izquierda
    }

    if (abuelo==NULL){ //si el abuelo no existe
        raiz = hermano; //la raiz será el hermano que encontramos
            if(hermano!=NULL){hermano->padre = NULL;} //verificamos si el hermano existe antes de acceder al padre y anularlo, ya que el padre sería la raiz y la raiz no tiene padre.
    } else {
        if (abuelo->izquierda==padre){ //si el nodo izquierdo del abuelo existe y es el padre
            abuelo->izquierda = hermano; // entonces ahora será el hermano
        } else {
            abuelo->derecha = hermano; // y si no, será el nodo derecho del abuelo.
        }
        if(hermano!=NULL){hermano->padre = abuelo;} //verificamos si el hermano existe, antes de hacer que el padre sea el abuelo.
        
    }   

    //eliminamos la hoja y al padre, ya que ya fueron cambiadas.

    delete hoja; 
    delete padre;
    
}

/* ****
* TipoFuncion NombreFuncion
    void       eliminar
******
* Resumen Función
Llama a la función buscar hoja, para buscar la hoja en la que se encuentra la posición, borra el caracter cuando lo encuentra y actualiza el peso 
del arbol, si el texto que contiene la hoja es igual a 0, entonces elimina la hoja.

******
* Input :
* tipoParámetro NombreParámetro : Descripción Parámetro
    int         posicion  :  La posición que queremos eliminar
* .......
******
* Returns :
* TipoRetorno , Descripción retorno
    void: no retorna nada, solo elimina un caracter, y si el nodo queda sin texto lo elimina.
**** */

void Linea::eliminar(int posicion){

    int posicionLocal = 0; //definimos la posicion local
    Nodo* nodo = raiz; //empezaremos desde la raiz
    Nodo* hoja = buscarhoja(nodo, posicion, posicionLocal); //buscamos la hoja

    borrarChar(hoja, posicionLocal); //borramos el caracter con la funcion
    actualizarPesos(hoja); //y actualizamos el peso del arbol
    
    if(hoja->texto.length() == 0){ //si la hoja no tiene texto la eliminamos
        eliminarHoja(hoja);
    }

}

/* ****
* TipoFuncion NombreFuncion
    void      invertirHoja
******
* Resumen Función
 Invierte el texto que está en la hoja.
******
* Input :
* tipoParámetro NombreParámetro : Descripción Parámetro
    Nodo*           hoja: nodo hoja que vamos a invertir.
* .......
******
* Returns :
* TipoRetorno , Descripción retorno
    void : No retorna nada, solo invierte el texto que contiene la hoja.
**** */

void Linea::invertirHoja(Nodo* hoja){
    
    string invertido = ""; //definimos un string vacio

    for(int i = hoja->texto.length()-1; i>=0; i--){ // recorremos el string del final hacia el principio
        invertido += hoja->texto[i]; //vamos agregando caracter a caracter de final a inicio.
    }

    hoja->texto = invertido; //asignamos el nuevo texto a la hoja

}

/* ****
* TipoFuncion NombreFuncion
    void       ArbolEspejo
******
* Resumen Función
Crea un arbol pero con los nodos invertidos, el nodo de la derecha pasa a ser el de la izquierda y el de la izquierda a la derecha.
******
* Input :
* tipoParámetro NombreParámetro : Descripción Parámetro
    Nodo*           nodo: Nodo de que vamos a partir.
* .......
******
* Returns :
* TipoRetorno , Descripción retorno
    void: No retorna nada, solo intercambia los nodos.
**** */

void Linea::ArbolEspejo(Nodo* nodo){

    Nodo* Aux = NULL; //Nodo auxiliar para cambiar los valores de los nodos

    if(nodo->izquierda!=NULL && nodo->derecha!=NULL){
        
        Aux = nodo->izquierda; //asignamos el nodo auxiliar el nodo de la izquierda
        nodo->izquierda = nodo->derecha; //cambiamos la izquierda por la derecha
        nodo->derecha = Aux; // cambiamos la derecha por la izquierda utilizando el nodo auxiliar
        
    }
}

/* ****
* TipoFuncion NombreFuncion
    void        recorridoArbol
******
* Resumen Función
Recorre el arbol de forma recursiva y en post orden, y si son nodos internos entonces los invierte con la funcion arbol espejo, y cuando son 
hojas, entonces invierte el string.
******
* Input :
* tipoParámetro NombreParámetro : Descripción Parámetro
    Nodo*           raiz: recibe la raiz del arbol.
* .......
******
* Returns :
* TipoRetorno , Descripción retorno
    void: No retorna nada, solo invierte los nodos internos y los textos de las hojas.
**** */

void Linea::recorridoArbol(Nodo* raiz){

    
    if (raiz->izquierda!=NULL && raiz->derecha!=NULL) //si la raiz no es hoja
    {
        recorridoArbol(raiz->izquierda); //entonces recorre su nodo izquierdo
        recorridoArbol(raiz->derecha); // después  recorre su nodo derecho
        ArbolEspejo(raiz); // invierte los nodos internos

    } else {
        invertirHoja(raiz); // si es hoja entonces invierte el texto.
    }

}

/* ****
* TipoFuncion NombreFuncion
    void      invertir
******
* Resumen Función
Llama a la función recorrido arbol para ejecutar, es que necesitaba la raiz como parametro y la funcion invertir recibe un void.
******
* Input :
* tipoParámetro NombreParámetro : Descripción Parámetro
    void: no recibe nada.
* .......
******
* Returns :
* TipoRetorno , Descripción retorno
    void: No retorna nada, solo modifica el arbol.
**** */

void Linea::invertir(void){

    recorridoArbol(raiz); //llama a recorridoArbol entregandole el nodo raiz, para que las funciones funcionen correctamente.

}
