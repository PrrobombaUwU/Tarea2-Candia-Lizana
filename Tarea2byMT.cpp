#include <iostream>
#include <string>

using namespace std;

class Linea {

struct Nodo {
Nodo * izquierda , * derecha , * padre ;
string texto ;
unsigned int peso ;
};
Nodo* raiz ;
int w ;

public :

Linea (string str , int w ) ;
~Linea ( void ) ;
void insertar (int posicion , char caracter ) ;
void eliminar (int posicion ) ;
void concatenar ( Linea * raiz ) ;
void invertir ( void ) ;
int print ( void ) ;

//Funciones auxiliares para eliminar

Nodo* buscarhoja(Nodo* actual, unsigned int posicion, int& posicionLocal);
void borrarChar(Nodo* hoja, int posicionLocal);
void actualizarPesos(Nodo* nodo);
void eliminarHoja(Nodo* hoja);

//Funciones auxiliares para invertir

void invertirHoja(Nodo* hoja);
void ArbolEspejo(Nodo* nodo);
void recorridoArbol(Nodo* raiz);

// Funciones auxiliares internas
void liberarMemoria(Nodo* nodo);
string obtenerTexto(Nodo* nodo) const;

};

/* ****
* TipoFuncion NombreFuncion
    void        liberarMemoria
******
* Resumen Función
Recorre el árbol de forma recursiva en post orden y libera la memoria de cada nodo.
Al ser post orden, primero se liberan los hijos antes que el padre, evitando punteros colgantes.
******
* Input :
* tipoParámetro NombreParámetro : Descripción Parámetro
    Nodo*           nodo : nodo desde el cual se comenzará a liberar memoria recursivamente.
* .......
******
* Returns :
* TipoRetorno , Descripción retorno
    void : no retorna nada, solo libera la memoria del árbol.
**** */
void Linea::liberarMemoria(Nodo* nodo) {
    if (nodo == NULL) return;
    liberarMemoria(nodo->izquierda);
    liberarMemoria(nodo->derecha);
    delete nodo;
}

/* ****
* TipoFuncion NombreFuncion
    string      obtenerTexto
******
* Resumen Función
Recorre el árbol de forma recursiva y concatena el texto de todas las hojas en orden
de izquierda a derecha, reconstruyendo así la cadena completa almacenada en la estructura.
******
* Input :
* tipoParámetro NombreParámetro : Descripción Parámetro
    Nodo*           nodo : nodo desde el cual se comenzará a obtener el texto recursivamente.
* .......
******
* Returns :
* TipoRetorno , Descripción retorno
    string : retorna la cadena de texto completa del subárbol del nodo recibido.
**** */
string Linea::obtenerTexto(Nodo* nodo) const {
    if (nodo == NULL) return "";
    if (nodo->izquierda == NULL && nodo->derecha == NULL) {
        return nodo->texto;
    }
    return obtenerTexto(nodo->izquierda) + obtenerTexto(nodo->derecha);
}

/* ****
* TipoFuncion NombreFuncion
    Linea       Linea (Constructor)
******
* Resumen Función
Constructor de la clase Linea. Inicializa el peso máximo w y, si la cadena recibida
no está vacía, crea un nodo raíz hoja con el texto y su peso correspondiente.
Si la cadena está vacía, la raíz queda en NULL.
******
* Input :
* tipoParámetro NombreParámetro : Descripción Parámetro
    string          str       : cadena de texto inicial con la que se construye el árbol.
    int             peso_max  : tamaño máximo de caracteres permitido por nodo hoja.
* .......
******
* Returns :
* TipoRetorno , Descripción retorno
    Linea : objeto Linea inicializado con el texto y el valor de w dados.
**** */
Linea::Linea(string str, int peso_max) {
    w = peso_max;
    if (str.empty()) {
        raiz = NULL;
    } else {
        raiz = new Nodo();
        raiz->texto = str;
        raiz->peso = (unsigned int)str.size();
    }
}

/* ****
* TipoFuncion NombreFuncion
    void        ~Linea (Destructor)
******
* Resumen Función
Destructor de la clase Linea. Llama a liberarMemoria para recorrer y eliminar todos
los nodos del árbol, y luego establece la raíz en NULL para evitar punteros colgantes.
******
* Input :
* tipoParámetro NombreParámetro : Descripción Parámetro
    void : no recibe parámetros.
* .......
******
* Returns :
* TipoRetorno , Descripción retorno
    void : no retorna nada, libera toda la memoria del árbol.
**** */
Linea::~Linea(void) {
    liberarMemoria(raiz);
    raiz = NULL;
}

/* ****
* TipoFuncion NombreFuncion
    void        insertar
******
* Resumen Función
Inserta un caracter en la posición indicada dentro de la estructura. Si el árbol está vacío,
crea un nodo raíz con el caracter. En caso contrario, busca la hoja correspondiente a la
posición mediante buscarhoja e inserta el caracter en el string de dicha hoja, actualizando
su peso. Las posiciones son 1-indexadas.
******
* Input :
* tipoParámetro NombreParámetro : Descripción Parámetro
    int             posicion  : posición 1-indexada donde se insertará el caracter.
    char            caracter  : caracter que se desea insertar en la cadena.
* .......
******
* Returns :
* TipoRetorno , Descripción retorno
    void : no retorna nada, solo modifica el árbol insertando el caracter en la posición dada.
**** */
void Linea::insertar(int posicion, char caracter) {
    if (posicion < 1) {
        posicion = 1;
    }

    if (raiz == NULL) {
        raiz = new Nodo();
        raiz->texto = string(1, caracter);
        raiz->peso = 1;
        return;
    }

    int posicionLocal = 0;
    Nodo* hoja = buscarhoja(raiz, posicion - 1, posicionLocal);
    if (hoja == NULL) {
        return;
    }

    if (posicionLocal < 0) posicionLocal = 0;
    if (posicionLocal > (int)hoja->texto.size()) posicionLocal = (int)hoja->texto.size();
    hoja->texto.insert((size_t)posicionLocal, 1, caracter);
    hoja->peso = (unsigned int)hoja->texto.size();
}

/* ****
* TipoFuncion NombreFuncion
    void        concatenar
******
* Resumen Función
Concatena el texto de otra Linea al final de la cadena actual. Obtiene el texto completo
de ambas estructuras, libera el árbol actual y crea un nuevo nodo raíz hoja que contiene
la unión de ambas cadenas con su peso correspondiente.
******
* Input :
* tipoParámetro NombreParámetro : Descripción Parámetro
    Linea*          otra : puntero a la Linea cuyo texto se agregará al final de la cadena actual.
* .......
******
* Returns :
* TipoRetorno , Descripción retorno
    void : no retorna nada, solo modifica el árbol con el texto concatenado.
**** */
void Linea::concatenar(Linea* otra) {
    if (otra == NULL || otra->raiz == NULL) {
        return;
    }

    string textoActual = obtenerTexto(raiz);
    string textoOtro = otra->obtenerTexto(otra->raiz);

    liberarMemoria(raiz);
    raiz = new Nodo();
    raiz->texto = textoActual + textoOtro;
    raiz->peso = (unsigned int)raiz->texto.size();
}

/* ****
* TipoFuncion NombreFuncion
    int         print
******
* Resumen Función
Obtiene el texto completo del árbol mediante obtenerTexto y lo imprime por pantalla
seguido de un salto de línea. Retorna el largo total de la cadena impresa.
******
* Input :
* tipoParámetro NombreParámetro : Descripción Parámetro
    void : no recibe parámetros.
* .......
******
* Returns :
* TipoRetorno , Descripción retorno
    int : retorna el largo total de la cadena impresa.
**** */
int Linea::print(void) {
    string texto = obtenerTexto(raiz);
    cout << texto << endl;
    return (int)texto.size();
}

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

Linea::Nodo* Linea::buscarhoja(Nodo* actual, unsigned int posicion, int& posicionLocal){
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
    if (padre == NULL) {
        // La hoja era la raíz
        delete hoja;
        raiz = NULL;
        return;
    }

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

    if (posicion < 1) return;

    int posicionLocal = 0; //definimos la posicion local
    Nodo* nodo = raiz; //empezaremos desde la raiz
    Nodo* hoja = buscarhoja(nodo, posicion - 1, posicionLocal); //buscamos la hoja

    if (hoja == NULL) return;

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

/* ****
* TipoFuncion NombreFuncion
    void        mostrarMenu
******
* Resumen Función
Despliega por pantalla las opciones disponibles del menú principal, permitiendo al usuario
elegir la operación que desea realizar sobre la estructura Linea.
******
* Input :
* tipoParámetro NombreParámetro : Descripción Parámetro
    void : no recibe parámetros.
* .......
******
* Returns :
* TipoRetorno , Descripción retorno
    void : no retorna nada, solo imprime el menú por pantalla.
**** */
void mostrarMenu(void) {
    cout << "\n--- Menu ---" << endl;
    cout << "1. Insertar caracter" << endl;
    cout << "2. Eliminar caracter" << endl;
    cout << "3. Concatenar texto" << endl;
    cout << "4. Invertir" << endl;
    cout << "5. Imprimir texto actual" << endl;
    cout << "6. Salir" << endl;
    cout << "Opcion: ";
}

int main(void) {
    string textoInicial;
    int w;

    cout << "Ingrese el texto inicial: ";
    getline(cin, textoInicial);

    cout << "Ingrese el valor de w (tamano maximo por nodo hoja): ";
    cin >> w;
    cin.ignore();

    Linea* linea = new Linea(textoInicial, w);

    cout << "\nTexto actual: ";
    linea->print();

    int opcion = 0;
    while (opcion != 6) {
        mostrarMenu();
        cin >> opcion;

        if (opcion == 1) {
            int posicion;
            string entrada;
            cout << "Posicion (1-indexada): ";
            cin >> posicion;
            cin.ignore();
            cout << "Caracter a insertar: ";
            getline(cin, entrada);
            if (!entrada.empty()) {
                linea->insertar(posicion, entrada[0]);
                cout << "Texto actual: ";
                linea->print();
            }

        } else if (opcion == 2) {
            int posicion;
            cout << "Posicion a eliminar (1-indexada): ";
            cin >> posicion;
            cin.ignore();
            linea->eliminar(posicion);
            cout << "Texto actual: ";
            linea->print();

        } else if (opcion == 3) {
            string textoExtra;
            cout << "Texto a concatenar: ";
            cin.ignore();
            getline(cin, textoExtra);
            Linea* extra = new Linea(textoExtra, w);
            linea->concatenar(extra);
            delete extra;
            cout << "Texto actual: ";
            linea->print();

        } else if (opcion == 4) {
            linea->invertir();
            cout << "Texto actual: ";
            linea->print();

        } else if (opcion == 5) {
            cout << "Texto actual: ";
            linea->print();

        } else if (opcion == 6) {
            cout << "Saliendo..." << endl;

        } else {
            cout << "Opcion invalida." << endl;
        }
    }

    delete linea;
    return 0;
}
