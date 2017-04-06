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
#define ROADS_TXT "./maps/espinho_roads7.txt"
#define SUBROADS_TXT "./maps/espinho_subroads7.txt"
#define NODES_TXT "./maps/espinho_nodes7.txt"

/*
 * @brief Stores the CPoints in the text file
 */
void saveCPoints(std::vector<CPoint>& pontos);

/*
 * @brief Stores the Users in the text file
 */
void saveUsers(std::vector<User*> &utils);

/*
 * @brief Loads the Users from the text file
 */
void loadUsers(std::vector<User*> &utils);

/*
 * @brief Loads the Roads from the text file
 */
void loadRoads(std::vector<Road*> &estradas);

/*
 * @brief Loads the CPoints from the text file
 */
void loadCPoints(std::vector<CPoint> &pontos, Graph<Node> &grafo);

/*
 * @brief Loads the Nodes from the text file
 */
void loadNodes(Graph<Node> &grafo);

/*
 * @brief Loads the Edges from the text file
 */
void loadEdges(Graph<Node> &grafo, vector<Road*> &estradas);

#endif /* FILEHANDLERS_H_ */
