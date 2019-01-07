//Nuria Galera & Achraf Hmimou
//FOPR (EPSEVG)

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

typedef char matriu[7][10]; // Definim el tipus de matriu on anira el dibuix de la matriu

vector <string> obtindre_coleccio_de_paraules(){
	//Pre: Agafa un archiu de text de la carpeta
	//Post: Retorna un vector implert amb les paraules de l'artxiu de text.

    vector<string> paraules;
    ifstream file_input_stream("paraules.txt");
        
    string x;

    while(file_input_stream>>x){

        paraules.push_back(x);

    }
    file_input_stream.close();
    return paraules;
}

int numero_aleatori(int a){
	//Pre: Agafa el tamany del vector paraules.
	//Post:	Et retorna un numero aleatori dintre del rang [0, paraules.size()]
    srand(time(NULL));
    
    int num_aleatori = rand();
    return num_aleatori % a;
}

string obtindre_paraula_aleatoria(){
	//Pre: Agafa la coleccio de paraules i un num aleatori
	//Post: Et retorna una paraula aleatoria.
    vector<string> paraules = obtindre_coleccio_de_paraules();
    int num_aleatori = numero_aleatori(paraules.size());

    return paraules[num_aleatori];
}

void partides(int &partidas_guanyades, int &partidas_perdudes){
    //Pre: Funcio que agafa els contadors de partides guanyades/perdudes, el boolea que determina si s'ha guanyat i el contador que determina si has perdut
    //Post: Treu per pantalla el contador de partides guanyades i el contador de partides perdudes.

    cout<<"Partides Guanyades : "<< partidas_guanyades<<endl;
    cout<<"Partides Perdudes : "<< partidas_perdudes<<endl;

}

void mostrar_matriz(const matriu & mort){
     // Fa un cout de la matriu
	for(int i = 0; i<7; i++){
		for(int j = 0; j<10; j++){
			cout<<mort[i][j];
		}		
	cout<<endl;
	}
}

void penjat(int n, matriu &mort) {
    // Va omplint la matriu buida amb els diferents elements del pengat
	if(n == 1){

		for(int j = 1; j<5; j++){ 
		mort[6][j] = '-';
		}
	}
	if(n == 2){
		for(int i = 1; i < 5; i++){	
		mort[i][3] = '|';
		}
	}
	if(n == 3){
		
		for(int j = 3; j<8; j++){	
		mort[0][j] = '-';
		}
	}
	if(n == 4){
		mort[1][8] = '|';	
	}
	if(n == 5){
		mort[2][8] = 'O';

	}
	if(n == 6){
		mort[3][8] = '|';
		mort[4][8] = '|';
	}
	if(n == 7){
		mort[3][7] = '/';
	}
	if(n == 8){
		mort[3][9] = '\\';
	}
	if(n == 9){
		mort[5][7] = '/';
	}
	if(n == 10){
		mort[5][9] = '\\';
		
	}

}

bool compara(const string & x, vector <char> & paraula, char y){
	//Pre:agafar la lletra i el vector.
	//Post:agafara la lletra i ens dira si pertany al vector, si la lletra perany la completara i si no existeix retornara 		false.
	bool trobat=false;
	
	for (unsigned int i=0; i < x.size(); i++) {

		if(x[i]==y){paraula[i]=y;
			trobat=true;
		}
	}
	return trobat;

}

bool iguals(const string & x, const vector <char> & paraula){
	//Pre: Agafa paraula i vector.
	//Post: Et diu si la paraula i el vecor son iguals.Si es cert ens retornara trobat = a true.
	
	bool trobat = true;
	
	for(unsigned int i =0; i<paraula.size();i++){

		if(paraula[i] !=x [i])  trobat=false;
		
	}

	return trobat;
}

bool minuscula(const char x){
	//Pre: Agafa una lletra
	//Post: Et retorna si la lletra es minuscula o no.
	bool trobat=false;
	vector<char> lletres(27);
	lletres[0]='a';
	lletres[1]='b';
	lletres[2]='c';
	lletres[3]='d';
	lletres[4]='e';
	lletres[5]='f';
	lletres[6]='g';
	lletres[7]='h';
	lletres[8]='i';
	lletres[9]='j';
	lletres[10]='k';
	lletres[11]='l';
	lletres[12]='m';
	lletres[13]='n';
	lletres[14]='o';
	lletres[15]='p';
	lletres[16]='q';	
	lletres[17]='r';
	lletres[18]='s';
	lletres[19]='t';
	lletres[20]='u';
	lletres[21]='v';
	lletres[22]='w';
	lletres[23]='x';
	lletres[24]='y';
	lletres[25]='z';
	for(unsigned int i=0; i<26; i++){
		if(x==lletres[i]) trobat=true;
	}
	return trobat;
}

bool repe(const char x, const vector <char> lletresuti){
	//Pre: Agafa una lletra i un vector
	//Post: Et retorna true si la lletra ja esta escrita dins del vector.
	bool trobat=false;
	for(unsigned int i=0; i<lletresuti.size()-1; i++){
		if(lletresuti[i]==x) trobat=true;
	}
	return trobat;
}

int main(){

	bool tornar_a_comencar = false;
	char resposta; 
	int partidas_guanyades = 0; 
	int partidas_perdudes = 0;


	while(not tornar_a_comencar) { 
	//agafem una paraula i creem un vector amb la mateixa mida

		string x = obtindre_paraula_aleatoria();
		vector <char> paraula(x.size(),'_');
		//n es el contador del nombre de fallos i iguals el contador que ens dira si la paraula ja esta complerta o no
		int n=0;
		//La matriu vuida on anira el penjat

		matriu mort;

		for(int i = 0; i < 7; i++){
			for(int j = 0; j < 10; j++){

				mort[i][j] = ' ';
			}
		}
		cout<<"La paraula te : "<<x.size()<<" lletres"<<endl;
		for(unsigned int h=0; h<x.size(); h++){
			cout<<paraula[h]<<" ";
		}
		cout<<endl;
		vector <char> lletrauti(0);
		bool semblants = false;
		while(n<10 and not semblants){	
		//demanem una lletra i creidem a la funcio que ens dira si esta dins de el vector

			char y;
			cout<<"Dona'm una lletra minuscula : "; cin>>y; cout<<endl;
			bool k=minuscula(y);
			if(k==true){
				lletrauti.push_back(y);				
				bool l=repe(y,lletrauti);
				if(l==true) cout<<"Ja has intoduit aquesta lletraminuscula, introdueixe-ne una altre"<<endl;
				else if (l!=true){

					bool z=compara(x, paraula, y);
					if(z==true) {
						cout<<"Hi ha una lletra minuscula : "<<y<<"\n"<<endl;
						for(unsigned int i=0; i<paraula.size();i++){
							cout<<paraula[i]<<" ";	
				 
						}
						cout<<"\n"<<endl;


					} else {
						n++;
						penjat(n,mort); 
						mostrar_matriz(mort);		
						cout<<"No has encertat. Fallides : "<<n<<endl;	
					}	

					semblants = iguals(x, paraula);
					
					if(semblants) { //Si el vector es igual a la paraula, has guanyat
						cout<<"Felicitats, has guanyat!!"<<"\n"<<endl;
						cout<<"Vols jugar? (S/N)";cin>>resposta; cout<<"\n";
						++partidas_guanyades;

						if(resposta == 'N' or resposta == 'n'){
						
						tornar_a_comencar=true;

						}else if (resposta!='N' and resposta != 'S') {
							cout<<"Introduex S o N: "; cin>>resposta;
						}
						
					} 

					if(n==10) { //Si el contador de errors es igual a 10, has perdut,
 						

						cout<<"OHHH!  Has perdut!!"<<"\n"<<endl;

						partidas_perdudes++;
						cout<<"Vols jugar? (S/N)"; cin>>resposta; cout<<"\n";

					
						if(resposta == 'N' or resposta == 'n'){
			
							tornar_a_comencar=true;

			
			
						}else if (resposta!='N' and resposta != 'S') {
							
							
								cout<<"Introduex S o N: ";
 								cin>>resposta;	
					
							
					}
				}	
}
			
			}else if(k != true) { //En cas de que la lletra que s'introdueixi no sigui minuscula.nar_a_comencar=tr
				cout<<"No es una lletre minuscula, sisplau torna a introduir una lletra que sigui 					minuscula"<<endl;
			}
			
			if (resposta=='N'){
				tornar_a_comencar=true;
				cout<<endl;
				partides(partidas_guanyades,partidas_perdudes);
				cout<<endl;
				cout<<"ADEU, m'ha agradat molt jugar amb tu!!"<<endl;
		
			}
		
		}
	
	}
	

}



