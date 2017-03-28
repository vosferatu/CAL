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
#include "graphviewer.h"
#include "Road.h"
#include <math.h>
#include "Interface.h"
#include <ctype.h>

using namespace std;

Graph<Node> grafo;
vector<Road*> estradas;
vector<CPoint> pontos;

size_t origin_ind;

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
	int ans=-1;
	int new_ind=origin_ind;
	CPoint* ponto = NULL;
	for (size_t i = 0; i < pontos.size(); i++) {
		if (pontos.at(i).getBikes() > 0
				&& grafo.getVertex(pontos.at(i).getColNode())->getDist()
				< min && i!=origin_ind) {
			min = grafo.getVertex(pontos.at(i).getColNode())->getDist();
			ponto = &(pontos.at(i));
			new_ind=i;
		}
	}

	cout << "\nThe nearest point ("<< grafo.getVertex(ponto->getColNode())->getDist() <<" m) with bikes for rental is " << ponto->getName() << endl;
	cout << "\nDo you want to rent a bike on there? (Y/N)";

	while (ans < 1 || ans > 2) {
		cout << "\n1 - Yes\n2 - No\n";
		cin >> ans;
	}

	switch(ans)
	{
	case 1:
		ponto->rentBike();
		origin_ind=new_ind;
		break;
	case 2:
		cout << "\nSo where do you want to do it?\n";
		for (unsigned int i = 0, a=0; i < pontos.size(); i++)
		{
			//TODO:Lidar com pontos inacessíveis ou devoluções no mesmo ponto
			cout << a+1 << " - " << pontos.at(i).getName() << " ("<< grafo.getVertex(pontos.at(i).getColNode())->getDist() <<" m)"<< endl;
			a++;
		}
		cin >> ans;
		pontos.at(ans-1).rentBike();
		origin_ind=ans;
		break;
	default:
		break;
	}

	return;
}

void searchForReturn() {
	int min = INT_MAX;
	int new_ind=origin_ind;
	int ans=-1;
	CPoint* ponto = NULL;
	for (unsigned int i = 0; i < pontos.size(); i++) {
		if (pontos.at(i).getPlaces() > 0
				&& grafo.getVertex(pontos.at(i).getColNode())->getDist()
				< min && i!=origin_ind) {
			min = grafo.getVertex(pontos.at(i).getColNode())->getDist();
			ponto = &(pontos.at(i));
			new_ind=i;
		}
	}
	cout << "\nThe nearest point with places for return is ("<< grafo.getVertex(ponto->getColNode())->getDist() <<" m | " << 8-0.11*ponto->getAltitude() << " euros) " << ponto->getName()<< endl;
	cout << "Do you want to return a bike on there? (Y/N)";

	while (ans < 1 || ans > 2) {
		cout << "\n1 - Yes\n2 - No\n";
		cin >> ans;
	}

	switch(ans)
	{
	case 1:
		if(ponto->getPlaces() > 0){
			ponto->returnBike();
			origin_ind=new_ind;
		}
		else{
			//TODO maybe run function again? probably after searching, before asking user
		}
		break;
	case 2:
		cout << "\nSo where do you want to do it?\n";
		for (unsigned int i = 0, a=0; i < pontos.size(); i++)
		{
			//TODO:Lidar com pontos inacessíveis ou devoluções no mesmo ponto
			cout << a+1 << " - " << pontos.at(i).getName() << " ("<< grafo.getVertex(pontos.at(i).getColNode())->getDist() <<" m | " << 8-0.11*pontos.at(i).getAltitude() << " euros)" << endl;
			a++;
		}
		cin >> ans;
		pontos.at(ans-1).returnBike();
		origin_ind=ans;
		break;
	default:
		break;
	}

	return;

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
			Road *road = new Road(id, name, two_way == "True");
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
					int distance=src_coords.getDistanceFromLatLon(dest_coords);

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
	ifstream ifs("espinho_nodes.txt");
	if (ifs.is_open()) {
		string line;
		while (!ifs.eof()) {
			getline(ifs, line, ';');
			long long id = atoll(line.c_str());
			getline(ifs, line, ';');
			float lat = atof(line.c_str());
			getline(ifs, line, ';');
			float lon = atof(line.c_str());

			if(lat>GeoCoordinate::latMax)
				GeoCoordinate::latMax=lat;

			if(lat<GeoCoordinate::latMin)
				GeoCoordinate::latMin=lat;

			if(lon>GeoCoordinate::lonMax)
				GeoCoordinate::lonMax=lon;

			if(lon<GeoCoordinate::lonMin)
				GeoCoordinate::lonMin=lon;

			GeoCoordinate degrees(lat, lon);
			getline(ifs, line, ';');
			lat = atof(line.c_str());
			getline(ifs, line, '\n');
			lon = atof(line.c_str());
			GeoCoordinate radians(lat, lon);
			Node node(id, degrees, radians);
			grafo.addVertex(node);
		}
	}
	ifs.close();

}

void saveCPoints(){
	ofstream ifs("espinho_cpoints.txt", ios::trunc);

	if(ifs.is_open()){
		for(size_t i = 0; i < pontos.size(); i++) {
			ifs << pontos[i];
			if(i < (pontos.size()-1))
				ifs << '\n';

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
		cout << "\nWhich collection point are you in?";
		for (size_t i = 0; i < pontos.size(); i++) {
			cout << endl;
			cout << i+1 << " - " << pontos[i].getName();
		}
		cout << endl;
		cin >> ans;
	}
	return ans-1;

}

void menu(){
	size_t ans=-1;
	cout << "\nWhat do you want to do?";
	while (ans < 1 || ans > 2) {
		cout << "\n1 - Rent\n2 - Return\n";
		cin >> ans;
	}

	while(1)
	{
		char exit;

		grafo.dijkstraShortestPath(pontos.at(origin_ind).getColNode());

		if (ans == 1)
		{
			searchForRent();
			ans=2;
		}
		else
		{
			searchForReturn();
			ans=1;
		}

		cout<<"\nDo you want to exit? (Y/N)\n";

		cin >> exit;

		switch(exit)
		{
		case 'Y':
			return;
		case 'y':
			return;
		default:
			continue;
		}
	}
}

int main() {

	cout << "Loading...";
	cout << endl;
	loadNodes();
	loadRoads();
	loadCPoints();
	loadEdges();

	showGraph(&grafo,&pontos);

	cout << "\n	   BIKE SHARING	   \n";
	//clientInit();
	origin_ind = originCPoint();
		menu();

	//TODO: Mostrar ponto de partilha mais
	//prďż˝ximo de onde se encontra, com lugar
	//disponďż˝vel para a devoluďż˝ďż˝o da bicicleta
	//TODO: Mostrar ponto de partilha mais
	//barato de onde se encontra, com lugar
	//disponďż˝vel para a devoluďż˝ďż˝o da bicicleta
}

