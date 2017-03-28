/*
 * User.h
 *
 *  Created on: 15/03/2017
 *      Author: bmsp2
 */

#ifndef USER_H_
#define USER_H_

#include <string>
#include <stack>
#include "CPoint.h"

#define PAYPAL 0
#define CREDIT 1

class User{
	/*
	 * @brief Client's name
	 */
	std::string name;

	/*
	 * @brief Client's password
	 */
	std::string password;

	/*
	 * @brief Client's payment method
	 */
	int pay_method;

	/*
	 * @brief Client's payment number
	 */
	int pay_no;

	/**
	 * @brief Last CPoint visited;
	 */
	size_t last;
public:
	User() {
	}

	/*
	 * @brief Client constructor
	 */
	User(std::string cli_name, std::string cli_password, size_t cli_last, int cli_pay_method,int cli_pay_no);

	/*
	 * @brief Gets Client's name
	 */
	const std::string& getName() const;

	/*
	 * @brief Gets Client's payment method
	 */
	const int getPayMethod() const;

	/*
	 * @brief Gets Client's payment number
	 */
	int getPayNo() const;

	friend std::ofstream& operator<<(std::ofstream& out, const User& user);

	const std::string& getPassword() const;

	size_t getLast() const;
};



#endif /* USER_H_ */
