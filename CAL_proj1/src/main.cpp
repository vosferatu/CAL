/*
 * Interface.cpp
 *
 *  Created on: 15/03/2017
 *      Author: bmsp2
 */

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "Graph.h"
#include "Geography.h"
#include "Node.h"
#include "User.h"
#include "Road.h"
using namespace std;

Graph<Node> grafo;
vector<Road*> estradas;

Road* searchRoad(int id){
	for(size_t i=0; i<estradas.size(); i++){
		if(estradas[i]->getId()==id)
			return estradas[i];
	}

	return NULL;
}

void loadRoads(){
	ifstream ifs("porto_roads.txt");
	if(ifs.is_open()){
		string line;
		while(!ifs.eof()){
			getline(ifs,line,';');
			int id=atoi(line.c_str());
			getline(ifs,line,';');
			string name=line;
			getline(ifs,line,'\n');
			string two_way=line;
			Road *road=new Road(id,name,two_way=="true");
			estradas.push_back(road);
		}
	}
	ifs.close();
}

void loadEdges(){
	ifstream ifs("porto_subroads.txt");
	if(ifs.is_open()){
		string line;
		while(!ifs.eof()){
			getline(ifs,line,';');
			int id=atoi(line.c_str());

			Road *road=searchRoad(id);

			if(road==NULL)
				continue;
			else
			{
				getline(ifs,line,';');
				int sour=atoi(line.c_str());
				getline(ifs,line,'\n');
				int dest=atoi(line.c_str());

				Vertex<Node>* source, *destination;

				for(size_t i=0; i<grafo.getVertexSet().size(); i++){
					if(grafo.getVertexSet()[i]->getInfo().getId()==sour)
						source=grafo.getVertexSet()[i];
					if(grafo.getVertexSet()[i]->getInfo().getId()==dest)
						destination=grafo.getVertexSet()[i];
					if(source!=NULL && destination!=NULL)
					break;
				}
				if(source!=NULL && destination!=NULL)
				{
						if(road->isTwoWay())
						{
							source->addEdge(destination, 1/* distancia */);
							destination->addEdge(source, 1/* distancia */);
						}
						else
							source->addEdge(destination, 1/* distancia */);
				}

			}
		}
	}

}

void loadNodes(){
	srand (time(NULL));
	int index = rand() % 10 + 1;
	ifstream ifs("porto_nodes.txt");
	if(ifs.is_open()){
		string line;
		while(!ifs.eof()){
			getline(ifs,line,';');
			int id=atoi(line.c_str());
			getline(ifs,line,';');
			long lat=atol(line.c_str());
			getline(ifs,line,';');
			long lon=atol(line.c_str());
			GeoCoordinate degrees(lat,lon);
			getline(ifs,line,';');
			lat=atol(line.c_str());
			getline(ifs,line,'\n');
			lon=atol(line.c_str());
			GeoCoordinate radians(lat,lon);
			if(index==0)
				{
				Node node(id,degrees,radians, true);
				grafo.addVertex(node);
				index = rand() % 10 + 1;
				}
			else
			{
				Node node(id,degrees,radians, false);
				grafo.addVertex(node);
				index--;
			}
		}
	}
	ifs.close();
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

	grafo.getNumVertex();

	clientInit();

}

int main(){

	cout << "Loading...\n";
	loadNodes();
	loadRoads();
	loadEdges();
	interface();
	//TODO: Listagem de locais poss�veis?
	//TODO: Carregar grafo
	//TODO: Mostrar ponto de partilha mais
	//pr�ximo de onde se encontra, com lugar
	//dispon�vel para a devolu��o da bicicleta
	//TODO: Mostrar ponto de partilha mais
	//pr�ximo de onde se encontra, com lugar
	//dispon�vel para a devolu��o da bicicleta
	//TODO: Mostrar ponto de partilha mais
	//barato de onde se encontra, com lugar
	//dispon�vel para a devolu��o da bicicleta

	//XXX: Todos os n�s s�o pontos de recolha?
	//XXX: Intera��o utilizador/sistema fica-se
	//pelo registo e verifica��o do mesmo?
	//XXX: N� inicial � dado numa macro ou
	//perguntado ao utilizador?
	//XXX: Altitudes variam em que amplitude?
	//XXX: Qual a f�rmula de c�lculo do custo?
	//XXX: Como calcular a dist�ncia entre n�s a
	//partir da latitude e longitude?
	// http://stackoverflow.com/questions/27928/calculate-distance-between-two-latitude-longitude-points-haversine-formula
}


