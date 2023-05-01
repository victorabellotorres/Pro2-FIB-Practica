/** @file Cluster.hh
    @brief Especificación de la clase Cluster
*/

#ifndef CLUSTER_HH
#define CLUSTER_HH

#include "Procesador.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include "BinTree.hh"
#endif
using namespace std;


/** @class Cluster
    @brief Representa un sistema de procesadores distribuidos en forma de arbol binario.

    Permite modificar el sistema de procesadores y gestionar la ejecución de los procesos y la memoria de los procesadores.
*/
class Cluster
{
public:
    // Constructores

    /** @brief Creadora por defecto
        \pre <em>cierto</em>
        \post El resultado es un clúster, que contiene un único procesador, siendo este la raíz con id = 0 y la memoria sin inicializar
    */
    Cluster();

    // Modificadores

/** @brief Modifica el árbol binario de procesadores
    \pre <em>cierto</em>
    \post El clúster pasado por parámetro se coloca en el procesador cuyo id se indica por parámetro, haciendo crecer así el parámetro implícito.
    La función devuelve 'true' si no ha habido ningún error, en caso contrario devuelve 'false' y el mensaje de error contenido en el parámetro error (si el procesador no existe, si tenia procesos en ejecución o procesadores auxiliares).
*/
    bool modificar(string id_procesador, const Cluster& c, string& error); 

/** @brief Añade un proceso a un procesador específico
    \pre <em>cierto</em>
    \post El proceso p pasa a ejecutarse y ocupar la memoria del procesador cuyo id se indica por parámetro.
    La función devuelve 'true' si no ha habido ningún error, en caso contrario devuelve 'false' y el mensaje de error contenido en el parámetro error (si el procesador no existe, si este ya contiene un proceso con el mismo id o no se puede colocar en el procesador)
*/
    bool añadir_proceso_procesador(string id_procesador, const Proceso& p,  string& error);

/** @brief Elimina un proceso de un procesador específico
    \pre <em>cierto</em>
    \post El proceso  se elimina del procesador cuyos id's se indica por parámetro
    La función devuelve 'true' si no ha habido ningún error, en caso contrario devuelve 'false' y el mensaje de error contenido en el parámetro error (si el procesador no existe o el procesador no contiene el proceso)
*/
    bool eliminar_proceso_procesador(string id_procesador, string id_proceso,  string& error);

/** @brief Añade un proceso al procesador adecuado
    \pre <em>cierto</em>
    \post El proceso p se añade al procesador que tenga el hueco de memoria más ajustado respecto al proceso, el que tenga más memoria libre en caso de empate entre procesadores, el más cercano a la raíz en caso de empate y el que este más a la izquierda si el empate persiste.
    La función devuelve 'true' si no ha habido ningún error, en caso contrario devuelve 'false' y el mensaje de error contenido en el parámetro error (si el proceso no se puede añadir en ningún procesador)
*/
    bool añadir_proceso(const Proceso& p,  string& error);

/** @brief Avanza el tiempo de todos los procesos que estan siendo ejecutados
    \pre t >= 0
    \post El tiempo de ejecución de todos los procesos de los procesadores del parámetro implícito progresa t unidades de tiempo. Se eliminan todos los procesos que hayan terminado en el interválo de tiempo t
*/
    void avanzar_tiempo(int t);

/** @brief Compacta la memoria de un procesador procesador específico
    \pre <em>cierto</em>
    \post Todos los procesos del procesador cuyo id es indicado por parámetro se mueven al principio de su memoria, sin solaparse, sin dejar huecos y respetando el orden inicial
    La función devuelve 'true' si no ha habido ningún error, en caso contrario devuelve 'false' y el mensaje de error contenido en el parámetro error (si el procesador no existe)
*/
    bool compactar_memoria_procesador(string id_procesador, string& error);

/** @brief Compacta la memoria de los procesadores del parámetro implícito
    \pre <em>cierto</em>
    \post Todos los procesos de los procesadores se mueven al principio de su memoria, sin solaparse, sin dejar huecos y respetando el orden inicial
*/
    void compactar_memoria();

    // Consultores

    // Lectura y escritura

/** @brief Lee los procesadores de un clúster y sus conexiones
    \pre El canal estándar de entrada contiene los procesadores, sus conexiones y la memoria de cada uno de ellos
    \post El parámetro implícito contiene el arbol binario de los procesadores leídos por el canal estándar de entrada
*/
    void leer();

/** @brief Imprime en el canal de salida estándar los procesos de un procesador específico
    \pre <em>cierto</em>
    \post Estan escritos en el canal estándar de salida los procesos del procesador cuyo id es indicado por parámetro por orden creciente de posición de memoria, incluyendo la posicíon y el resto de datos de cada proceso
    La función devuelve 'true' si no ha habido ningún error, en caso contrario devuelve 'false' y el mensaje de error contenido en el parámetro error (si el procesador no existe)
*/
    bool imprimir_procesador(string id_procesador, string& error) const;

/** @brief Imprime en el canal de salida estándar los procesos de los procesadores del parámetro implícito
    \pre Los procesos y procesadores contenidos en el parámetro implícito tienen los datos a imprimir definidos
    \post Estan escritos en el canal estándar de salida los procesos de cada procesador(por orden creciente de id), por orden creciente de posición de memoria, incluyendo la posicíon y el resto de datos de cada proceso
*/
    void imprimir_procesadores() const;

/** @brief Escribe la estructura de procesadores del parámetro implícito
    \pre <em>cierto</em>
    \post Escribe la estructura de procesadores del parámetro implícito
*/
    void imprimir_estructura() const;
private:
};
#endif