/*
 * Interface.cpp
 *
 *  Created on: 15/03/2017
 *      Author: bmsp2
 */

#include <iostream>
#include <fstream>
#include "Client.h"
using namespace std;

void clientInit(){
	int ans=0;
	string name;
	fstream file;
	bool exists=false;

	while(ans<1 || ans>2){
		cout << "\n1 - Login\n2 - Register\n";
		cin >> ans;
	}

	if(ans==1){
		cout << "\nLOGIN\n";
		cout << "Username: ";
		cin >> name;
		file.open("Users.txt");
		while(!file.eof() || !exists){
			string line;
			getline(file,line,';');
			if(line==name)
				{
				/*int pay_met, pay_no;
				file >> pay_met;
				getline(file,line,';');
				file >> pay_no;*/
				exists=true;

				//user=Client(name,pay_met,pay_no);
				}
		}
	}
	if(!exists || ans==2)
	{
		int pay_met, pay_no;
		cout << "\nREGISTRATION";
		cout << "Username: ";
		cin >> name;
		cout << "Payment method?\n1 - Paypal\n2 - Credit Card\n";
		cin >> pay_met;
		cout << "Payment method number: \n";
		cin >> pay_no;
		file.open("Users.txt");
		file.seekg(0, file.end);
		file << name << ";" << pay_met << ";" << pay_no;
	}
}

void interface(){

	cout << "	BIKE SHARING	\n" << endl;

	clientInit();

	cout << "Em que local se encontra?\n";
}

int main(){
	//TODO: Listagem de locais possíveis?
	//TODO: Carregar grafo
	//TODO: Mostrar ponto de partilha mais
	//próximo de onde se encontra, com lugar
	//disponível para a devolução da bicicleta
	//TODO: Mostrar ponto de partilha mais
	//próximo de onde se encontra, com lugar
	//disponível para a devolução da bicicleta
	//TODO: Mostrar ponto de partilha mais
	//barato de onde se encontra, com lugar
	//disponível para a devolução da bicicleta
}


