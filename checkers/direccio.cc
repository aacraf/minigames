#include "direccio.h"
using namespace std;

///////////////////////////////////////////
//// Implementació de la classe direcció ///

///--- Crear una direcció nova, amb el primer valor de la llista.
direccio::direccio() {
  d = NO;
}

///--- Obtenir la direcció
int direccio::getDireccio() const
  /*Pre: cert*/
  /*Post: retorna el numero correspoent a la llista de direccions*/
{
	return d;
}


///--- Veure si el valor de la direcció és el del final de la llista.
bool direccio::is_stop() const {
  /*Pre: cert*/
  /*Post: retorna true si el es troba en STOP, que es el ultim element de la llista*/
  bool trobat = false;
  if (d == STOP) trobat = true;
  return trobat;
}

///--- canviar el valor de la direccio, posant-li el primer de la llista
void direccio::init() {
  /*Pre: cert*/
  /*Post: la direcc50io sera el primer element de la llista enumerada*/
  d = NO;
}

///--- Canviar el valor de la direcció pel següent de la llista.
///--- Permet usar instruccions "++d" (on d és de tipus direcció).
direccio& direccio::operator++() {
  /*Pre: cert*/
  /*Post: mou el punter una posicio cap endevant excepte si ja es troba a la ultima posicio*/
  if (d != STOP) d=dirs(d+1);
  return (*this);
}

///--- Obtenir les components x,y que representen un moviment
///--- en aquesta direcció. P.ex  N -> (-1,0), NE -> (-1,1)
coord direccio::despl() const {
  /*Pre: posicio a la que estas de la enum*/
  /*Post: retorna una coordenada que dependra de la direccio a assolir*/
  coord res;
  if(d == NO) res = coord(-1,-1);
  else if(d == NE) res = coord(-1,1);
  else if(d == SE) res = coord(1,-1);
  else if(d == SO) res = coord(1,1);
  else res = coord(0,0);
  return res;
}

///--- Obtenir un string amb el nom de la direcció.
///--- Aquest mètode és útil per fer debugging.
std::string direccio::mostra() const {
  /*Pre: posicio a la que estas de la enum*/
  /*Post: un string que ens indica en quina diraccio estem anant*/
  //string res;
  string res;
  if(d == NO) res ="NO";
  else if(d == NE) res = "NE";
  else if(d == SE) res = "SE";
  else if(d == SO) res = "SO";
  else res = "STOP";
  return res;
}
