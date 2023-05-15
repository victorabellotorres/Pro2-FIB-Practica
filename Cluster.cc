/** @file Cluster.cc
    @brief Código de la clase Cluster
*/

#include "Cluster.hh"

//--------------------------------Métodos públicos--------------------------------

// Constructores

Cluster::Cluster() {
    Procesador p;

    id_tree = BinTree<string>(p.consultar_id());
    map_procesadores = map<string, Procesador>();

    map_procesadores[p.consultar_id()] = p;
}

// Modificadores

bool Cluster::añadir_proceso_procesador(string id_procesador, const Proceso& p, string &error) {
    map<string,Procesador>::iterator it = map_procesadores.find(id_procesador);

    if (it == map_procesadores.end()) {
        error = "no existe procesador";
        return false;
    }
    if (it->second.existe_proceso(p.consultar_id())) {
        error = "ya existe proceso";
        return false;
    }
    if (not it->second.añadir_proceso(p)) {
        error = "no cabe proceso";
        return false;
    }
    return true;
}

bool Cluster::eliminar_proceso_procesador(string id_procesador, int id_proceso,  string& error) {
    map<string,Procesador>::iterator it = map_procesadores.find(id_procesador);

    if (it == map_procesadores.end()) {
        error = "no existe procesador";
        return false;
    }
    if (not it->second.eliminar_proceso(id_proceso)) {
        error = "no existe proceso";
        return false;
    }
    return true;
}

//TODO: añadir proceso

void Cluster::avanzar_tiempo(int t) {
    map<string,Procesador>::iterator it = map_procesadores.begin();

    while (it != map_procesadores.end()) {
        it->second.avanzar_tiempo(t);
        ++it;
    }
}

// TODO: compactar memorias

// Lectura y escritura

void Cluster::leer() {
    map_procesadores = map<string, Procesador>();
    BinTree<string> c;

    leer_recursivo(c, map_procesadores);
    id_tree = c;
}

bool Cluster::imprimir_procesador(string id_procesador, string& error) const {
    map<string,Procesador>::const_iterator it = map_procesadores.find(id_procesador);
    if (it == map_procesadores.end()) {
        error = "no existe procesador";
        return false;
    }
    it->second.escribir();
    return true;
}

void Cluster::imprimir_procesadores() const  {
    map<string,Procesador>::const_iterator it = map_procesadores.begin();

    while (it != map_procesadores.end()) {
        cout << it->first << endl;
        it->second.escribir();
        ++it;
    }
}

void Cluster::imprimir_estructura() const {
    imprimir_estructura_recursivo(id_tree);
    cout << endl;
}

//--------------------------------Métodos privados--------------------------------

void Cluster::leer_recursivo(BinTree<string>& c, map<string,Procesador>& map_proc) {
    string id;
    cin >> id;

    if (id != "*") {
    int memoria;
    cin >> memoria;
    Procesador p(id,memoria);
    map_proc[id] = p;

    BinTree<string> left;
    BinTree<string> right;
    leer_recursivo(left, map_proc);
    leer_recursivo(right, map_proc);
    c = BinTree<string>(id, left, right);
    }
}

void Cluster::imprimir_estructura_recursivo(const BinTree<string>& b) {
    if (not b.empty()){
        cout << "(" << b.value();
        imprimir_estructura_recursivo(b.left());
        imprimir_estructura_recursivo(b.right());
        cout << ")";
    }
    else cout << " ";
}