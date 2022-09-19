#pragma once
bool regex_search(std::string c_str, std::string reg) {
		const char* cstr = c_str.c_str();
		const char* reg_ = reg.c_str();
		MRegexp* re = mregexp_compile(reg_);
		MRegexpMatch m;
		bool stat = mregexp_match(re, cstr, &m);
		mregexp_free(re);
		return stat;
	}

	std::string _scan_string(char delim, StringIter* chars) {
		std::string ret = "";
		while ((chars->next) != delim) {
			char c = chars->move_next();
			if (chars->end) {
				throw "oopsie";
			}
			ret += c;
		}
		chars->move_next();
		return ret;

	}

	std::string _scan(std::string f_char, StringIter *chars, std::string allowed) {
		std::string ret = "" + f_char;
		char p = chars->next;
		std::string p_;
		p_.push_back(p);
		while ((!chars->end) && (regex_search(p_, (allowed)))) {
			if (p == ' ') {
				break;
			}
			ret += chars->move_next();
			p = chars->next;
			p_ = "";
			p_.push_back(p);
		}
		return ret;
	}


	Iterator<Token> lex(StringIter* chars) {
		std::vector<Token> tokens;
		std::string whitespace = " \n\t";
		std::string special_chars = "(){},;=:";
		std::string operations = "+-*/<>";
		std::string isString = "\"'";

		std::string number("[.0-9]");
		std::string symbol("[_a-zA-Z]");

		while (!chars->end) {
			char c = chars->move_next();
			std::string c_str;
			c_str.push_back(c);
			//std::cout << tokens.size();
			if (whitespace.find(c) != std::string::npos) {
				// do nothing. we don't like whitespace
			}
			else if (special_chars.find(c) != std::string::npos) {
				// we found a special char :0
				tokens.push_back(Token(c_str, ""));
			}
			else if (operations.find(c) != std::string::npos) {
				tokens.push_back(Token("operation", c_str));
			}
			else if (isString.find(c) != std::string::npos) {
				tokens.push_back(Token("string", _scan_string(c, chars)));
			}
			else if (regex_search(c_str, number)) {
				tokens.push_back(Token("number", _scan(c_str, chars, "[.0-9]")));

			}
			else if (regex_search(c_str, symbol)) {
				tokens.push_back(Token("symbol", _scan(c_str, chars, "[_a-zA-Z0-9]")));
				//std::cout << "found symbol\n";
			}

		}
		return Iterator<Token>(tokens);
	}


