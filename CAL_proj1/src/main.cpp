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
#include <math.h>
#include <ctype.h>
#include "Graph.h"
#include "Geography.h"
#include "Node.h"
#include "CPoint.h"
#include "graphviewer.h"
#include "Road.h"
#include "Interface.h"
#include "User.h"
#include "FileHandlers.h"

using namespace std;

Graph<Node> grafo;
vector<Road*> estradas;
vector<CPoint> pontos;
vector<User*> utils;
User* current_user;
size_t origin_ind;

int main(){

	cout << "Loading...";
	cout << endl;
	loadNodes(grafo);
	loadRoads(estradas);
	loadCPoints(pontos,grafo);
	loadEdges(grafo,estradas);

	cout << "\n	   BIKE SHARING	   \n";
	printf("ERRO 1");
	printf("Aanabela  %f\n", grafo.conetivity());

	/* Shows full graph */
	showGraph(&grafo,&pontos);

	clientInit(origin_ind, utils, pontos, current_user);

	menu(origin_ind,pontos,grafo);

	saveCPoints(pontos);
	saveUsers(utils);

	//TODO: Analise do tempo de execucao
	//TODO: Avaliar a conectividade
	//TODO: Imprimir caminho ate aluguer ou recolha (Consola + GUI)
}
