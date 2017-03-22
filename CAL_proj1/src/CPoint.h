/*
 * CPoint.h
 *
 *  Created on: 15/03/2017
 *      Author: bmsp2
 */

#ifndef CPOINT_H_
#define CPOINT_H_

#include "Node.h"
#include <string>

class CPoint{
	/*
	 * @brief Node's available bikes
	 */
	int bikes;
	/*
	 * @brief Node's available parking places
	 */
	int places;
	/*
	 * @brief Pointer to the correspondent node
	 */
	Node* col_node;
public:
	/*
	 * @brief Gets the number of available bikes
	 */
	int getBikes() const;

	/*
	 * @brief Gets the number of available parking places
	 */
	int getPlaces() const;

	/*
	 * @brief Gets the Collection Node
	 */
	Node* getColNode() const;
};

#endif
