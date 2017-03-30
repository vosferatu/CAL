#include <vector>
#include "Graph.h"
#include "CPoint.h"
#include "User.h"
#include "graphviewer.h"

/*
 * @brief Shows the complete graph
 * @param grafo Graph to be shown
 * @param pontos CPoints to be shown
 */
void showGraph(Graph<Node>* grafo, vector<CPoint>* pontos);

/*
 * @brief Updates the origin CPoint
 * @param pontos Existing CPoints
 * @param origin_ind Origin Index
 */
int originCPoint(vector<CPoint> &pontos, size_t &origin_ind);

/*
 * @brief Shows the menu
 */
void menu(size_t &origin_ind, vector<CPoint> &pontos, Graph<Node> &grafo);

/*
 * @brief Search for a place to rent a bike
 * @param origin_ind Index of the origin CPoint
 * @param pontos CPoints vector
 * @param grafo Graph for searching
 */
void searchForRent(size_t &origin_ind, vector<CPoint> &pontos, Graph<Node> &grafo);

void searchForReturn(size_t &origin_ind, vector<CPoint> &pontos, Graph<Node> &grafo);

void clientInit(size_t &origin_ind, vector<User*> &utils, vector<CPoint> &pontos, User* current_user);
