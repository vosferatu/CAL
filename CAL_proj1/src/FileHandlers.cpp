/*
 * FileHandlers.cpp
 *
 *  Created on: 30/03/2017
 *      Author: bmsp2
 */

#include "FileHandlers.h"

using namespace std;

void saveCPoints(vector<CPoint>& pontos){
	ofstream ifs(CPOINTS_TXT, ios::trunc);

	if(ifs.is_open()){
		for(size_t i = 0; i < pontos.size(); i++) {
			ifs << pontos[i];
			if(i < (pontos.size()-1))
				ifs << '\n';

		}
	}
	ifs.close();
}

void saveUsers(std::vector<User*> &utils){
	ofstream ifs(USERS_TXT, ios::trunc);

	if(ifs.is_open()){
		for(size_t i = 0; i < utils.size(); i++) {
			ifs << (*utils[i]);

			if(i < (utils.size()-1))
				ifs << '\n';
		}
	}
	ifs.close();
}

void loadUsers(std::vector<User*> &utils) {
	ifstream ifs(USERS_TXT);
	if (ifs.is_open()) {
		string line;
		while (!ifs.eof()) {
			getline(ifs, line, ';');
			string name = line;
			getline(ifs, line, ';');
			string password = line;
			getline(ifs, line, ';');
			int pay_method = atoi(line.c_str());
			getline(ifs, line, ';');
			int pay_no = atoi(line.c_str());
			getline(ifs, line);
			int last = atoi(line.c_str());
			User * user = new User(name, password, pay_method, pay_no,last);
			utils.push_back(user);
		}
	}
	ifs.close();
}


void loadCPoints(vector<CPoint> &pontos, Graph<Node> &grafo) {
	ifstream ifs(CPOINTS_TXT);
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

void loadRoads(vector<Road*> &estradas) {
	ifstream ifs(ROADS_TXT);
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

void loadEdges(Graph<Node> &grafo, vector<Road*> &estradas) {
	ifstream ifs(SUBROADS_TXT);
	if (ifs.is_open()) {
		string line;
		while (!ifs.eof()) {
			getline(ifs, line, ';');
			int id = atoi(line.c_str());

			Road *road = searchRoad(id,estradas);
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

void loadNodes(Graph<Node> &grafo) {
	ifstream ifs(NODES_TXT);
	if (ifs.is_open()) {
		string line;
		while (!ifs.eof()) {
			User a;
			//cout << a;
		//	cout << a;
			getline(ifs, line, ';');
			long long id = atoll(line.c_str());
			getline(ifs, line, ';');
			float lat = atof(line.c_str());
			getline(ifs, line, ';');
			float lon = atof(line.c_str());
			GeoCoordinate degrees(lat, lon);
			getline(ifs, line, ';');
			lat = atof(line.c_str());
			getline(ifs, line, '\n');
			lon = atof(line.c_str());

			if(lat>GeoCoordinate::latMax)
				GeoCoordinate::latMax=lat;

			if(lat<GeoCoordinate::latMin)
				GeoCoordinate::latMin=lat;

			if(lon>GeoCoordinate::lonMax)
				GeoCoordinate::lonMax=lon;

			if(lon<GeoCoordinate::lonMin)
				GeoCoordinate::lonMin=lon;

			GeoCoordinate radians(lat, lon);
			Node node(id, degrees, radians);
			grafo.addVertex(node);
		}
	}
	ifs.close();

}
