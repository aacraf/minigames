#include <sstream>
#include "coord.h"

using namespace std;

string IntAString(int n)
	/*Pre: n es un integer*/
	/*Post: retorna n en format string*/
{
   stringstream ss;
   ss << n;
   return ss.str();
}

///////////////////////////////////////////
//// Implementació de la classe coord ///

//---- Crear un parell de coordenades sense valor inicial
coord::coord() { }

//---- Crear un nou parell de coordenades, amb valor (a,b)
coord::coord(int a, int b) {
  x = a;
  y = b;
}

//---- Suma a la coordenada actual el parell de coordenades donat.
//---- Per exemple:  t=(3,4) i z=(-1,2),  tindrem t+z = (2,6)
coord coord::operator+(const coord& c) const 
	/*Pre: c conte dos integers*/
	/*Post: retorna una variable tipus coord amb la suma de cadascun dels seus elements de int x, y; forma independent*/
{
  coord res;
  res.x = c.x + x;
  res.y = c.y + y;
  return res;
}

//---- Compara la coordenada actual el parell de coordenades donat.
bool coord::operator==(const coord &c) const 
	/*Pre: c conte dos integers*/
	/*Post: retorna true si les x son iguals i les y son iguals*/
{
  bool trobat = false;
  if(c.x == x and c.y == y) trobat = true; 
  return trobat;
}

//---- Retorna un string amb el contingut de la coordenada entre paréntesis.
//---- Aquest mètode és útil per fer debugging.
//---- Per exemple si x=3 i y=-1, mostra retornaria "(3,-1)"
string coord::mostra() const {
	/*Pre: cert*/
	/*Post: retorna una string amb les components x i y*/
  string res = "("+ IntAString(x)+","+IntAString(y)+")";
  return res;
}

//---- Retorna un string amb el contingut de la coordenada entre paréntesis
//---- sumant 1 a cada component. Aquest mètode és útil per fer debugging.
//---- Per exemple si x=3 i y=-1, mostra1 retornaria "(4,0)"
string coord::mostra1() const {
	/*Pre: cert*/
	/*Post: retorna una string amb les components x i y sumanli 1 a cada component*/
  string res = "("+ IntAString(x+1)+","+IntAString(y+1)+")";
  return res;
}
