#include <iostream>
#include "arbreIOcoord.h"   /*Inclou escaquer*/

using namespace std;

bool cerca_llista(list<coord>& mov,int cfx, int cfy)
	/*Pre: cert*/
	/*Post: retorna true si les corrdenades cfx i cfy estan dintre de la llista mov*/
{
	bool trobat = false;
	list<coord>::iterator it = mov.begin();

	while(it != mov.end() && not trobat)
	{
		coord t = *it;
		if(t.x == cfx && t.y == cfy) trobat = true;
		else ++it;
	}
	return trobat;
}

bool cerca_coord(vector<coord>& cerca, coord t)
	/*Pre: i i j seran naturals que indican les coordenades de les caselels*/
	/*Post: retorna true si les coordenades i i j estan dintre del vector de moviments posibles*/
{
	bool trobat = false;
	unsigned int k = 0;
	while(k<cerca.size() && not trobat)
	{
		coord p = cerca[k];
		if(p.x == t.x && p.y == t.y) trobat = true;
		++k;
	}
	return trobat;
}

pair<int,int> fitxas(escaquer& e,unsigned int n)
	/*Pre: el numero n sera natural i postiu*/
	/*Post:retornara el numero de fitxes blanques i de fitxes 		negres que hi han al tauler en aquell moment.*/
{
  int num_caselles_blanques = 0, num_caselles_negres = 0;
  for(unsigned int i = 0; i<n; ++i)
  {
    for(unsigned int j = 0; j<n; ++j)
    {
	  coord aux(i,j);
	  int valor = e(aux).valor();
      if(valor == casella::BLANCA or valor == casella::DAMA_BLANCA) ++num_caselles_blanques;
      else if(valor == casella::NEGRA or valor == casella::DAMA_NEGRA) ++num_caselles_negres;
    }
  }
  pair<int,int> fitxas = make_pair(num_caselles_blanques, num_caselles_negres);
  return fitxas;
}

void jugador(escaquer& e, int torn)
	/*Pre: el numero n sera natural i postiu*/
	/*Post: mostrara per pantalla la capçalera indicant quin 		jugador te el torn en aquell moment, i tambe mostra lestat
actual del tauler amb els moviments posibles que te aquell jugador.*/
{
	if(torn == casella::BLANCA)
	{
		cout << endl<<"========== Jugador B =========="<<endl;
		e.mostra(torn);
		cout<<"================================"<<endl<<endl;
	}
	else if(torn == casella::NEGRA)
	{
		cout << endl<<"========== Jugador N =========="<<endl;
		e.mostra(torn);
		cout<<"================================"<<endl<<endl;
	}
	else
	{
		cout << endl<<"========== LLIURE =========="<<endl;
		e.mostra();
		cout<<"================================"<<endl<<endl;
	}
}
void es_victoria(escaquer& e, bool& victoria, unsigned int n)
	/*Pre: el numero n sera natural i postiu*/
	/*Post: escriura per pantalla quin jugador a guanyat o si encara estan jugant, que van empatats i posa a true el bool victoria que necessitem en altres funcions*/
{
	pair<int,int> fitxas_taula = fitxas(e,n);//mirem cauntes fitxes de cada jugador queden
	if(fitxas_taula.first == 0 or fitxas_taula.second == 0) victoria = true;
	else if(not e.pot_jugar(casella::BLANCA) || not e.pot_jugar(casella::NEGRA)) victoria = true;
	else
	{
		/// Avaluem l'escaquer
	  int val = e.avalua();
	  if (val > 0)
		cout<<"Guanyen les Blanques";
	  else if (val < 0)
		cout<<"Guanyen les Negres";
	  else
		cout<<"EMPAT";
	}
}

int altura(arbre<coord> &a)
	/*Pre: Un arbre de coordenades,*/
	/*Post: retorna laltura de l'arbre*/

 {
  int nnodes;
  if (a.es_buit()) nnodes = 0; //Cas base, en cas de que larbre estigui buit laltura es 0 automaticament
  else {//Calcula recursivament l'altura dels fills de l'arbre i li suma la arrel.
    arbre<coord> a1 = a.fe();
    arbre<coord> a2 = a.fd();
    int y = altura(a1);
    int z = altura(a2);
    if(y>z) nnodes = y+1; /*Controlem que no retorni la suma*/
	else nnodes = z + 1;
  }
  return nnodes;
}

void crear_arbre(escaquer &e, arbre<coord>& a, coord cini, direccio d, int& damas_blancas)
	/*Pre: Un arbre de coordenades i una coordenada que sigui dincs del tauler */
	/*Post: retorna un arbre amb una fulla inserida, depenent de la direccio a la que es mogui la fitxa, es creara una nova fulla dreta o esquerra.*/
{
	coord cfin;
 	arbre<coord>buit;
	int alt = altura(a);
	while(not d.is_stop() && alt!= 0)
	{
		bool capturar = false;
		e.es_pot_capturar(cini, d, capturar, cfin);
		if(capturar &&  e(coord(cini+d.despl())).valor() == 2) ++damas_blancas;
		if(capturar)
		{
			/*DAMAS*/
			if (d.getDireccio() == 0) a = arbre<coord> (cini, arbre<coord>(cfin, buit, buit), a.fd());
			else if (d.getDireccio() == 1) a = arbre<coord> (cini, a.fe(), arbre<coord>(cfin, buit, buit));

			else if (d.getDireccio() == 2) a = arbre<coord> (cini, arbre<coord>(cfin, buit, buit), a.fd());
			else if (d.getDireccio() == 3) a = arbre<coord> (cini, a.fe(), arbre<coord>(cfin, buit, buit));
		}
		++d;
	}
}

arbre<coord> omple_arbre(escaquer &e, arbre<coord>& a, coord cini, direccio d,int& damas_blancas,unsigned int n)
	/*Pre: Un arbre de coordenades i una coordenada que sigui dincs del tauler*/
	/*Post: retorna un arbre amb les diferents captures que es poden fer i depenent de si la catura es cap a lest o cap a loest, les posicions finsals de la captura es coloquen als fills drets o esquerres, respectivament*/
{
  if (not a.es_buit()) {
    crear_arbre(e, a, cini, d, damas_blancas); /*te saco los hijops*/

    arbre<coord> fe = a.fe();
    arbre<coord> fd = a.fd();

		/*creem una copia per tal de no modificar el taulell*/
		escaquer copia(n);
		copia = e;

    if(not fe.es_buit())
		{
			copia.posa_fitxa(a.arrel(),fe.arrel(),e(a.arrel()).valor());
			omple_arbre(copia,fe,fe.arrel(),d, damas_blancas,n);
		}
		copia = e; //tornem a agafar la copia
    if(not fd.es_buit())
		{
			copia.posa_fitxa(a.arrel(),fd.arrel(),e(a.arrel()).valor());
			omple_arbre(copia,fd,fd.arrel(),d, damas_blancas,n);
		}
		arbre<coord> aux = arbre<coord>(a.arrel(), fe, fd);
		a = aux;
  }
	return a;
}

vector<arbre<coord> > buscar_camins(list<arbre<coord> > &ordinador,vector<int>& damas)
	/*Pre: cert*/
	/*Post: Retorna un vector amb larbre o els arbres que tenen la altura mes gran*/
{
	list<arbre<coord> >::iterator it = ordinador.begin();
	vector<int>::iterator it2 = damas.begin();

	        /*!!!*/
	vector<arbre<coord> > res;
	vector<int> temp;

	while(it != ordinador.end() && it2 != damas.end())
	{
		if(altura(*it)>= 2)
		{
			int maxim = altura(*it);
			arbre<coord> aux = *it;
			int x = *it2;
			if(altura(aux) > maxim)
			{
				temp.clear();
				res.clear(); /*Reinicia el vector*/
				maxim = altura(aux);
				res.push_back(aux);
				temp.push_back(x);
			}
			else if(altura(aux) == maxim) //En cas de que el nou arbre tingui una altura major a larbre que ja teniem, es neteja el vector i es guarda el nou arbre.
			{
					res.push_back(aux);
					temp.push_back(x);
			}
			++it;
			++it2;
		}
		else ++it;
	}
	damas = temp;
	return res;
}

bool tots_iguals(vector<int>& damas)
	/*Pre: cert*/
	/*Post: retorna un bool indicant true si s'ha trobat que el contungut de damas es diferent entre ell*/
{
	bool trobat = false;
	for(unsigned int i = 0; i<damas.size() && not trobat; i++)
	{
		if(damas[i] != damas[i+1]) trobat = true;
	}
	return trobat;
}

arbre<coord> cami_arbre(list<arbre<coord> > &ordinador, vector<int>& damas)
	/*Pre: cert*/
	/*Post: retorna el arbre que pugui capturar mes dames, o en cas de que dos arbres puguin capturar el mateix nombre de dames, escullira un dels dos arbres aleatoriament*/
{
	arbre<coord> res;
	vector<int> aux;
	vector<arbre<coord> > rand;
	vector<arbre<coord> > camins = buscar_camins(ordinador, damas);
	int count = 0;

	if(camins.size() > 1 && not tots_iguals(damas))//En cas de que hi hagui mes de un arbre i capturin diferentes damas
	{

			/*COMPROVA EL ARBRE AMB MES DAMAS*/
		for(unsigned int i = 0; i<damas.size();++i)
		{
			if(damas[i]<damas[i+1])
			{
					rand.clear();
					rand.push_back(camins[i+1]);
					++count;
			}
			else
			{
				rand.push_back(camins[i]);
				++count;
			}
		}
		res = rand[0];
	}
	else if(camins.size() == 1)
	{
		int i = 0;
		res = camins[i];
	}
	else{
		res= arbre<coord>();
	}
	return res;
}

void fer_captura(escaquer &e, arbre<coord>& a,int torn)
	/*Pre: el pi no esta buit*/
	/*Post: Es mou realment les fitxes d'una casella a una altre del tauler*/
{
	arbre<coord> fe = a.fe();
	arbre<coord> fd = a.fd();
	int x = e(a.arrel()).valor();

	if(not a.fe().es_buit() && altura(fe)>=altura(fd))
	{
			e.posa_fitxa(a.arrel(), fe.arrel(), x);
			fer_captura(e,fe, x);
	}
	else if(not a.fd().es_buit())
	{
			e.posa_fitxa(a.arrel(), fd.arrel(), x);
			fer_captura(e,fd, x);
	}
}

void TornOrdinador(escaquer &e, int torn, unsigned int n, bool &victoria)
	/*Pre: El nombre n es un nombre natural i sense signe */
	/*Post: Crea una llista amb tots els moviments posibles que te el jugador negre. Ls llista esta omplerta per els arbres dels moviments posibles, incloses les posibles captures i captures consecutives.*/
{
	list<arbre<coord> >ordinador;
	vector<int> damas;
	list<arbre<coord> >::iterator it = ordinador.begin();
	direccio d;
	while(not d.is_stop())
	{
		for (unsigned int i = 0; i<n; i++)
		{
			for(unsigned int j = 0; j<n; j++)
			{
			 	int x = e(coord(i,j)).valor();
				if(x == torn && d.getDireccio()==2 && not e.mov_possibles(coord(i,j)).empty())
				{
					int damas_blancas = 0;
					arbre<coord> a(coord(i,j),arbre<coord>(),arbre<coord>());
					a = omple_arbre(e,a,coord(i,j),d,damas_blancas,n);
					ordinador.insert(it, a);
					damas.push_back(damas_blancas);
				}
				else if (x == casella::DAMA_NEGRA && not e.mov_possibles(coord(i,j)).empty())
				{
					arbre<coord> a(coord(i,j),arbre<coord>(),arbre<coord>());
					arbre<coord> b(coord(i,j),arbre<coord>(),arbre<coord>());

					/*DAMAS*/
					if(d.getDireccio()<2)
					{
						int damas_blancas = 0;
						a = omple_arbre(e,a,coord(i,j),d,damas_blancas,n);
						ordinador.insert(it,a);
						damas.push_back(damas_blancas);
					}
					else
					{
						int damas_blancas = 0;
						b = omple_arbre(e,a,coord(i,j),d,damas_blancas,n);
						ordinador.insert(it,b);
						damas.push_back(damas_blancas);
					}
				}
			}
		}
		++d;
	}

	/*Omplim el arbre de captura*/
	arbre<coord> res = cami_arbre(ordinador,damas);


	if(not res.es_buit())
	{
	cout<<"L'arbre construit es "<<endl;
	cout<<res;
	cout<<endl<<"i té alçada "<<altura(res)-1<<endl;
	}


	if(not res.es_buit()) /*Fem les captures corresponents al arbre*/
	{
		fer_captura(e,res,torn);
		jugador(e,torn);
		cout<<endl<<"Es el torn del ordinador "<<endl;
		if(e.pot_jugar(torn)) TornOrdinador(e, torn, n, victoria);
	}
	else     /*Moviment aleatori*/
	{
		vector<coord> aleatori;
		for(unsigned int i = 0; i<n; i++)
		{
			for(unsigned int j = 0; j<n; j++)
			{
				coord t = coord(i,j);
				if((e(t).valor() == torn or e(t).valor() == casella::DAMA_NEGRA) && not e.mov_possibles(t).empty())
				{
					aleatori.push_back(t);
				}
			}
		}
		int i = rand() % aleatori.size();
		coord mov(aleatori[i]);
		list<coord> mov_aleatori = e.mov_possibles(mov);
		list<coord>::iterator it2= mov_aleatori.begin();
		vector<coord> movs_finals;
		while(it2 != mov_aleatori.end())
		{
			coord t = *it2;
			movs_finals.push_back(t);
			++it2;
		}
		int x = rand() % movs_finals.size();
		coord mov_final = movs_finals[x];
		e.posa_fitxa(mov, mov_final, torn);
	}
}


void TornJugador(escaquer &e, int torn, unsigned int n, bool& victoria, int opcio)
	/*Pre: El nombre n es un nombre natural i sense signe */
	/*Post: Mou la fitxa indicada a la posicio indicada. Sempre que la fitxa que es vol moure es pugui moure i es donin caselles existents i que es tracti del jugador blanc, el torn del jugador negre crida a la funcio tornordinador per a que es realitzin els moviments automaticament.*/

{

	int fila, columna, filaf, columnaf;
	cout<<"Casella Origen ";
	cout<<endl<<"Fila i Columna (1-8): ";cin>>fila>>columna;
	coord cini(fila-1,columna-1);
	if(not e.dins_limits(cini)) victoria = true;
	else
	{
		cout<<endl<<"Casella Final ";
		cout<<endl<<"Fila i Columna (1-8): ";cin>>filaf>>columnaf;
		coord cfin(filaf-1,columnaf-1);


		list<coord> mov;
		if(not e.dins_limits(cfin)) victoria = true;
		else
		{
			int color2;
			if((e(cini).valor() == casella::BLANCA)) color2 = casella::DAMA_BLANCA;
			else if(e(cini).valor() == casella::NEGRA) color2 = casella::DAMA_NEGRA;

		 if ((e(cini).valor() == casella::LLIURE)||not (e(cfin).valor() == casella::LLIURE)||(not cerca_llista(mov = 				e.mov_possibles(cini), filaf-1, columnaf-1))||((e(cini).valor() != torn) && (e(cini).valor() != color2)))
		{
			cout<< endl <<"Error: Posició ja ocupada o moviment no vàlid."<<endl;
			TornJugador(e,torn,n,victoria,opcio);
		}
		else
		{
			int x = e(cini).valor();
			int fitxini = e.avalua();
			if(e.posa_fitxa(cini, cfin, x))
			{
				int fitxfin = e.avalua();
				if(fitxfin != fitxini)
					{
						jugador(e, torn);
						es_victoria(e, victoria, n);
						cout<<endl;
						if(torn == casella::NEGRA && opcio==2) TornOrdinador(e,torn,n,victoria);
						else TornJugador(e,torn, n,victoria,opcio);
					}
			}
		}
		}
	}
}

int comprovar_torn(escaquer &e,int torn)
	/*Pre: torn a de ser -1 o 1*/
	/*Post: retorna el torn al jugador contrari al que esta jugant actualment*/
{
	if(torn == casella::BLANCA)
	{
		if(e.pot_jugar(casella::NEGRA)) torn = casella::NEGRA;
	}
	else if(torn == casella::NEGRA)
	{
		if(e.pot_jugar(casella::BLANCA)) torn = casella::BLANCA;
	}
	return torn;
}


int main()
{
	unsigned int n, opcio;
	cout<<endl<<"La Dimensió de l'escaquer ha de ser múltiple de 2 i 8 com a minim "<<endl;
	cout<<"Quina és la Dimensió ? : "; cin>>n;
	cout<<endl;
	/// Creem un escaquer nxn
	cout<<"Les Opcions disponibles son (1) Bàsic (2) Especial "<<endl;
	cout<<"Quina opció vols ? : "; cin>>opcio;
	escaquer e(n);
	int torn = casella::BLANCA;
	bool victoria = false;

	//util::neteja();
	//util::espera(2);

	while(e.pot_jugar(torn) && not victoria)
	{
		/*Mostra el taulell*/
		 /*ESTP*/

		jugador(e, torn);
		//mirem el estat de la partida
		es_victoria(e, victoria, n);
		if(torn == casella::NEGRA && opcio == 2) cout<<endl<<"Es el torn del ordinador "<<endl;
		cout<<endl;
		/*Moviments*/
		if(opcio == 2 && torn == casella::NEGRA) TornOrdinador(e,torn,n,victoria);
		else TornJugador(e, torn, n,victoria,opcio);
		/*comprovar torn*/
		torn = comprovar_torn(e, torn);
		//util::neteja();
		//util::espera(2);
	}
	cout << endl<<"FINAL DE PARTIDA !! "<<endl;
	cout <<"===================="<<endl;;
	e.mostra();
	int val = e.avalua();
	if (val > 0) cout<<endl<<"Guanyen les Blanques";
	else if (val < 0) cout<<endl<<"Guanyen les Negres";
	else if(not e.pot_jugar(casella::BLANCA) || not e.pot_jugar(casella::NEGRA)) cout<<endl<<"TAULES";
	else cout<<endl<<"EMPAT";
}
