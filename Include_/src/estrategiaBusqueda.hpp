#include "grafo.hpp"

class EstrategiaBusqueda {
  public:
    virtual nodo buscar(grafo& g, int nodo_inicio, int nodo_objetivo) = 0;
    std::vector<nodo> reconstruirCamino(nodo nodo_objetivo, std::map<int, std::map<int, double>> lista_adyacencia) {
      std::vector<nodo> camino;
      nodo* actual = &nodo_objetivo; 

      while (actual != nullptr) {
        camino.push_back(*actual);
        actual = actual->getPadre();
      }

      std::reverse(camino.begin(), camino.end());
      return camino;
    }

    void imprimirIteracion(int iteracion, std::vector<nodo*> nodos_generados, std::vector<nodo*> nodos_visitados) {
      std::cout << "Iteración " << iteracion << std::endl;
      std::cout << "Nodos generados: ";
      if(!nodos_generados.empty()) {
        if(nodos_generados.size() == 1) {
          std::cout << nodos_generados[0]->getID() << std::endl;
        } else {
          for(int i = 0; i < nodos_generados.size() - 1; i++) {
            std::cout << nodos_generados[i]->getID() << ", ";
          }
          std::cout << nodos_generados[nodos_generados.size() - 1]->getID() << std::endl;
        }
      }
      std::cout << "Nodos visitados: ";
      if(!nodos_visitados.empty()) {
        if(nodos_visitados.size() == 1) {
          std::cout << nodos_visitados[0]->getID() << std::endl;
        } else {
          for(int i = 0; i < nodos_visitados.size() - 1; i++) {
            std::cout << nodos_visitados[i]->getID() << ", ";
          }
          std::cout << nodos_visitados[nodos_visitados.size() - 1]->getID() << std::endl;
        }
      }
      std::cout << "\n===================================" << std::endl;
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
      //Imprimimos los datos iniciales
      imprimirInicio(g.getGrafoSize(), g.getNumAristas(), id_nodo_inicio, id_nodo_objetivo);
      std::queue<nodo*> cola_nodos;      // Cola de nodos a visitar
      std::vector<nodo*> nodos_visitados;  // Se almacenan los nodos que ya se han visitado
      std::vector<nodo*> nodos_generados; // Se almacenan los nodos que se han expandido
      std::map<int, std::map<int, double>> lista_adyacencia = g.getListaAdyacente();

      int iteracion = 0;
      nodo* nodo_inicio = new nodo(id_nodo_inicio);
      nodos_generados.push_back(nodo_inicio);
      cola_nodos.push(nodo_inicio);
      imprimirIteracion(iteracion, nodos_generados, nodos_visitados);

      while (!cola_nodos.empty()) {
        nodo* nodo_actual = cola_nodos.front();
        nodos_visitados.push_back(nodo_actual);
        cola_nodos.pop();

        for(auto& vecino  : lista_adyacencia[nodo_actual->getID()]) {
          bool nodo_generado = false;
          nodo* padre = nodo_actual->getPadre();
          while(padre != nullptr) {
            if(padre->getID() == vecino.first) {
              nodo_generado = true;
              break;
            }
            padre = padre->getPadre();
          }
          if(nodo_actual->getID() == id_nodo_objetivo) {
            iteracion++;
            imprimirIteracion(iteracion, nodos_generados, nodos_visitados);
            std::vector<nodo> camino = reconstruirCamino(*nodo_actual, lista_adyacencia);
            std::cout << "Camino : ";
            //imprimir el camino con "-" entre los nodos, excepto el último
            for(int i = 0; i < camino.size() - 1; i++) {
              std::cout << camino[i].getID() << " - ";
            }
            std::cout << camino[camino.size() - 1].getID() << std::endl;
            std::cout << "===================================" << std::endl;
            std::cout << "Coste: " << nodo_actual->getCosteRama() << std::endl;
            std::cout << "===================================" << std::endl;
            return *nodo_actual;
          }
          if(!nodo_generado) {
            nodo* nodo_vecino = new nodo(vecino.first);
            nodo_vecino->setPadre(nodo_actual);
            int coste_nodo = nodo_actual->getCosteRama() + vecino.second;
            nodo_vecino->setCosteRama(coste_nodo);

            //Guardamos el nodo en la cola y en el vector de nodos generados
            cola_nodos.push(nodo_vecino);
            nodos_generados.push_back(nodo_vecino);
          }
        }

        //Marcamos el nodo actual como visitado
        iteracion++;
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