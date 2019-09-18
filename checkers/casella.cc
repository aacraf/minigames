#include <iostream>
#include "casella.h"

///////////////////////////////////////////
//// Implementació de la classe casella ///

//---- Crea una casella amb valor inicial LLIURE.
casella::casella() {
	color = LLIURE;
	visitada = false;
}

//---- Modifica el color de la casella.
void casella::omple(int x)
	/*Pre: x es un enter*/
	/*Post: modifica variable color depenent de l'enter donat*/
{
	if (x == 1) color = BLANCA;
	else if ( x == 2 ) color = DAMA_BLANCA;
	else if ( x == -1 ) color = NEGRA;
	else if ( x == -2 ) color = DAMA_NEGRA;
	else color = LLIURE;
}

//---- Marcar la casella com a visitada.
void casella::marca()
	/*Pre: cert*/
	/*Post: modifica la variable que indica si una casella ha estat visitada a true*/
{
	visitada = true;
}

//---- Desmarca la casella (no visitada).
void casella::desmarca()
	/*Pre: cert*/
	/*Post: modifica la variable que indica si una casella ha estat visitada o no a false*/
{
	visitada = false;
}

//---- Obté el contingut de la casella.
int casella::valor() const
	/*Pre: cert*/
	/*Post: retorna el valor de cada casella que indicara el color*/
{
	return color;
}

//---- Obté el el caràcter de la casella a dibuxar:
//---- BLANCA -> B, DAMA_BLANCA ->Q, NEGRA -> N, DAMA_NEGRA ->P, LLIURE -> -
char casella::mostra() const
	/*Pre: cert*/
	/*Post: retorna un caracter que determina quina peca es troba en el taulell */
{
	char res;
	if ( color == BLANCA ) res = 'B';
	else if ( color == DAMA_BLANCA ) res = 'Q';
	else if ( color == NEGRA ) res = 'N';
	else if ( color == DAMA_NEGRA ) res = 'P';
	else res = '-';
	return res;
}

//---- Consulta si la casella esta marcada com visitada.
bool casella::es_visitada() const
	/*Pre: cert*/
	/*Post: retorna si la casella ha estat visitada o no*/
{
	return visitada;
}
