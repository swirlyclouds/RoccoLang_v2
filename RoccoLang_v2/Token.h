#include <string>
#pragma once
class Token
{
	std::string token;
	std::string value;
public:
	Token(std::string t_, std::string v_) : token(t_), value(v_) {

	}
	std::string get_type() {
		return token;
	}
	std::string get_value() {
		return value;
	}
};

