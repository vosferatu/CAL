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

int main(){

	/**
	* @brief Graph representing the map
	*/
	Graph<Node> grafo { };

	/**
	* @brief Roads vector
	*/
	vector<Road*> estradas;

	/**
	* @brief CPoints vector
	*/
	vector<CPoint> pontos;

	/**
	* @brief Users vector
	*/
	vector<User*> utils;

	/**
	* @brief Current user
	*/
	User* current_user { };

	/**
	* @brief Current user
	*/
	size_t origin_ind { };

	cout << "Loading...";
	cout << endl;
	loadNodes(grafo);
	loadRoads(estradas);
	loadCPoints(pontos,grafo);
	loadEdges(grafo,estradas);
	loadUsers(utils);

	cout << "\n	   BIKE SHARING	   \n";
	printf("Percentage %f\n", grafo.conetivity());

	/** Shows full graph */
	//showGraph(&grafo,&pontos);

	clientInit(origin_ind, utils, pontos, current_user);

	menu(origin_ind,pontos,grafo);

	saveCPoints(pontos);
	saveUsers(utils);
}
