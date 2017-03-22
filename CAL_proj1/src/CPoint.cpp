/*
 * CPoint.cpp
 *
 *  Created on: 22/03/2017
 *      Author: bmsp2
 */

#include "CPoint.h"

int CPoint::getPlaces() const {
	return places;
}

int CPoint::getBikes() const {
	return bikes;
}

Node* CPoint::getColNode() const {
	return col_node;
}
