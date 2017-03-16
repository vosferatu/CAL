/*
 * Interface.cpp
 *
 *  Created on: 15/03/2017
 *      Author: bmsp2
 */

#include <iostream>
#include <fstream>

#include "User.h"
using namespace std;

Graph<Node*> grafo;

void readGrafo(){

}

void clientInit(){
	int ans=0;
	string name;
	string password;
	fstream file;
	bool exists=false;
	bool valid=false;

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
			string read_name, read_password, line;
			getline(file,read_name,';');
			getline(file,read_password,';');
			getline(file,line,'\n');
			if(read_name==name)
			{
				exists=true;
				while(!valid){
					cout << "PASSWORD: ";
					cin >> password;
					if(read_password==password)
						valid=true;
				}
			}
			if(exists==true)
			{
				file.close();
				break;
			}
		}
	}

	if(!exists || ans==2)
	{
		int pay_met, pay_no;
		cout << "\nREGISTRATION";
		cout << "\nUsername: ";
		cin.ignore();
		getline(cin,name);
		cout << "Password: ";
		cin >> password;
		cout << "Payment method?\n1 - Paypal\n2 - Credit Card\n";
		cin >> pay_met;
		cout << "Payment method number: ";
		cin >> pay_no;
		file.open("Users.txt");
		file.seekg(0, file.end);
		file << name << ";" << password << ";" << pay_met << ";" << pay_no << '\n';
		file.close();
	}
}

void interface(){

	cout << "	BIKE SHARING	\n" << endl;

	clientInit();
}

int main(){

	readGrafo();
	interface();
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


