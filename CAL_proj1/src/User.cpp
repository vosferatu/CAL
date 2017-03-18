/*
 * Client.cpp
 *
 *  Created on: 15/03/2017
 *      Author: bmsp2
 */

#include "User.h"

User::User(std::string cli_name,int cli_pay_method,int cli_pay_no){
	name=cli_name;
	pay_method=cli_pay_method;
	pay_no=cli_pay_no;
}

const std::string& User::getName() const {
	return name;
}

const int User::getPayMethod() const {
	return pay_method;
}

int User::getPayNo() const {
	return pay_no;
}
