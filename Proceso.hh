/** @file Proceso.hh
    @brief Especificación de la clase Proceso
*/

#ifndef PROCESO_HH
#define PROCESO_HH

#ifndef NO_DIAGRAM
#include <iostream>
#endif
using namespace std;

/** @class Proceso
    @brief Representa un proceso

    Permite consultar datos, imprimirlos en el canal de salida y avanzar su tiempo de ejecución
*/
class Proceso
{
public:
    // Constructores

/** @brief Constructora por defecto
    \pre <em>cierto</em>
    \post El resultado es un proceso con un id, tamaño y tiempo no inicializados
*/
    Proceso();

    // Modificadores

/** @brief Modificadora del tiempo
    \pre El parámetro implícito tiene el tiempo inicializado y t >= 0
    \post El tiempo de ejecución del parámetro implícito progresa t unidades de tiempo.
*/
    void avanzar_tiempo(int t);

    // Consultores

/** @brief Consultora del identificador
    \pre El id del parámetro implícito esta inicializado
    \post La función devuelve el id del parámetro implícito
*/
    int id() const;

/** @brief Consultora del tamaño
    \pre El tamaño del parámetro implícito esta inicializado
    \post La función devuelve el tamaño del parámetro implícito
*/
    int tamaño() const;

/** @brief Consultora del tiempo
    \pre El tiempo del parámetro implícito esta inicializado
    \post La función devuelve el tiempo del parámero implícito
*/
    int tiempo() const;

    // Lectura y escritura

/** @brief Lee los datos de un proceso
    \pre El canal estándar de entrada contiene el id, tamaño y tiempo de un proceso
    \post El id, tamaño y tiempo del parámetro implícito pasan a tener el valor leido en el canal estándar de entrada
*/
    void leer();

/** @brief Escribe los datos de un proceso
    \pre El parámetro implícito tiene el id, tamaño y tiempo inicializados
    \post Esta escrito en el canal estándar de salida el id, tamaño y tiempo del parámetro implícito
*/
    void escribir() const;

private:
};
#endif