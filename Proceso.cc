/** @file Proceso.cc
    @brief Código de la clase Proceso
*/

#include "Proceso.hh"

//--------------------------------Métodos públicos--------------------------------

// Constructores

Proceso::Proceso() {
    id = 0;
    tamaño = 0;
    tiempo = 0;
}

// Modificadores

bool Proceso::avanzar_tiempo(int t) {
    tiempo -= t;
    if (t < 0) t = 0;

    return tiempo <= 0;
}

// Consultores

int Proceso::consultar_id() const {
    return id;
}

int Proceso::consultar_tamaño() const {
    return tamaño;
}

int Proceso::consultar_tiempo() const {
    return tiempo;
}

//Lectura y escritura

void Proceso::leer() {
    cin >> id >> tamaño >> tiempo;
}

void Proceso::escribir() const {
    cout << id << " " << tamaño << " " << tiempo << endl;
}




