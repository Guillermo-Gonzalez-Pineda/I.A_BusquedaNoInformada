#include "grafo.hpp"

class EstrategiaBusqueda {
  public:
    virtual nodo buscar(grafo& g, int nodo_inicio, int nodo_objetivo, std::ofstream& archivo_salida, bool imprimir_traza) = 0;
    std::vector<nodo> reconstruirCamino(nodo nodo_objetivo) {
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

    void imprimirArchivoIteracion(int iteracion, std::vector<nodo*> nodos_generados, std::vector<nodo*> nodos_visitados, std::ofstream& archivo_salida) {
      archivo_salida << "Iteración " << iteracion << std::endl;
      archivo_salida << "Nodos generados: ";
      if(!nodos_generados.empty()) {
        if(nodos_generados.size() == 1) {
          archivo_salida << nodos_generados[0]->getID() << std::endl;
        } else {
          for(int i = 0; i < nodos_generados.size() - 1; i++) {
            archivo_salida << nodos_generados[i]->getID() << ", ";
          }
          archivo_salida << nodos_generados[nodos_generados.size() - 1]->getID() << std::endl;
        }
      }
      archivo_salida << "Nodos visitados: ";
      if(!nodos_visitados.empty()) {
        if(nodos_visitados.size() == 1) {
          archivo_salida << nodos_visitados[0]->getID() << std::endl;
        } else {
          for(int i = 0; i < nodos_visitados.size() - 1; i++) {
            archivo_salida << nodos_visitados[i]->getID() << ", ";
          }
          archivo_salida << nodos_visitados[nodos_visitados.size() - 1]->getID() << std::endl;
        }
      }
      archivo_salida << "\n===================================" << std::endl;
    }

    void imprimirArchivoInicio(int num_nodos, int num_aristas, int id_nodo_inicio, int id_nodo_objetivo, std::ofstream& archivo_salida) {
      archivo_salida << "Numero de nodos del grafo: " << num_nodos << std::endl;
      archivo_salida << "Numero de aristas del grafo: " << num_aristas << std::endl;
      archivo_salida << "Vértice Origen: " << id_nodo_inicio << std::endl;
      archivo_salida << "Vértice Destino: " << id_nodo_objetivo << std::endl;
      archivo_salida << "===================================" << std::endl;
    }

    void imprimirInicio(int num_nodos, int num_aristas, int id_nodo_inicio, int id_nodo_objetivo) {
      std::cout << "Numero de nodos del grafo: " << num_nodos << std::endl;
      std::cout << "Numero de aristas del grafo: " << num_aristas << std::endl;
      std::cout << "Vértice Origen: " << id_nodo_inicio << std::endl;
      std::cout << "Vértice Destino: " << id_nodo_objetivo << std::endl;
      std::cout << "===================================" << std::endl;
    }

    void imprimirArchivoCamino(std::vector<nodo> camino, nodo* nodo_actual, std::ofstream& archivo_salida) {
      archivo_salida << "Camino: ";
      for(int i = 0; i < camino.size() - 1; i++) {
        archivo_salida << camino[i].getID() << " - ";
      }
      archivo_salida << camino[camino.size() - 1].getID() << std::endl;
      archivo_salida << "===================================" << std::endl;
      archivo_salida << "Coste: " << nodo_actual->getCosteRama() << std::endl;
      archivo_salida << "===================================" << std::endl;
    }

    void imprimirCamino(std::vector<nodo> camino, nodo* nodo_actual) {
      std::cout << "Camino: ";
      for(int i = 0; i < camino.size() - 1; i++) {
        std::cout << camino[i].getID() << " -> ";
      }
      std::cout << camino[camino.size() - 1].getID() << std::endl;
      std::cout << "===================================" << std::endl;
      std::cout << "Coste: " << nodo_actual->getCosteRama() << std::endl;
      std::cout << "===================================" << std::endl;
    }

  private:
    int suma_coste = 0;
};




class BusquedaAnchura : public EstrategiaBusqueda {
  public:
    nodo buscar(grafo& g, int id_nodo_inicio, int id_nodo_objetivo, std::ofstream& archivo_salida, bool imprimir_traza) override {
      //Imprimimos los datos iniciales
       if (imprimir_traza) {
        imprimirInicio(g.getGrafoSize(), g.getNumAristas(), id_nodo_inicio, id_nodo_objetivo);
      }
      imprimirArchivoInicio(g.getGrafoSize(), g.getNumAristas(), id_nodo_inicio, id_nodo_objetivo, archivo_salida);
      std::queue<nodo*> cola_nodos;      // Cola de nodos a visitar
      std::vector<nodo*> nodos_visitados;  // Se almacenan los nodos que ya se han visitado
      std::vector<nodo*> nodos_generados; // Se almacenan los nodos que se han expandido
      std::map<int, std::map<int, double>> lista_adyacencia = g.getListaAdyacente();

      int iteracion = 1;
      nodo* nodo_inicio = new nodo(id_nodo_inicio);
      nodos_generados.push_back(nodo_inicio);
      cola_nodos.push(nodo_inicio);

      // Imprimir la primera iteración
      if (imprimir_traza) {
        imprimirIteracion(iteracion, nodos_generados, nodos_visitados);
      }
      imprimirArchivoIteracion(iteracion, nodos_generados, nodos_visitados, archivo_salida);

      while (!cola_nodos.empty()) {
        nodo* nodo_actual = cola_nodos.front();
        nodos_visitados.push_back(nodo_actual);
        cola_nodos.pop();

        if(nodo_actual->getID() == id_nodo_objetivo) {
          iteracion++;
          if (imprimir_traza) {
            imprimirIteracion(iteracion, nodos_generados, nodos_visitados);
          }
          imprimirArchivoIteracion(iteracion, nodos_generados, nodos_visitados, archivo_salida);
          
          std::vector<nodo> camino = reconstruirCamino(*nodo_actual);
          if (imprimir_traza) {
            imprimirCamino(camino, nodo_actual);
          }
          imprimirArchivoCamino(camino, nodo_actual, archivo_salida);
          return *nodo_actual;
        }

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
        if (imprimir_traza) {
          imprimirIteracion(iteracion, nodos_generados, nodos_visitados);
        }
        imprimirArchivoIteracion(iteracion, nodos_generados, nodos_visitados, archivo_salida);
      }

      std::cout << "Nodo objetivo no encontrado." << std::endl;
      return nodo(-1);
    }
};

class BusquedaProfundidad : public EstrategiaBusqueda {
  public:
    nodo buscar(grafo& g, int id_nodo_inicio, int id_nodo_objetivo, std::ofstream& archivo_salida, bool imprimir_traza) override {
      if(imprimir_traza) {imprimirInicio(g.getGrafoSize(), g.getNumAristas(), id_nodo_inicio, id_nodo_objetivo);}
      imprimirArchivoInicio(g.getGrafoSize(), g.getNumAristas(), id_nodo_inicio, id_nodo_objetivo, archivo_salida);
      std::stack<nodo*> pila_nodos;      // Pila de nodos a visitar
      std::vector<nodo*> nodos_visitados;  // Se almacenan los nodos que ya se han visitado
      std::vector<nodo*> nodos_generados; // Se almacenan los nodos que se han expandido
      std::map<int, std::map<int, double>> lista_adyacencia = g.getListaAdyacente();

      int iteracion = 1;
      nodo* nodo_inicio = new nodo(id_nodo_inicio);
      pila_nodos.push(nodo_inicio);
      nodos_generados.push_back(nodo_inicio);

      if(imprimir_traza) {imprimirIteracion(iteracion, nodos_generados, nodos_visitados);}    //Imprimir en pantalla
      imprimirArchivoIteracion(iteracion, nodos_generados, nodos_visitados, archivo_salida);

      while(!pila_nodos.empty()) {
        nodo* nodo_actual = pila_nodos.top();
        nodos_visitados.push_back(nodo_actual);
        pila_nodos.pop();
        iteracion++;

        if(nodo_actual->getID() == id_nodo_objetivo) {
          if(imprimir_traza) {imprimirIteracion(iteracion, nodos_generados, nodos_visitados);}    //Imprimir en pantalla
          imprimirArchivoIteracion(iteracion, nodos_generados, nodos_visitados, archivo_salida);
          std::vector<nodo> camino = reconstruirCamino(*nodo_actual);
          if(imprimir_traza) {imprimirCamino(camino, nodo_actual);}       //Imprimir en pantalla
          imprimirArchivoCamino(camino, nodo_actual, archivo_salida);
          return *nodo_actual;
        }

        std::vector<nodo*> hijos_generados;


        for(auto& vecino : lista_adyacencia[nodo_actual->getID()]) {
          bool generado_rama = false;
          nodo* padre = nodo_actual->getPadre();
          while(padre != nullptr) {
            if(padre->getID() == vecino.first) {
              generado_rama = true;
              break;
            }
            padre = padre->getPadre();
          }

          if(!generado_rama) {
            nodo* nodo_vecino = new nodo(vecino.first);
            nodo_vecino->setPadre(nodo_actual);
            int coste_nodo = nodo_actual->getCosteRama() + vecino.second;
            nodo_vecino->setCosteRama(coste_nodo);

            //Guardamos el nodo en la pila
            hijos_generados.push_back(nodo_vecino);
            nodos_generados.push_back(nodo_vecino);
          }

        }

        std::reverse(hijos_generados.begin(), hijos_generados.end());
        for(auto& nodo_temp : hijos_generados) {
          pila_nodos.push(nodo_temp);
        }

        //Marcamos el nodo actual como visitado
        if(imprimir_traza) {imprimirIteracion(iteracion, nodos_generados, nodos_visitados);}
        imprimirArchivoIteracion(iteracion, nodos_generados, nodos_visitados, archivo_salida);
      }

      std::cout << "Nodo objetivo no encontrado." << std::endl;
      return nodo(-1);
    }
};
