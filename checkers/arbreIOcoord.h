#ifndef ARBREIOINT_H 
#define ARBREIOINT_H
#include "arbre.h"
#include "escaquer.h"
#include <iostream>
using namespace std;
   
ostream& operator<<(ostream &os, const arbre<coord> &x);
/* Pre: cert */
/* Post: s'han escrit al canal estandard de sortida els elements de x */  

#endif
