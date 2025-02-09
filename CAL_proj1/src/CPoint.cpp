/*
 * CPoint.cpp
 *
 *  Created on: 22/03/2017
 *      Author: bmsp2
 */

#include "CPoint.h"

CPoint::CPoint(){}

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

int CPoint::getDistance() const {
	return distance;
}

void CPoint::setDistance(int nDistance) {
	distance=nDistance;
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

void CPoint::rentBike(){
	if(bikes != 0)
		bikes--;
	places++;
}

void CPoint::returnBike(){
	bikes++;
	places--;
}

std::ofstream& operator<<(std::ofstream& out, const CPoint& point){
	out << point.getName() << ";" << point.getColNode()->getId() << ";";

	out << point.getBikes() << ";" << point.getPlaces() << ";";

	out << point.getAltitude();

	return out;
}
