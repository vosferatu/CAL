/*
 * main.cpp
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
#include "CPoint.h"
#include "Road.h"
#include <math.h>

using namespace std;

Graph<Node> grafo;
vector<Road*> estradas;
vector<CPoint> pontos;

int origin_ind;

/*
 *@brief Calculates bike return's price, in cents
 *@param destination Collection point where the bike will be returned;
 */
int priceCentsCalculator(CPoint destination){
	int price=800-(destination.getAltitude()*1.1);

	return price;
}

void searchForRent() {
	int min = INT_MAX;
	CPoint* ponto = NULL;
	for (unsigned int i = 0; i < pontos.size(); i++) {
		if (pontos.at(i).getBikes() > 0
				&& grafo.getVertex(pontos.at(i).getColNode())->getDist()
				< min) {
			min = grafo.getVertex(pontos.at(i).getColNode())->getDist();
			ponto = &(pontos.at(i));
		}
	}
	cout << "O ponto mais proximo com bicicletas e a " << ponto->getName()
					<< endl;
}

void searchForReturn() {
	int min = INT_MAX;
	CPoint* ponto = NULL;
	for (unsigned int i = 0; i < pontos.size(); i++) {
		if (pontos.at(i).getPlaces() > 0
				&& grafo.getVertex(pontos.at(i).getColNode())->getDist()
				< min) {
			min = grafo.getVertex(pontos.at(i).getColNode())->getDist();
			ponto = &(pontos.at(i));
		}
	}
	cout << "O ponto mais proximo com vagas e a " << ponto->getName()
					<< endl;

}

/*
 * @brief Returns the distance between two places
 * @param place1 First place to compare
 * @param place2 Second place to compare
 */
int getDistanceFromLatLonInKm(GeoCoordinate place1, GeoCoordinate place2) {
	int R = 6371; // Radius of the earth in km
	float a = sin((place2.getLat() - place1.getLat()) / 2)
											* sin((place2.getLat() - place1.getLat()) / 2)
											+ cos(place1.getLat()) * cos(place2.getLat())
											* sin((place2.getLon() - place1.getLon()) / 2)
											* sin((place2.getLon() - place1.getLon()) / 2);
	float c = 2 * atan2(sqrt(a), sqrt(1 - a));
	float d = R * c; // Distance in km
	return d;
}

Road* searchRoad(int id) {
	for (size_t i = 0; i < estradas.size(); i++) {
		if (estradas[i]->getId() == id)
			return estradas[i];
	}

	return NULL;
}

void loadCPoints() {
	ifstream ifs("espinho_cpoints.txt");
	if (ifs.is_open()) {
		string line;
		while (!ifs.eof()) {
			getline(ifs, line, ';');
			string name = line;
			getline(ifs, line, ';');
			int id_node = atoi(line.c_str());
			getline(ifs, line, ';');
			int no_bikes = atoi(line.c_str());
			getline(ifs, line, ';');
			int no_vagas = atoi(line.c_str());
			getline(ifs, line, '\n');
			int altitude = atoi(line.c_str());
			for (unsigned int i = 0; i < grafo.getVertexSet().size(); i++) {
				if (grafo.getVertexSet()[i]->getInfo()->getId() == id_node) {
					CPoint aux(name, no_bikes, no_vagas, grafo.getVertexSet()[i]->getInfo(),altitude);
					pontos.push_back(aux);
				}
			}
		}
	}
	ifs.close();
}

void loadRoads() {
	ifstream ifs("espinho_roads.txt");
	if (ifs.is_open()) {
		string line;
		while (!ifs.eof()) {
			getline(ifs, line, ';');
			int id = atoi(line.c_str());
			getline(ifs, line, ';');
			string name = line;
			getline(ifs, line, '\n');
			string two_way = line;
			Road *road = new Road(id, name, two_way == "true");
			estradas.push_back(road);
		}
	}
	ifs.close();
}

void loadEdges() {
	ifstream ifs("espinho_subroads.txt");
	if (ifs.is_open()) {
		string line;
		while (!ifs.eof()) {
			getline(ifs, line, ';');
			int id = atoi(line.c_str());

			Road *road = searchRoad(id);
			if (road == NULL) {
				getline(ifs, line, '\n');
				continue;
			} else {
				getline(ifs, line, ';');
				int sour = atoi(line.c_str());
				getline(ifs, line, '\n');
				int dest = atoi(line.c_str());
				Vertex<Node>* source=NULL, *destination=NULL;
				for (size_t i = 0; i < grafo.getVertexSet().size(); i++) {
					if (grafo.getVertexSet()[i]->getInfo()->getId() == sour)
						source = grafo.getVertexSet()[i];
					if (grafo.getVertexSet()[i]->getInfo()->getId() == dest)
						destination = grafo.getVertexSet()[i];
					if (source != NULL && destination != NULL)
						break;
				}

				if (source != NULL && destination != NULL) {
					GeoCoordinate src_coords=source->getInfo()->getRadCoords();
					GeoCoordinate dest_coords=destination->getInfo()->getRadCoords();
					int distance=getDistanceFromLatLonInKm(src_coords, dest_coords);

					if (road->isTwoWay()) {
						source->addEdge(destination, distance);
						destination->addEdge(source, distance);
					} else {
						source->addEdge(destination, distance);
					}
				}

			}
		}
	}

}

void loadNodes() {
	srand(time(NULL));
	int index = rand() % 10 + 1;
	ifstream ifs("espinho_nodes.txt");
	if (ifs.is_open()) {
		string line;
		while (!ifs.eof()) {
			getline(ifs, line, ';');
			int id = atoi(line.c_str());
			getline(ifs, line, ';');
			long lat = atol(line.c_str());
			getline(ifs, line, ';');
			long lon = atol(line.c_str());
			GeoCoordinate degrees(lat, lon);
			getline(ifs, line, ';');
			lat = atol(line.c_str());
			getline(ifs, line, '\n');
			lon = atol(line.c_str());
			GeoCoordinate radians(lat, lon);
			Node node(id, degrees, radians);
			grafo.addVertex(node);
			index--;
		}
	}
	ifs.close();
}

void clientInit() {
	int ans = 0;
	string name;
	string password;
	fstream file;
	bool exists = false;
	bool valid = false;

	while (ans < 1 || ans > 2) {
		cout << "\n1 - Login\n2 - Register\n";
		cin >> ans;
	}

	if (ans == 1) {
		cout << "\nLOGIN\n";
		cout << "Username: ";
		cin >> name;
		file.open("Users.txt");
		while (!file.eof()) {
			string read_name, read_password, line;
			getline(file, read_name, ';');
			getline(file, read_password, ';');
			getline(file, line, '\n');
			if (read_name == name) {
				exists = true;
				while (!valid) {
					cout << "PASSWORD: ";
					cin >> password;
					if (read_password == password)
						valid = true;
				}
			}
			if (exists == true) {
				file.close();
				break;
			}
		}
	}

	if (!exists || ans == 2) {
		int pay_met, pay_no;
		cout << "\nREGISTRATION";
		cout << "\nUsername: ";
		cin.ignore();
		getline(cin, name);
		cout << "Password: ";
		cin >> password;
		cout << "Payment method?\n1 - Paypal\n2 - Credit Card\n";
		cin >> pay_met;
		cout << "Payment method number: ";
		cin >> pay_no;
		file.open("Users.txt");
		file.seekg(0, file.end);
		file << name << ";" << password << ";" << pay_met << ";" << pay_no
				<< '\n';
		file.close();
	}
}

int originCPoint() {
	size_t ans=-1;

	while(ans < 1 || ans > pontos.size()){
		cout << "Which collection point are you in?\n";
		for (size_t i = 0; i < pontos.size(); i++) {
			cout << endl;
			cout << i+1 << " - " << pontos[i].getName();
		}
		cout << endl;
		cin >> ans;
	}
	return ans;

}

void menu(){
	size_t ans=-1;
	cout << "\nWhat do you want to do?\n";
	while (ans < 1 || ans > 2) {
		cout << "\n1 - Rent\n2 - Return\n";
		cin >> ans;
	}
	grafo.dijkstraShortestPath(pontos.at(ans).getColNode());
	if (ans == 1)
		searchForRent();
	else
		searchForReturn();
}

int main() {

	cout << "Loading...";
	cout << endl;
	loadNodes();
	loadRoads();
	loadCPoints();
	loadEdges();

	cout << "\n	   BIKE SHARING	   \n";
	clientInit();
	do{
		origin_ind = originCPoint();
		menu();
	}while(1);
	//TODO: Mostrar ponto de partilha mais
	//pr�ximo de onde se encontra, com lugar
	//dispon�vel para a devolu��o da bicicleta
	//TODO: Mostrar ponto de partilha mais
	//barato de onde se encontra, com lugar
	//dispon�vel para a devolu��o da bicicleta

	//XXX: Qual a f�rmula de c�lculo do custo?
}

