/*
 * FileHandlers.h
 *
 *  Created on: 30/03/2017
 *      Author: bmsp2
 */

#ifndef SRC_FILEHANDLERS_H_
#define SRC_FILEHANDLERS_H_


#include <fstream>
#include <vector>
#include <cstdlib>
#include "CPoint.h"
#include "User.h"
#include "Road.h"
#include "Node.h"
#include "Graph.h"

#define CPOINTS_TXT "espinho_cpoints.txt"
#define USERS_TXT "users.txt"
#define ROADS_TXT "./maps/espinho_roads.txt"
#define SUBROADS_TXT "./maps/espinho_subroads.txt"
#define NODES_TXT "./maps/espinho_nodes.txt"


void saveCPoints(std::vector<CPoint>& pontos);

void saveUsers(std::vector<User*> &utils);

void loadUsers(std::vector<User*> &utils);

void loadRoads(std::vector<Road*> &estradas);

void loadCPoints(std::vector<CPoint> &pontos, Graph<Node> &grafo);

void loadNodes(Graph<Node> &grafo);

void loadEdges(Graph<Node> &grafo, vector<Road*> &estradas);

#endif /* SRC_FILEHANDLERS_H_ */
