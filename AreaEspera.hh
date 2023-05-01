/** @file AreaEspera.hh
    @brief Especificación de la clase AreaEspera
*/

#ifndef AREAESPERA_HH
#define AREAESPERA_HH

#include "Proceso.hh"
#include "Cluster.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <queue>
#endif
using namespace std;

/** @class AreaEspera
    @brief Representa un área de espera de procesos

    Permite almacenar y gestionar procesos pendientes de distintas prioridades y enviar procesos a un clúster.
*/
class AreaEspera
{
public:
    // Constructores
    
/** @brief Constructora por defecto
    \pre <em>cierto</em>
    \post El resultado es un área de espera sin ninguna prioridad ni proceso
*/
    AreaEspera();

    // Modificadores

/** @brief Añade una prioridad al parámetro implícito
    \pre <em>cierto</em>
    \post Se añade al parámetro implícito una prioridad vacía que tiene el id pasado por parámetro
    La función devuelve 'true' si no ha habido ningún error, en caso contrario devuelve 'false' y el mensaje de error contenido en el parámetro error (si ya existe una prioridad con el mismo id)
*/
    bool añadir_prioridad(string id_prioridad, string& error);

/** @brief Elimina una prioridad del parámetro implícito
    \pre <em>cierto</em>
    \post Se elimina del parámetro implícito la prioridad que tenga el id pasado por parámetro
    La función devuelve 'true' si no ha habido ningún error, en caso contrario devuelve 'false' y el mensaje de error contenido en el parámetro error (si no existe una prioridad con el mismo id o si esta tiene procesos pendientes)
*/
    bool eliminar_prioridad(string id_prioridad, string& error);

/** @brief Añade un proceso a una prioridad específica
    \pre <em>cierto</em>
    \post Se añadre el proceso p pasado por parámetro de la prioridad cuyo id se indica por parámetro.
    La función devuelve 'true' si no ha habido ningún error, en caso contrario devuelve 'false' y el mensaje de error contenido en el parámetro error (si no existe una prioridad con el id indicado o si ya existe este proceso en la prioridad)
*/
    bool añadir_proceso(string id_prioridad, const Proceso& p, string& error);

/** @brief Se intentan colocar n procesos pendientes a un clúster por orden de prioridad
    \pre <em>cierto</em>
    \post Se han intentado enviar n procesos pendientes del parámetro implícito al clúster pasado por parámetro, enviando primero por orden de prioridad, y dentro de la misma prioridad primero los procesos más antiguos
    Se continuan enviando procesos pendiantes hasta se hayan colocado n procesos, o se hayan acabado los procesos, o hasta que todos los procesos pendientes se hayan intentado colocar sin éxito (los procesos rechazados vuelven al área como si fueran nuevos)
    También se actualizan los contadores de procesos rechazados de la prioridad
*/
    void enviar_procesos_cluster(Cluster& c, int n);

    // Consultores

    // Lectura y escritura

/** @brief Lee un número n de prioridades
    \pre El canal estándar de entrada contiene los identificadores de n prioridades
    \post El parámetro implícito contiene n prioridades cuyos identificadores han sido leidos por el canal estándar de entrada 
*/
    void leer(int n);

/** @brief Imprime en el canal estándar de salida los procesos pendientes de una prioridad
    \pre <em>cierto</em>
    \post Estan escritos en el canal estándar de salida los procesos pendientes de una prioridad por orden decreciente de antigüedad
    Además de el número de procesos de la prioridad colocados y rechazados en el clúster por la operación 'envier_procesos_cluster'
    La función devuelve 'true' si no ha habido ningún error, en caso contrario devuelve 'false' y el mensaje de error contenido en el parámetro error (si no existe una prioridad con el id indicado)
*/
    bool imprimir_prioridad(string id_prioridad, string& error) const;

/** @brief Imprime en el canal estándar de salida los procesos pendientes de todas las priorirades 
    \pre <em>cierto</em>
    \post Estan escritos en el canal estándar de salida los procesos por orden decreciente de antigüedad de todas las prioridades, por orden creciente de prioridad.
    Además, se escribe el número de procesos de cada prioridad colocados y rechazados en el clúster por la operación 'envier_procesos_cluster'
*/
    void imprimir() const;

private:
};

#endif