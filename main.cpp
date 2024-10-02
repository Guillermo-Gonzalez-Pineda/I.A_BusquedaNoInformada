#include "Include_/src/estrategiaBusqueda.hpp"

int main(int argc, char* argv[]) {
  if(argc >= 3) {
    std::cerr << "La ejecución del programa es: ./busqueda_no_informada 'Archivo-Grafo'" << std::endl;
    return 1;
  }
  //Traduce el archivo que ha pasado el usuario a una cadena de texto
  std::string nombre_fichero(argv[1]);
  //Carga el grafo desde el archivo
  grafo g(nombre_fichero);

  //Verificamos si el grafo se cargó correctamente
  if(g.getGrafoSize() == -1) {
    std::cerr << "Error al construir el grafo." << std::endl;
    return 1;
  }
  

  //Solicitamos al usuario un nodo inicial y un nodo objetivo.
  int id_nodo_inicial = 0;
  int id_nodo_objetivo = 0;
  //Comprobamos que ninguno de los dos es mayor o menos que el tamaño del grafo 
  do {
    std::cout << "Elija un nodo inicial:" << std::endl;
    std::cin >> id_nodo_inicial;
    std::cout << "\nElija un nodo objetivo:" << std::endl;
    std::cin >> id_nodo_objetivo;
  } while(id_nodo_inicial < 1 || id_nodo_inicial > g.getGrafoSize() || id_nodo_objetivo < 1 || id_nodo_objetivo > g.getGrafoSize());

  //Solicitamos al usuario un estilo de búsqueda
  int tipo_busqueda = 0;
  std::cout << "Elija el tipo de búsqueda a realizar: " << std::endl;
  std::cout << "    1) Busqueda en Amplitud." << std::endl;
  std::cout << "    2) Busqueda en Profundidad." << std::endl;
  std::cin >> tipo_busqueda;

  EstrategiaBusqueda* algoritmo_busqueda = nullptr;
  nodo resultado;
  if(tipo_busqueda == 1) {
    algoritmo_busqueda = new BusquedaAnchura();
    resultado = algoritmo_busqueda->buscar(g, id_nodo_inicial, id_nodo_objetivo);
  } else if(tipo_busqueda == 2) {
    algoritmo_busqueda = new BusquedaProfundidad();
    //algoritmo_busqueda->buscar(g, id_nodo_inicial, id_nodo_objetivo);
  } else {
    std::cerr << "Debe seleccionar un metodo de busqueda valido" << std::endl;
  }

  if(resultado.getID() != -1) {
    std::cout << "Nodo Objetivo " << id_nodo_objetivo << " encontrado." << std::endl;
  } else {
    std::cout << "No se pudo encontrar el nodo objetivo." << std::endl;
  }
  
  return 0;
}