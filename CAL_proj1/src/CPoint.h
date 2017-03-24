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
	 * @brief CPoint's name
	 */
	std::string name;
	/*
	 * @brief CPoint's available bikes
	 */
	int bikes;
	/*
	 * @brief CPoint's available parking places
	 */
	int places;
	/*
	 * @brief Pointer to the correspondent node
	 */
	Node* col_node;
public:
	/*
	* @brief CPoint constructor;
	*/
	CPoint(std::string name_cpoint, int bikes_cpoint, int places_cpoint, Node* col_node_cpoint);
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

	/*
	 * @brief Gets CPoint's name
	 */
	const std::string& getName() const;
};

#endif
