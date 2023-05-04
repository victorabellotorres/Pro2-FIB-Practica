/** @file Pocesador.cc
    @brief Código de la clase Procesador
*/

#include "Procesador.hh"

//--------------------------------Métodos públicos--------------------------------

// Constructores

Procesador::Procesador() {
    id = '0';
    tamaño_memoria = 0;
    memoria_libre = 0;
    hueco_pos[0].insert(0);
}

Procesador::Procesador(const string id, const int memoria) {
    this->id = id;
    tamaño_memoria = memoria;
    memoria_libre = memoria;
    hueco_pos[tamaño_memoria].insert(0);
}

// Modificadores

bool Procesador::añadir_proceso(const Proceso& p) {
    map<int,set<int>>::iterator it = hueco_pos.lower_bound(p.consultar_tamaño());

    if (it == hueco_pos.end()) return false;

    // se coloca el proceso en la posicion
    int pos = *(it->second.begin());
 
    pos_proceso[pos] = p;
    id_pos[p.consultar_id()] = pos;
    it->second.erase(it->second.begin());

    int hueco = it->first;
    // si el tamaño del proceso es mas pequeño que el hueco, se actualizan los huecos 
    if (it->first != p.consultar_tamaño()) hueco_pos[hueco - p.consultar_tamaño()].insert(pos + p.consultar_tamaño());
 
    // si no hay mas huecos con el mismo tamaño, se elimina el elemento que contiene el key=hueco
    if (it->second.empty()) hueco_pos.erase(it);

    memoria_libre -= p.consultar_tamaño();

    return true;
}

bool Procesador::eliminar_proceso(int id) {
    map<int,int>::iterator it_id = id_pos.find(id);
    if (it_id == id_pos.end()) return false;

    map<int,Proceso>::iterator it_pos = pos_proceso.find(it_id->second);

    //se elimina el elemento con clave id de la memoria
    id_pos.erase(it_id);
    int pos = it_pos->first;
    int hueco = it_pos->second.consultar_tamaño();

    it_pos = pos_proceso.erase(it_pos);
    int siguiente_hueco = tamaño_memoria - (pos+hueco);
    // en el caso que el proceso eliminado no fuese el último
    if (it_pos != pos_proceso.end()) siguiente_hueco = it_pos->first - (pos+hueco);
    if (siguiente_hueco > 0) {
        map<int,set<int>>::iterator it_hueco = hueco_pos.find(siguiente_hueco);
        //se elimina la posicion donde esta el siguiente hueco
        it_hueco->second.erase(pos+hueco);
        //se elimina el hueco, si no existen mas huecos de ese tamaño
        if (it_hueco->second.empty()) hueco_pos.erase(it_hueco);
    }   
    hueco += siguiente_hueco;


    int anterior_hueco = pos;
    if (it_pos != pos_proceso.begin()) {
        --it_pos;
        anterior_hueco = pos - (it_pos->first + it_pos->second.consultar_tamaño());
    }

    if (anterior_hueco > 0) {
        map<int,set<int>>::iterator it_hueco = hueco_pos.find(anterior_hueco);

        //se elimina la posicion donde esta el anterior_hueco
        it_hueco->second.erase(pos+hueco);

        //se elimina el hueco, si no existen mas huecos de ese tamaño
        if (it_hueco->second.empty()) hueco_pos.erase(it_hueco);

        //se actualiza la posicion
        pos = (it_pos->first + it_pos->second.consultar_tamaño());
    }
    hueco += anterior_hueco;

    hueco_pos[hueco].insert(pos);

    return true;
}

void Procesador::avanzar_tiempo(int t) {
    map<int, Proceso>::iterator it = pos_proceso.begin();

    while (it != pos_proceso.end()) {
        if (it->second.avanzar_tiempo(t)) eliminar_proceso(it->second.consultar_id());
        ++it;
    }
}

// TODO: compactar memorias

// Consultores

string Procesador::consultar_id() const {
    return id;
}

int Procesador::consultar_memoria_libre() const {
    return memoria_libre;
}

bool Procesador::contiene_proceso() const {
    return (id_pos.size() > 0);
}

bool Procesador::existe_proceso(int id) const {
    return id_pos.find(id) != id_pos.end(); 
}

int Procesador::hueco_mas_ajustado(int tamaño) const {
    return *(hueco_pos.lower_bound(tamaño)->second.begin());
}

// Lectura y escritura

void Procesador::leer() {
    cin >> id >> tamaño_memoria;

    memoria_libre = tamaño_memoria;
    id_pos = map<int, int>();
    pos_proceso = map<int, Proceso>();
    hueco_pos = map<int, set<int>>();
    hueco_pos[tamaño_memoria].insert(0);
}

void Procesador::escribir() const {
    map<int,Proceso>::const_iterator it = pos_proceso.begin();

    while (it != pos_proceso.end()) {
        cout << it->first << " ";
        it->second.escribir();
        ++it;
    }
}
