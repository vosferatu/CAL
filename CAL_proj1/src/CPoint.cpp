/*
 * CPoint.cpp
 *
 *  Created on: 22/03/2017
 *      Author: bmsp2
 */

#include "CPoint.h"

CPoint::CPoint(std::string name_cpoint, int bikes_cpoint, int places_cpoint, Node* col_node_cpoint, double altitude_cpoint)
{
	name=name_cpoint;
	bikes=bikes_cpoint;
	places=places_cpoint;
	col_node=col_node_cpoint;
	altitude=altitude_cpoint;
}

int CPoint::getPlaces() const {
	return places;
}

int CPoint::getBikes() const {
	return bikes;
}

Node* CPoint::getColNode() const {
	return col_node;
}

const std::string& CPoint::getName() const {
	return name;
}

double CPoint::getAltitude() const {
	return altitude;
}
