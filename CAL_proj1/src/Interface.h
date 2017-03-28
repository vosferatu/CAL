#include <vector>
#include "Graph.h"
#include "CPoint.h"
#include "graphviewer.h"

/**
 * @brief Shows the complete graph
 * @param grafo Graph to be shown
 * @param pontos CPoints to be shown
 */
void showGraph(Graph<Node>* grafo, vector<CPoint>* pontos);

/**
 * @brief Updates the origin CPoint
 * @param pontos Existing CPoints
 * @param origin_ind Origin Index
 */
int originCPoint(vector<CPoint> *pontos, size_t *origin_ind);
