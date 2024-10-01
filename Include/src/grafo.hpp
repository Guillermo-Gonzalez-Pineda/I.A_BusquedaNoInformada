#include "../lib/lib.h"
#include "nodo.hpp"

class grafo {
  public:
    grafo() {};
    grafo(std::string);

    nodo getNodo(int id);
    std::map<int, std::map<int, int>> getListaAdyacente() {return lista_adyacencia_;};
    int getGrafoSize() {return grafo_size_;};
    int getNumAristas() {return num_aristas;};

  private:
    std::map<int, std::map<int, int>> lista_adyacencia_;
    int grafo_size_;
    int num_aristas = 0;
    std::map<int, nodo> cache_nodos_;
};

nodo grafo::getNodo(int id_nodo) {
  if(cache_nodos_.find(id_nodo) == cache_nodos_.end()) {
    cache_nodos_[id_nodo] = nodo(id_nodo);
  }
  return cache_nodos_[id_nodo];
};

grafo::grafo(std::string nombre_archivo) {
  //Abrimos el archivo cuyo nombre nos han pasado por parámetros
  std::ifstream archivo(nombre_archivo);
  if(!archivo.is_open()) {
    std::cerr << "El Archivo no se pudo abrir." << std::endl;
    //Comprobar que no se construyó el grafo
    grafo_size_ = -1;
    return;
  }
  //Leemos el numero de nodos que tiene el grafo
  std::string linea;
  std::getline(archivo, linea);
  grafo_size_ = stoi(linea);
  int id_temp = 0;

  //Recorremos el archivo guardando los costes en la lista de adyacencia
  //En la iteración 1 -> 2, también se almacenará el coste de 2 -> 1.
  //Esto se hará con todos
 	for(int i = 1; i <= grafo_size_; i++) {
		for(int j = i + 1; j <= grafo_size_; j++) {
			std::getline(archivo, linea);
      //Si hay un -1 no se guarda ningún coste.
			if(linea == "-1.00" || linea == "-1,00") {
				continue;
			}
			int coste = stoi(linea);
			lista_adyacencia_[i][j] = coste;
      lista_adyacencia_[j][i] = coste;
      num_aristas++;
		}
	}
}
