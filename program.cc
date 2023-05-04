/** @file pro2.cc
    @brief Programa principal
*/

#include "AreaEspera.hh"
#include "Cluster.hh" // redundante pero necesario para el diagrama

#ifndef NO_DIAGRAM
#include <iostream>
#endif

int main()
{
    Cluster c;
    c.leer();
    int n;
    cin >> n;
    AreaEspera ae;
    ae.leer(n);

    string comando, error;
    cin >> comando;
    while (comando != "fin") {
        
        if (comando == "configurar_cluster" or comando == "cc") {
            c.leer();
            cout << "#" << comando << endl;
        }
        // else if (comando == "modificar_cluster" or comando == "mc") {
        //     string id_procesador;
        //     cin >> id_procesador;
        //     Cluster c_aux;
        //     c_aux.leer();
        //     if (not c.modificar(id_procesador, c_aux, error)) cout << "error: " << error << endl;
        // }
        else if (comando == "alta_prioridad" or comando == "ap") {
            string id_prioridad;
            cin >> id_prioridad;
            cout << "#" << comando << " " << id_prioridad << endl;
            if (not ae.añadir_prioridad(id_prioridad, error)) cout << "error: " << error << endl;
        }
        else if (comando == "baja_prioridad" or comando == "bp") {
            string id_prioridad;
            cin >> id_prioridad;
            cout << "#" << comando << " " << id_prioridad << endl;
            if (not ae.eliminar_prioridad(id_prioridad, error)) cout << "error: " << error << endl;
        }
        else if (comando == "alta_proceso_espera" or comando == "ape") {
            string id_prioridad;
            cin >> id_prioridad;
            Proceso p;
            p.leer();
            cout << "#" << comando << " " << id_prioridad << " " << p.consultar_id() << endl;
            if (not ae.añadir_proceso(id_prioridad, p, error)) cout << "error: " << error << endl;
        }
        else if (comando == "alta_proceso_procesador" or comando == "app") {
            string id_procesador;
            cin >> id_procesador;
            Proceso p;
            p.leer();
            cout << "#" << comando << " " << id_procesador << " " << p.consultar_id() << endl;
            if (not c.añadir_proceso_procesador(id_procesador, p, error)) cout << "error: " << error << endl;
        }
        else if (comando == "baja_proceso_procesador" or comando == "bpp") {
            string id_procesador;
            int id_proceso;
            cin >> id_procesador >> id_proceso;
            cout << "#" << comando << " " << id_procesador << " " << id_proceso << endl;
            if (not c.eliminar_proceso_procesador(id_procesador, id_proceso, error)) cout << "error: " << error << endl;
        }
        // else if (comando == "enviar_procesos_cluster") {
        //     int n;
        //     cin >> n;
        //     ae.enviar_procesos_cluster(c, n);
        // }
        else if (comando == "avanzar_tiempo" or comando == "at") {
            int t;
            cin >> t;
            cout << "#" << comando << " " << t << endl;
            c.avanzar_tiempo(t);
        }
        else if (comando == "imprimir_prioridad" or comando == "ipri") {
            string id_prioridad;
            cin >> id_prioridad;
            cout << "#" << comando << " " << id_prioridad << endl;
            if (not ae.imprimir_prioridad(id_prioridad, error)) cout << "error: " << error << endl;
        }
        else if (comando == "imprimir_area_espera" or comando == "iae") {
            cout << "#" << comando << endl;
            ae.imprimir();
        }
        else if (comando == "imprimir_procesador" or comando == "ipro") {
            string id_procesador;
            cin >> id_procesador;
            cout << "#" << comando << " " << id_procesador << endl;
            if (not c.imprimir_procesador(id_procesador, error)) cout << "error: " << error << endl;
        }
        else if (comando == "imprimir_procesadores_cluster" or comando == "ipc") {
            cout << "#" << comando << endl;
            c.imprimir_procesadores();
        }
        else if (comando == "imprimir_estructura_cluster" or comando == "iec") {
            cout << "#" << comando << endl;
            c.imprimir_estructura();
        }
        // else if (comando == "compactar_memoria_procesador" or comando == "cmp") {
        //     string id_procesador;
        //     if (not c.compactar_memoria_procesador(id_procesador, error)) cout << "error: " << error << endl;
        // }
        // else if (comando == "compactar_memoria_cluster" or comando == "cmc") {
        //     c.compactar_memoria();
        // }
        cin >> comando;
    }
}