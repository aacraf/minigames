#include <iostream>
#include <algorithm>
#include <math.h>
#include "escaquer.h"


bool cerca_llista(list<coord>& mov, list<coord>::iterator &it, int cfx, int cfy)
	/*Pre: cert*/
	/*Post: retorna true si les corrdenades cfx i cfy estan dintre de la llista mov*/
{
	bool trobat;
	coord t = *it;
	if(mov.empty()) trobat = false;
	if(t.x == cfx && t.y == cfy) trobat = true;
	else
	{
		++it;
		trobat = cerca_llista(mov,it,cfx,cfy);
	}
	return trobat;
}

bool cerca_coord(vector<coord>& cerca,unsigned int i,unsigned int j)
	/*Pre: i i j seran naturals que indican les coordenades de les caselels*/
	/*Post: retorna true si les coordenades i i j estan dintre del vector de moviments posibles*/
{
	bool trobat = false;
	unsigned int k = 0;
	while(k<cerca.size() && not trobat)
	{
		coord t = cerca[k];
		unsigned int x = t.x;
		unsigned int y = t.y;
		if(x == i && y == j) trobat = true;
		++k;
	}
	return trobat;
}

vector<coord> de_pila_a_cua(queue<list<coord> >& interrogants,vector<coord>&cerca)
	/*Pre: cert*/
	/*Post: retorna un vector amb tots els elements de la cua de llistes*/
{
	list<coord>::iterator it;
	while(not interrogants.empty())
	{
		list<coord> auxiliar = interrogants.front();
		it = auxiliar.begin();
		while(it != auxiliar.end())
		{
			coord t = *it;
			cerca.push_back(t);
			++it;
		}
		interrogants.pop();
	}
	return cerca;
}


///////////////////////////////////////////
//// Implementació de la classe escaquer ///

//---- Constructora. Serveix per declarar una variable
//---- de tipus "escaquer" de mida n x n inicialitzada
//---- amb les peces inicials d'una partida de Dames.
//---- Pre: n és parell i n>=8

escaquer::escaquer(nat n)
  // crea taula de mida n x n
{
  taula = vector<vector<casella> >(n,vector<casella>(n,casella()));

  // inicialitza les caselles del escaquer
	
	for (unsigned int i=0; i<taula.size();i++)
    {
  		for (unsigned int j=0; j<taula.size();j++)
    	{
		int t = j%2;
		if ((i==0 || i==2) && t==1) taula[i][j].omple(casella::NEGRA);
		else if (i==1 && t==0) taula[i][j].omple(casella::NEGRA);
		else if ((i==n-3 || i==n-1) && t==0) taula[i][j].omple(casella::BLANCA);
		else if (i==n-2 && t==1) taula[i][j].omple(casella::BLANCA);
		else taula[i][j].omple(casella::LLIURE);
	  	}
	}
	
}

//---- Diu si les coord p estan dins dels limits del escaquer.
bool escaquer::dins_limits(coord p) const
  /*Pre: cert*/
  /*Post: retorna true si la coordenada es troba dins dels limits del taulell*/
{
  bool res = false;
  unsigned int x = p.x;
  unsigned int y = p.y;
  if(x < taula.size() and y < taula.size() and x >= 0 and y >= 0) res = true;
  return res;
}

//---- Accedeix a la casella de la coord p del escaquer.
casella& escaquer::operator()(coord p) {
  /*Pre: cert*/
  /*Post: retorna la casella correspoent a la coordenada donada*/
  return taula[p.x][p.y];
}

//---- Escriu a la pantalla el contingut del escaquer.
void escaquer::mostra() const {
  /*Pre: el size del taulel ha de estar entre 8 i 100*/
  /*Post: escriu per pantalla el contingut del escaquer.*/

	unsigned int size = taula.size();

	cout<<" ";
	if(size > 9)cout << " ";

	for(unsigned int i =1 ; i <= size; ++i)
	{
		cout << " ";
		if(size > 9 and i <= 9) cout << "0";
		cout << i ;
	}

	cout << endl;

	for (unsigned int i = 0; i < size; ++i) {
	  if (size > 9 and i < 9) cout << "0";
	  cout << i+1 ;
	  for (unsigned int j = 0; j < size; j++){
	      if (size > 9) cout << " ";
	        cout << " " << taula[i][j].mostra();
	  }
	  cout << endl;
	}

}

//---- Escriu a la pantalla el contingut del escaquer marcant amb '?'
//---- les caselles on es poden posar fitxes del color donat.
void escaquer::mostra(int color) const {
	/*Pre: -3<color<=2*/
	/*Post: escriu per pantalla el contingut del escaquer marcant amb '?' les caselles on es 		poden posar fitxes del color donat*/

	queue<list<coord> > interrogants;
	vector<coord> cerca;
	int color2;
	unsigned int size = taula.size()-1;
	if(color == casella::BLANCA ) color2 = casella::DAMA_BLANCA;
	else if (color == casella::NEGRA) color2 = casella::DAMA_NEGRA;

	if(pot_jugar(color))
	{
		for(unsigned int i = 0; i<=size; ++i)
	{
			for(unsigned int j = 0; j<=size; ++j)
			{
				if(taula[i][j].valor() == color or taula[i][j].valor() == color2)
				{
					/*Omple una cua de llistes amb tots els moviments posibles que te un color*/
					list<coord>aux = mov_possibles(coord(i,j));
					interrogants.push(aux);
				}
			}
		}
	}

	//Posem els moviments posibles que estan en la cua de llistes a un vector
	cerca = de_pila_a_cua(interrogants, cerca);

	cout<<" ";
	if(size > 9)cout << " ";

	for(unsigned int i =1 ; i <= size+1; ++i)
	{
		cout << " ";
		if(size > 9 and i <= 9) cout << "0";
		cout << i ;
	}

	cout << endl;

	for (unsigned int i = 0; i <= size; ++i) {
		if (size > 9 and i < 9) cout << "0";
		cout << i+1 ;
		for (unsigned int j = 0; j <= size; j++){
				cout<<" ";
				if (size > 9) cout << " ";
				if(cerca_coord(cerca, i, j)) cout<<"?";
				else cout<<taula[i][j].mostra();
		}
		cout << endl;
	}

}

//---- Avalua les fitxes del escaquer:
//---- num_caselles_blanques - num_caselles_negres
int escaquer::avalua() const {
  /*Pre: cert */
  /*Post: torna el numero de fitxes restants en el taulell*/
  int num_caselles_blanques = 0, num_caselles_negres = 0;
  for(unsigned int i = 0; i<taula.size(); ++i)
  {
    for(unsigned int j = 0; j<taula.size(); ++j)
    {
	  int valor = taula[i][j].valor();
      if(valor == casella::BLANCA or valor == casella::DAMA_BLANCA) num_caselles_blanques += valor;
      else if(valor == casella::NEGRA or valor == casella::DAMA_NEGRA) num_caselles_negres += valor;
    }
  }
  return num_caselles_blanques + num_caselles_negres;
}

//---- Comprova si es pot despl desde la coordenada cini en la direcció d
//---- Retorna: despl (si es pot despl o no), c (coordenada final després del moviment)
void escaquer::es_pot_despl(coord cini, direccio d, bool &despl, coord &c) const {
  /*Pre: 0<=d<=4*/
  /*Post: modifica despl si la fitxa es pot moure i c sera la coordenada final despres del 			moviment*/
	c = cini + d.despl();


	if(dins_limits(c) and taula[c.x][c.y].valor() == 0) despl = true;
	else despl = false;
}

//---- Comprova si es pot capturar desde la coordenada cini en la direcció d
//---- Retorna: capturar (si es pot capturar o no), c (coordenada final després de la captura)
void escaquer::es_pot_capturar(coord cini, direccio d, bool &capturar, coord &c) const
	/*Pre: 0<=d<=4*/
  	/*Post: modifica a true capturar si pots capturar la fitxa i modifica les coordenades de c despres de la captura*/
{
	int color = taula[cini.x][cini.y].valor();
	if(dins_limits(cini + d.despl()))
	{

		c = cini + d.despl();
		int color_captura = taula[c.x][c.y].valor();

		if((dins_limits(c) && color>casella::LLIURE && color_captura<casella::LLIURE)) capturar = true;
		else if((dins_limits(c) && color<casella::LLIURE && color_captura>casella::LLIURE)) capturar = true;
		else
		{
			capturar = false;
			c = cini;
		}
		if(capturar)
	  	{
			coord aux;
			aux = c + d.despl();
			if(dins_limits(aux) and taula[aux.x][aux.y].valor() == 0)
			{
				c = aux;
			}
			else
			{
					capturar = false;
					c = cini;
			}
		}
	}
	else c = cini;
}

//---- Comprova si es pot posar una peça de color de la coordena c:
//---- Cal comprovar si en una de les 4 direccions hi ha una peça dama del color
//---- o bé en los 2 direccions una peça del color
//---- també es poden capturar fitxes de l'adversari (de color diferent al color donat).
list<coord> escaquer::mov_possibles(coord c) const
	/*Pre: cert*/
	/*Post: retrorna una llista de coordenades amb els moviments possibles a la coordenada c*/
{
	list<coord>res;
	list<coord>::iterator it = res.begin();
	direccio d;
	coord cdesp;
	bool despl = false, capturar = false;
	int color = taula[c.x][c.y].valor();
	while(not d.is_stop() && dins_limits(c))
	{
		if((color == casella::BLANCA && d.getDireccio()<2) || color == casella::DAMA_BLANCA || color == casella::DAMA_NEGRA || (color == casella::NEGRA && d.getDireccio()>1))
		{
			if(dins_limits(c+d.despl()))
			{
				es_pot_despl(c, d, despl, cdesp);
				if(despl) res.insert(it, cdesp);
				es_pot_capturar(c,d,capturar,cdesp);
				if(capturar) res.insert(it, cdesp);
			}
		}
		++d;
	}
	return res;
}

//---- Comprova si el color pot jugar (la peça de color es pot col·locar en algun lloc).
bool escaquer::pot_jugar(int color) const
	/*Pre: -2<=color<=2*/
	/*Post: retrorna true si el color te algun moviment posible*/
 {
	//bool trobat=false;
	int color2;

	if(color == casella::BLANCA ) color2 = casella::DAMA_BLANCA;
	else if (color == casella::NEGRA) color2 = casella::DAMA_NEGRA;

	for(unsigned int i = 0; i < taula.size(); i++){
		for(unsigned int j = 0; j < taula.size(); j++){
			if(taula[i][j].valor() == color or taula[i][j].valor() == color2)
			{
				list<coord> aux = mov_possibles(coord(i,j));
				if(not aux.empty()) return true;
			}
		}
	}
	return false;
}

//---- Col·loca la fitxa de color a la coordena c i captura les fitxes (si es poden capturar) segons regles de les dames
//---- S'avalua si realment es pot posar la fitxa o no
bool escaquer::posa_fitxa(coord c, coord cf, int color)
	/*Pre: -2<=color<=2**/
	/*Post: retorna true si s'ha pogut efectuar el moviment dins del taulell*/
{
	bool res=false, despl=false, capturar=false;
	coord cini(c.x, c.y);
	int ccolor = taula[c.x][c.y].valor();
	coord cfinal(cf.x,cf.y);
	direccio d;
	unsigned int x = cf.x;
	while(not d.is_stop() && not res && pot_jugar(color) && ccolor != casella::LLIURE)
	{
		es_pot_capturar(c,d,capturar,cf);
		if(capturar && cf == cfinal)
		{
			res = true;
			c = c + d.despl();
			taula[cini.x][cini.y].omple(casella::LLIURE);
			taula[c.x][c.y].omple(casella::LLIURE);
			taula[cf.x][cf.y].omple(color);
		}
		else
		{
			es_pot_despl(c,d,despl,cf);
			cout<<"";/*sense aquest cout, el compilador no funciona be*/
			if(despl && cf == cfinal)
			{
				res = true;
				taula[c.x][c.y].omple(casella::LLIURE);
				taula[cf.x][cf.y].omple(color);
			}
		}
		++d;
	}
	if(res)
	{
		//En cas de que la fitxa de color es trobi al final del taulell, es converteix en dama
		if(color == casella::BLANCA && cf.x == 0){
			taula[cf.x][cf.y].omple(casella::DAMA_BLANCA);
			cout<<endl<<"Enhorabona has aconseguit una DAMA!! ";
		}
		else if(color == casella::NEGRA && x == taula.size()-1)
		{
			taula[cf.x][cf.y].omple(casella::DAMA_NEGRA);
			cout<<endl<<"Enhorabona has aconseguit una DAMA!! ";
		}
	}
	return res;
}
