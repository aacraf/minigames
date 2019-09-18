#include <string>

#include "coord.h"

//---- Definició del tipus "direccio", que enumera els valors
//---- possibles de la direcció que podem mirar des d'una
//---- casella qualsevol. Aquest tipus té l'operador d'autoincrement,
//---- que permet modificar una variable de tipus "direccio" amb el valor
//---- de la direcció següent en el sentit de les agulles del rellotge.

class direccio {
   public:
     ///--- Llista de direccions possibles, més STOP per marcar
     ///--- que no n'hi ha més.
     enum dirs {NO,NE,SE,SO,STOP};
     ///--- Crear una direcció nova, amb el primer valor de la llista.
     direccio();

     ///--- Obtenir la direcció
     int getDireccio() const;
	 /*Pre: cert*/
	 /*Post: retorna el numero correspoent a la llista de 			direccions*/

     ///--- Veure si el valor de la direcció és el del final de la llista.http://cpp.sh/
     bool is_stop() const;
     /*Pre: cert*/
  	 /*Post: retorna true si el es troba en STOP, que es el ultim 		element de la llista*/

     ///--- Canviar el valor de la direcció, posant-li el primer de la llista.
     void init();
     /*Pre: cert*/
  	 /*Post: la direccio sera el primer element de la llista 		   	enumerada*/

     ///--- Canviar el valor de la direcció pel següent de la llista.
     ///--- Permet usar instruccions "++d" (on d és de tipus direcció).
     ///--- No es pot avançar més enllà de la posició STOP
     direccio& operator++();
     /*Pre: cert*/
     /*Post: mou el punter una posicio cap endevant excepte si ja es troba a la ultima posicio*/

     ///--- Obtenir les components x,y que significa un moviment en
     ///--- en aquesta direcció. P.ex NE -> (-1,1)
     coord despl() const;
    /*Pre: posicio a la que estas de la enum*/
    /*Post: retorna una coordenada que dependra de la direccio a assolir*/ 
	

     ///--- Obtenir un string amb el nom de la direcció.
     ///--- Aquest mètode és útil per fer debugging.
     std::string mostra() const;
     /*Pre: posicio a la que estas de la enum*/
     /*Post: un string que ens indica en quina diraccio estem anant*/
   private:
     dirs d;
};
