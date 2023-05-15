/** @file Procesador.hh
    @brief Especificación de la clase Procesador
*/

#ifndef PROCESADOR_HH
#define PROCESADOR_HH

#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <map>
#include <set>
#endif
using namespace std;

/** @class Procesador
    @brief Representa un procesador

    Permite ejecutar procesos y gestionar su propia memoria
*/
class Procesador
{
public:
    // Constructores

/** @brief Constructora por defecto
    \pre <em>cierto</em>
    \post El resultado es un procesador con un id y tamaño de memoria igual a cero y una memoria vacia.
*/
    Procesador();

/** @brief Constructora con valores concretos
    \pre id solo contiene letras y numeros, y el tamaño de la memoria
    \post El resultado es un procesador con el id y el tamaño de memoria pasados por parámetro, y una memoria vacia.
*/
    Procesador(string id, int memoria);


    // Modificadores
/** @brief Añade un proceso al parámetro implícito
    \pre El parámetro implícito no contiene un proceso con el mismo identificador que <em>p</em>
    \post El proceso p pasa a ejecutarse y ocupar la memoria del parámetro implícito (el proceso se coloca en la posición más pequeña que deje el hueco más ajustado)
    La función devuelve 'true' si no ha habido ningún error, en caso contrario devuelve 'false'
*/
    bool añadir_proceso(const Proceso& p);

/** @brief Elimina un proceso del parámetro implícito
    \pre <em>cierto</em>
    \post El proceso cuyo id es igual al pasado por parámetro se elimina del parámetro implícito, dejando libre la memoria usada por este proceso
    La función devuelve 'true' si no ha habido ningún error, en caso contrario devuelve 'false'
*/
    bool eliminar_proceso(int id);

/** @brief Avanza el tiempo de todos los procesos que estan siendo ejecutados
    \pre t >= 0
    \post El tiempo de ejecución de todos los procesos del parámetro implícito progresa t unidades de tiempo. Se eliminan todos los procesos que hayan terminado en el interválo de tiempo t
*/
    void avanzar_tiempo(int t);

/** @brief Compacta la memoria del parámetro implícito
    \pre <em>cierto</em>
    \post Todos los procesos del parámetro implícito se mueven al principio de la memoria, sin solaparse, sin dejar huecos y respetando el orden inicial
*/
    void compactar_memoria();

    // Consultores

/** @brief Consultora del identificador
    \pre El parámetro implícito tiene un id inicializado
    \post Devuelve el identificador del parámetro implícito
*/
    string consultar_id() const;

/** @brief Consultora de la memoria disponible
    \pre El parámetro implícito tiene la memoria inicializada
    \post Devuelve la memoria disponible (que no esta ocupada por ningún proceso) del parámetro implícito
*/
    int consultar_memoria_libre() const;

/** @brief Consultora de la existencia de procesos en el parámetro implícito
    \pre <em>cierto</em>
    \post Devuelve 'true' si el parámetro implícito contiene algún proceso, en caso contrario devuelve 'false'
*/
    bool contiene_proceso() const;

/** @brief Consultora de la existencia de un proceso específico
    \pre <em>cierto</em>
    \post Devuelve 'true' si el parámetro implícito contiene el proceso p pasado por parámetro, en caso contrario devuelve 'false'
*/
    bool existe_proceso(int id) const;

/** @brief Consultora de cuan ajustado es el espacio de memoria respecto un proceso
    \pre p tiene un tamaño > 0 y el parámetro implícito tiene la memoria inicializada
    \post Devuelve el tamaño que tiene el hueco de memoria más pequeño que es mas grande i igual que el tamaño pasado por parámetro.
    Si no existe tal hueco, la función devuelve -1
*/
    int hueco_mas_ajustado(int tamaño) const;

    // Lectura y escritura

/** @brief Lee un procesador
    \pre El canal estándar de entrada contiene el id y el tamaño de la memoria de un procesador
    \post El parámetro implícito pasa a tener el identificador y el tamaño leídos por el canal de entrada
*/
    void leer();

/** @brief Imprime en el canal de salida estándar los procesos del parámetro implícito
    \pre <em>cierto</em>
    \post Estan escritos en el canal estándar de salida los procesos del parámetro implícito por orden creciente de posición de memoria, incluyendo la posicíon y el resto de datos de cada proceso.
*/
    void escribir() const;

private:

/** @brief Identificador del procesador */
    string id;

/** @brief Tamaño total de la memoria del procesador*/
    int tamaño_memoria;

/** @brief Memoria libre disponible para almacenar procesos del procesador */
    int memoria_libre;


/** @brief Almacena el id de los procesos en memoria(keys) junto a su posición en memoria(values) */
    map<int,int> id_pos;

/** @brief Almacena las posiciones de los procesos en memoria(keys) junto a los procesos correspondientes(values)*/
    map<int,Proceso> pos_proceso;

/** @brief Almacena los espacios vacios en memoria(keys) junto a las posiciones donde se encuentran los espacios(values)*/
    map<int,set<int>> hueco_pos;

/** @brief Elimina el proceso al que apunta el iterador 
    \pre <em>cierto</em>
    \post El elemento apuntado por el iter
*/
    void eliminar_proceso(map<int, Proceso>::iterator& it);
};
#endif