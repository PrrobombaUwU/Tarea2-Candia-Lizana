## Preguntas Teoricas

# Pregunta 1: ¿Cual es la complejidad de insertar un elemento?
Teniendo un arbol binario y suponiendo que esta balanceado, la complejidad de insertar un elemento seria de O(log n), ya que recorrer el arbol toma O(log n) y el dividir el nodo en caso de que supere el limite de este tomara O(w), pero como w es una costante sera igual a O(1), asi pues el tiempo sera de O(log n) y en caso de no estar ordenado seria una complejidad mayor, siendo de O(n).


# Pregunta 2: ¿Cual es la complejidad de eliminar un elemento?
Tenoendo un arbol binario y suponiendo que esta balanceado, la complejidad de eliminar un elemento seria de O(log n), al igual que insertar se debe recorrer el arbol siendo de O(log n), al eliminar un elemento sera O(w) osea O(1) al solo eliminar uno y en caso de eliminar el nodo, habria que reorganizar el arbol tomando asi O(log n). por lo tanto la complejidad seria de O(log n), ahora si no esta balanceado al igual que insertar, aumentara su complejidad, dando asi O(n).


# Pregunta 3 ¿En qué afecta la buena selección del valor de límite de tamaño w del string contenido en las hojas?
El seleccionar bien el tamaño es clave para las operaciones y profundidad del arbol:
* Si w es muy chico implica una profundidad mayor, trayendo asi una busqueda más costosa.
* Si w es muy grande implica un costo mayor en las operaciones.
Por lo tanto, el definir bien el peso de los nodos garantiza una menor costo de ejecucion respecto a la busqueda y operaciones a realizar.


# ¿Suponiendo que todas las inserciones ocurren en un lado del árbol, la complejidad seguirá siendo la expresada normalmente? ¿En caso de que no, cómo podría ser arreglada?
No, si crece de un solo lado, vendria siendo como una lista enlazada, eliminando asi la ventaja de busqueda que tiene el arbol. para poder arreglarlo se deben realizar rotaciones de balanceo, hasta que todos los nodos presenten un grado que este entre -1 y 1. 
