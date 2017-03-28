/*
 * User.cpp
 *
 *  Created on: 15/03/2017
 *      Author: bmsp2
 */

#include "User.h"

User::User(std::string cli_name, std::string cli_password, size_t cli_last, int cli_pay_method,int cli_pay_no){
	name=cli_name;
	password=cli_password;
	last=cli_last;
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

const std::string& User::getPassword() const {
	return password;
}

size_t User::getLast() const {
	return last;
}

std::ofstream& operator<<(std::ofstream& out, const User& user){
	out << user.getName() << ";" << user.getPassword() << ";";

	out << user.getPayMethod() << ";" << user.getPayNo() << ";";

	out << user.getLast();

	return out;
}
