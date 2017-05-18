#include <fstream>
#include <vector>
#include <algorithm>

#include "CPoint.h"

/**
 * @brief returns a vector of points which name contains the exact string wanted
 * @param pontos points to compare
 * @param toSearch string to be searched
 */
std::vector<CPoint> indStringMatching(std::vector<CPoint> &pontos, std::string toSearch);

/**
 * @brief returns a vector of all points with it's distance to the string wanted
 * @param pontos points to compare
 * @param toSearch string to be searched
 */
std::vector<CPoint> ordApproximateStringMatching(std::vector<CPoint> &pontos, std::string toSearch);
