/** @file Cluster.cc
    @brief Código de la clase Cluster
*/

#include "Cluster.hh"

//--------------------------------Métodos públicos--------------------------------

// Constructores

Cluster::Cluster() {
    Procesador p;

    arbol_ids = BinTree<string>(p.consultar_id());
    map_procesadores = map<string, Procesador>();

    map_procesadores[p.consultar_id()] = p;
}

// Modificadores

bool Cluster::modificar(string id_procesador, string& error) {
    map<string, Procesador>::iterator it = map_procesadores.find(id_procesador);
    
    if (it == map_procesadores.end()) {
        error = "no existe procesador";
        return false;
    } else if (it->second.contiene_proceso()) {
        error = "procesador con procesos";
        return false;
    }

    BinTree<string> arbol_final;

    if (not añadir_arbol(id_procesador, arbol_ids, arbol_final)) {
        error = "procesador con auxiliares";
        return false;
    }

    arbol_ids = arbol_final;
    return true;
}

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

bool Cluster::añadir_proceso(const Proceso& p) {
    queue<BinTree<string>> cola_ids;
    map<string, Procesador>::iterator it_mejor_procesador;
    int max_hueco_mas_ajustado = 0;
    int max_memoria_libre = 0;

    cola_ids.push(arbol_ids);
    while(not cola_ids.empty()) {
        if (not cola_ids.front().left().empty()) cola_ids.push(cola_ids.front().left());
        if (not cola_ids.front().right().empty()) cola_ids.push(cola_ids.front().right());

        map<string, Procesador>::iterator it = map_procesadores.find(cola_ids.front().value());
        if (not it->second.existe_proceso(p.consultar_id())) {
            int hueco = it->second.hueco_mas_ajustado(p.consultar_tamaño());
            if (hueco > 0) {
                // cuando se encuentra el primer procesador con hueco > 0
                if (max_hueco_mas_ajustado == 0) {

                    it_mejor_procesador = it;
                    max_memoria_libre = it_mejor_procesador->second.consultar_memoria_libre();
                    max_hueco_mas_ajustado = hueco;
                }
                else if (hueco <= max_hueco_mas_ajustado) {
                    if (hueco == max_hueco_mas_ajustado) {

                        if (it->second.consultar_memoria_libre() > max_memoria_libre) {
                            it_mejor_procesador = it;
                            max_memoria_libre = it->second.consultar_memoria_libre();
                        }
                    }
                    else {
                        it_mejor_procesador = it;
                        max_memoria_libre = it_mejor_procesador->second.consultar_memoria_libre();
                        max_hueco_mas_ajustado = hueco;
                    }
                }
            }
        }

        cola_ids.pop();
    }

    if (max_hueco_mas_ajustado > 0) {
        it_mejor_procesador->second.añadir_proceso(p);
        return true;
    } else return false;
}

void Cluster::avanzar_tiempo(int t) {
    map<string,Procesador>::iterator it = map_procesadores.begin();

    while (it != map_procesadores.end()) {
        it->second.avanzar_tiempo(t);
        ++it;
    }
}

bool Cluster::compactar_memoria_procesador(string id_procesador, string& error) {
    map<string, Procesador>::iterator it = map_procesadores.find(id_procesador);
    
    if (it == map_procesadores.end()) {
        error = "no existe procesador";
        return false;
    }
    it->second.compactar_memoria();
    return true;
}

void Cluster::compactar_memoria() {
    map<string, Procesador>::iterator it = map_procesadores.begin();

    while (it != map_procesadores.end()) {
        it->second.compactar_memoria();
        ++it;
    }
}

// Lectura y escritura

void Cluster::leer() {
    map_procesadores = map<string, Procesador>();
    leer_recursivo(arbol_ids, map_procesadores);
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
    imprimir_estructura_recursivo(arbol_ids);
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

bool Cluster::añadir_arbol(string id_procesador, const BinTree<string>& arbol_original, BinTree<string>& arbol_final) {
    if (not arbol_original.empty()) {
        if (arbol_original.value() == id_procesador) {

            if (not arbol_original.left().empty() or not arbol_original.right().empty()) {
                leer_datos_arbol_aux();
                return false;
            }
            leer_recursivo(arbol_final, map_procesadores);
            map_procesadores.erase(arbol_original.value());
        }
        else {
            BinTree<string> arbol_derecha;
            BinTree<string> arbol_izquierda;
            if (not añadir_arbol(id_procesador, arbol_original.left(), arbol_izquierda)) return false;
            if (not añadir_arbol(id_procesador, arbol_original.right(), arbol_derecha)) return false;
            
            arbol_final = BinTree<string>(arbol_original.value(), arbol_izquierda, arbol_derecha);
        }
    }
    return true;
}

void Cluster::leer_datos_arbol_aux() {
    string id;
    cin >> id;

    if (id != "*") {
    int memoria;
    cin >> memoria;
    leer_datos_arbol_aux();
    leer_datos_arbol_aux();
    }
}

