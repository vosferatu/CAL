/*
 * Road.h
 *
 *  Created on: 14/03/2017
 *      Author: bmsp2
 */

#ifndef ROAD_H_
#define ROAD_H_

#include <string>
#include <vector>

class Road{
	/*
	 *	@brief Road's unique ID
	 */
	int id;
	/*
	 *	@brief Road's name
	 */
	std::string name;
	/*
	 *	@brief If it allows vehicles to travel in both directions
	 */
	bool two_way;
public:
	/*
	 * @brief Creates a Road
	 */
	Road(int number_ID, std::string street_name, bool two_way_street);
	/*
	 * @brief Returns the ID
	 */
	int getId() const;
	/*
	 * @brief Returns the name
	 */
	const std::string& getName() const;
	/*
	 * @brief Returns true if street is 'two-way'
	 */
	bool isTwoWay() const;
};

Road* searchRoad(int id, std::vector<Road*> &estradas);

#endif /* ROAD_H_ */
