#include "Include_/src/estrategiaBusqueda.hpp"

int main(int argc, char* argv[]) {
  if(argc >= 4) {
    std::cerr << RED << "La ejecución del programa es: ./busqueda_no_informada 'Archivo-Grafo' 'Archivo-Salida'" << RESET << std::endl;
    return 1;
  }

  //Traduce el archivo que ha pasado el usuario a una cadena de texto
  std::string nombre_fichero(argv[1]);
  std::string nombre_salida(argv[2]);
  //Carga el grafo desde el archivo
  grafo g(nombre_fichero);

  //Verificamos si el grafo se cargó correctamente
  if(g.getGrafoSize() == -1) {
    std::cerr << RED << "Error al construir el grafo." << RESET << std::endl;
    return 1;
  }

  std::ofstream archivo_salida(nombre_salida);
  if(!archivo_salida.is_open()) {
    std::cerr << RED << "El archivo no pudo abrirse." << RESET << std::endl;
  }

  //Solicitamos al usuario un nodo inicial y un nodo objetivo.
  int id_nodo_inicial = 0;
  int id_nodo_objetivo = 0;
  //Comprobamos que ninguno de los dos es mayor o menos que el tamaño del grafo 
  /*do {
    std::cout << CYAN << "Elija el nodo inicial:" << RESET << std::endl;
    std::cin >> id_nodo_inicial;
    
    std::cout << CYAN << "\nElija el nodo objetivo:" << RESET << std::endl;
    std::cin >> id_nodo_objetivo;
  } while(id_nodo_inicial < 1 || id_nodo_inicial > g.getGrafoSize() || id_nodo_objetivo < 1 || id_nodo_objetivo > g.getGrafoSize());
  */

  std::cout << CYAN << "\nElija el nodo inicial:" << RESET << std::endl;
  std::cin >> id_nodo_inicial;

  std::cout << CYAN << "\nElija el nodo objetivo:" << RESET << std::endl;
  std::cin >> id_nodo_objetivo;

  //Solicitamos al usuario un estilo de búsqueda
  int tipo_busqueda = 0;
  std::cout << MAGENTA << "\nElija el tipo de búsqueda a realizar: " << RESET << std::endl;
  std::cout << MAGENTA << "-------------------------------------" << RESET << std::endl;
  std::cout << GREEN << "    1) Búsqueda en Amplitud. (BFS)" << RESET << std::endl;
  std::cout << GREEN << "    2) Búsqueda en Profundidad. (DFS)" << RESET << std::endl;
  std::cout << GREEN << "    3) Búsqueda en Anchura Modificación" << RESET << std::endl;
  std::cin >> tipo_busqueda;


  std::string respuesta;
  bool imprimir_traza_pantalla = false;
  std::cout << MAGENTA << "¿Desea imprimir en pantalla la traza?  Y/N" << RESET << std::endl;
  std::cin >> respuesta;

  if(respuesta == "Y" || respuesta == "y" || respuesta == "yes" || respuesta == "YES") {
    imprimir_traza_pantalla = true;
  }
  

  EstrategiaBusqueda* algoritmo_busqueda = nullptr;
  nodo resultado;

  if(tipo_busqueda == 1) {
    algoritmo_busqueda = new BusquedaAnchura();
    resultado = algoritmo_busqueda->buscar(g, id_nodo_inicial, id_nodo_objetivo, archivo_salida, imprimir_traza_pantalla);
  } else if(tipo_busqueda == 2) {
    algoritmo_busqueda = new BusquedaProfundidad();
    resultado = algoritmo_busqueda->buscar(g, id_nodo_inicial, id_nodo_objetivo, archivo_salida, imprimir_traza_pantalla);
  } else if(tipo_busqueda == 3) {
    algoritmo_busqueda = new BusquedaAnchuraModificacion();
    resultado = algoritmo_busqueda->buscar(g, id_nodo_inicial, id_nodo_objetivo, archivo_salida, imprimir_traza_pantalla);
  } else {
    std::cerr << RED << "Debe seleccionar un metodo de busqueda valido" << RESET << std::endl;
  }

  if(resultado.getID() != -1) {
    std::cout << GREEN << "Nodo Objetivo " << id_nodo_objetivo << " encontrado." << RESET << std::endl;
  } else {
    std::cout << RED << "No se pudo encontrar el nodo objetivo." << RESET << std::endl;
  }
  
  return 0;
}