/** @file AreaEspera.cc
    @brief Código de la clase AreaEspera
*/

#include "AreaEspera.hh"

//--------------------------------Métodos públicos--------------------------------

// Constructores

AreaEspera::AreaEspera() {}

// Modificadores

bool AreaEspera::añadir_prioridad(string id_prioridad, string& error) {
    pair<map<string,Prioridad>::iterator,bool> p = map_prioridades.insert(make_pair(id_prioridad,Prioridad()));

    if (not p.second) {
        error = "ya existe prioridad";
    }
    return p.second;
}

bool AreaEspera::eliminar_prioridad(string id_prioridad, string& error) {
    map<string, Prioridad>::iterator it = map_prioridades.find(id_prioridad);
    
    if (it == map_prioridades.end()) {
        error = "no existe prioridad";
        return false;
    }
    
    if (not it->second.procesos.empty()) {
        error = "prioridad con procesos";
        return false;
    }

    map_prioridades.erase(it);
    return true;
}

bool AreaEspera::añadir_proceso(string id_prioridad, const Proceso& p, string& error) {
    map<string,Prioridad>::iterator it_prioridades = map_prioridades.find(id_prioridad);

    if (it_prioridades == map_prioridades.end()) {
        error = "no existe prioridad";
        return false;
    }
    list<Proceso>::iterator it_procesos = it_prioridades->second.procesos.begin();

    while (it_procesos != it_prioridades->second.procesos.end()) {
        if (p.consultar_id() == (*it_procesos).consultar_id()) {
            error = "ya existe proceso";
            return false;
        }
        ++it_procesos;
    }

    it_prioridades->second.procesos.insert(it_procesos, p);
    return true;
}

void AreaEspera::enviar_procesos_cluster(Cluster& c, int n) {
    map<string, Prioridad>::iterator it_prioridades = map_prioridades.begin();
    while (n > 0 and it_prioridades != map_prioridades.end()) {

        int tam_prioridad = it_prioridades->second.procesos.size();
        while (n > 0 and tam_prioridad > 0) {

            if (c.añadir_proceso(*(it_prioridades->second.procesos.begin()))) {
                ++it_prioridades->second.procesos_colocados;
                --n;
            }
            else {
                it_prioridades->second.procesos.insert(it_prioridades->second.procesos.end(), *(it_prioridades->second.procesos.begin()));
                ++it_prioridades->second.procesos_rechazados;
            }
            it_prioridades->second.procesos.erase(it_prioridades->second.procesos.begin());
            --tam_prioridad;
        }
        ++it_prioridades;
    }
}

// Lectura y escritura

void AreaEspera::leer(int n) {
    string id;
    for (int i = 0; i < n; ++i) {
        cin >> id;
        map_prioridades[id] = Prioridad();
    }
}

bool AreaEspera::imprimir_prioridad(string id_prioridad, string& error) const {
    map<string,Prioridad>::const_iterator it_prioridades = map_prioridades.find(id_prioridad);
    if (it_prioridades == map_prioridades.end()) {
        error = "no existe prioridad";
        return false;
    }
    list<Proceso>::const_iterator it_procesos = it_prioridades->second.procesos.begin();

    while (it_procesos != it_prioridades->second.procesos.end()) {
        (*it_procesos).escribir();
        ++it_procesos;
    }
    cout << it_prioridades->second.procesos_colocados << " " << it_prioridades->second.procesos_rechazados << endl;
    return true;
}

void AreaEspera::imprimir() const {
    map<string,Prioridad>::const_iterator it_prioridades = map_prioridades.begin();
    while (it_prioridades != map_prioridades.end()) {
        cout << it_prioridades->first << endl;

        list<Proceso>::const_iterator it_procesos = it_prioridades->second.procesos.begin();
        while (it_procesos != it_prioridades->second.procesos.end()) {
            (*it_procesos).escribir();
            ++it_procesos;
        }

        cout << it_prioridades->second.procesos_colocados << " " << it_prioridades->second.procesos_rechazados << endl;

        ++it_prioridades;
    }
}

