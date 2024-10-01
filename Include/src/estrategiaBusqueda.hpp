#include "grafo.hpp"

class EstrategiaBusqueda {
  public:
    virtual nodo buscar(grafo& g, int nodo_inicio, int nodo_objetivo) = 0;
    std::vector<nodo> reconstruirCamino(nodo nodo_objetivo, std::map<int, std::map<int, int>> lista_adyacencia) {
      std::vector<nodo> camino;
      nodo* actual = &nodo_objetivo; 

      while (actual != nullptr) {
        camino.push_back(*actual);
        actual = actual->getPadre();
      }

      std::reverse(camino.begin(), camino.end());
      return camino;
    }

    void imprimirIteracion(int iteracion, std::vector<int> nodos_generados, std::vector<int> nodos_visitados) {
      std::cout << "Iteración " << iteracion << std::endl;
      std::cout << "Nodos generados: ";
      if(nodos_generados.size() <= 1) {
        std::cout << 1 << std::endl;
      } else {
        for(int i = 0; i < nodos_generados.size() - 1; i++) {
          std::cout << nodos_generados[i] << ", ";
        }
        std::cout << nodos_generados[nodos_generados.size() - 1] << std::endl;
      }
      std::cout << "Nodos visitados: ";
      if(nodos_visitados.size() <= 1) {
        std::cout << 1 << std::endl;
      } else {
        for(int i = 0; i < nodos_visitados.size() - 1; i++) {
          std::cout << nodos_visitados[i] << ", ";
        }
        std::cout << nodos_visitados[nodos_visitados.size() - 1] << std::endl;
      }
    }

    void imprimirInicio(int num_nodos, int num_aristas, int id_nodo_inicio, int id_nodo_objetivo) {
      std::cout << "Numero de nodos del grafo: " << num_nodos << std::endl;
      std::cout << "Numero de aristas del grafo: " << num_aristas << std::endl;
      std::cout << "Vértice Origen: " << id_nodo_inicio << std::endl;
      std::cout << "Vértice Destino: " << id_nodo_objetivo << std::endl;
      std::cout << "===================================" << std::endl;
    }

  private:
    int suma_coste = 0;
};

class BusquedaAnchura : public EstrategiaBusqueda {
  public:
    nodo buscar(grafo& g, int id_nodo_inicio, int id_nodo_objetivo) override {
      //Imprimimos la primera iteración de la búsqueda
      imprimirInicio(g.getGrafoSize(), g.getNumAristas(), id_nodo_inicio, id_nodo_objetivo);
      std::queue<nodo> cola_nodos;        //Se almacenan los nodos, de forma ordenada, que toca explorar
      std::vector<int> nodos_generados;   //Se almacenan los nodos generados para imprimirlos por pantalla
      std::vector<int> nodos_visitados;   //Se almacenan los nodos visitados para imprimirlos por pantalla
      std::map<int, std::map<int, int>> lista_adyacencia = g.getListaAdyacente();   //Almacena los enlaces entre nodos y sus costes

      int iteracion = 1;
      nodos_generados.push_back(id_nodo_inicio);
      cola_nodos.push(nodo(id_nodo_inicio));
      imprimirIteracion(iteracion, nodos_generados, nodos_visitados);
      //Mientras haya nodos en la cola_nodos, realizamos lo siguiente
      while (!cola_nodos.empty()) {
        iteracion++;
        //actual es el nodo al frente de la cola
        nodo actual = cola_nodos.front();
        cola_nodos.pop();

        //Si encontramos el nodo objetivo, terminamos
        if (actual.getID() == id_nodo_objetivo) {
          std::vector<nodo> camino = reconstruirCamino(actual, lista_adyacencia);
          std::cout << "Camino: ";
          for(int i = 0; i < camino.size(); i++) {
            std::cout << camino[i].getID() << " - ";
          }
          std::cout << std::endl;
          std::cout << "Costo: " << actual.getCosteRama() << std::endl;
          return actual;
        }

        //Revisar los vecinos del nodo actual
        for(const auto& vecino : g.getListaAdyacente()[actual.getID()]) {

          //Recorremos la rama en orden inverso hasta llegar al nodo inicial
          bool nodo_generado_rama = false;
          nodo* nodo_temp = &actual;
          while (nodo_temp != nullptr) {
            if (nodo_temp->getID() == vecino.first) {
              nodo_generado_rama = true;
              break;
            }
            nodo_temp = nodo_temp->getPadre();
          }

          //Si el nodo no ha sido generado en su rama
          //Lo añadimos al vector y a la cola
          if (!nodo_generado_rama) {
            //Creamos el nodo vecino y le asignamos un coste y un padre
            nodo nodo_vecino(vecino.first);
            nodo_vecino.setPadre(&actual);
            int coste_nodo = actual.getCosteRama() + vecino.second;
            nodo_vecino.setCosteRama(coste_nodo);

            //Guardamos el nodo creado en la lista de nodos generados y en la cola de nodos
            nodos_generados.push_back(nodo_vecino.getID());
            cola_nodos.push(nodo_vecino);
          }
        }

        //Marcamos el nodo actual como visitado
        nodos_visitados.push_back(actual.getID());
        imprimirIteracion(iteracion, nodos_generados, nodos_visitados);
      }

      std::cout << "Nodo objetivo no encontrado." << std::endl;
      return nodo(-1);

    }
};

class BusquedaProfundidad : public EstrategiaBusqueda {
  public:
    nodo buscar(grafo& g, int nodo_inicio, int nodo_objetivo) override {
      
    }
};