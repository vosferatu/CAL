#include <vector>
#include "Graph.h"
#include "CPoint.h"
#include "User.h"
#include "graphviewer.h"

User* current_user = NULL;

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

/*
 * @brief Search for a place to return a bike
 * @param origin_ind Index of the origin CPoint
 * @param pontos CPoints vector
 * @param grafo Graph for searching
 */
void searchForReturn(size_t &origin_ind, vector<CPoint> &pontos, Graph<Node> &grafo);

<<<<<<< HEAD
/*
 * @brief get user info
 * @param origin_ind Index of the origin CPoint
 * @param pontos CPoints vector
 * @param grafo Graph for searching
 */
void clientInit(size_t &origin_ind, vector<User*> &utils, vector<CPoint> &pontos);
=======
void clientInit(size_t &origin_ind, vector<User*> &utils, vector<CPoint> &pontos, User* current_user);
>>>>>>> branch 'master' of https://github.com/JMendes25/CAL.git
