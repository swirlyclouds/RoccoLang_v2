#pragma once
class Parser
{
private:
	std::string stop;
public:
	Iterator<Token>* tokens;

	Parser(Iterator<Token>*  tokens, std::string stop) : tokens(tokens), stop(stop) {

	}
	void kill();
	Expression next_expression(Expression prev);
	std::vector<Expression> multiple_expressions(std::string sep, std::string end);

	std::vector<Expression> param_lst();

	void fail_if_end();
	std::vector<Expression> parse();
};

void Parser::fail_if_end() {
	if (this->tokens->end) {
		std::cout << "stopping" << std::endl;
		abort();
	}
}

Expression Parser::next_expression(Expression prev = Expression()) {
	Token t = *tokens->next;
	if (stop.find(t.get_type()) != std::string::npos) {
		return prev;
	}
	fail_if_end();
	tokens->move_next();
	if ((
		(t.get_type() == "number") ||
		(t.get_type() == "string") ||
		(t.get_type() == "symbol"))
		&& prev.nothing) {
		Expression r(t.get_type(), t.get_value());
		return next_expression(r);
	}
	else if (t.get_type() == "operation") {
		Expression nxt = next_expression();
		Expression op(t.get_value());// = new Operation(t.value);
		op.add_argument(prev);
		op.add_argument(nxt);
		auto r = next_expression(op);
		return r;
	}
	else if (t.get_type() == "(") {
		std::vector<Expression> args = multiple_expressions(",", ")");
		Expression r(prev, args);
		return next_expression(r);
	}
	else if (t.get_type() == "{") {
		std::vector<Expression> params = param_lst();
		std::vector<Expression> body = multiple_expressions(";", "}");
		Expression f(params, body);
		return next_expression(f);
	}
	else if (t.get_type() == "=") {
		if (prev.get_type() != "symbol") {
			std::cout << "oop" << std::endl;
			exit(-1);
		}
		Expression nxt = next_expression(Expression());
		Expression r(prev, nxt);
		auto y = next_expression(r);
		return y;
	}
	else {
		exit(-1);
	}
}
std::vector<Expression> Parser::param_lst() {
	if (tokens->next->get_type() != ":")
		return {};
	tokens->move_next();
	std::string type = tokens->next->get_type();
	if (type != "(")
		exit(-1);
	tokens->move_next();
	std::vector <Expression> ret = multiple_expressions(",", ")");
	for (int i = 0; i < ret.size(); i++) {
		if (ret[i].get_type() != "symbol") {
			exit(-1);
		}
	}
	return ret;
}
std::vector<Expression> Parser::multiple_expressions(std::string sep, std::string end) {
	std::vector<Expression> ret;
	fail_if_end();
	std::string type = tokens->next->get_type();
	if (type == end)
		tokens->move_next();
	else {
		Parser arg_parser = Parser(tokens, sep + end);
		while (type != end) {
			fail_if_end();
			Expression p = arg_parser.next_expression(Expression());
			if (p.get_type() != "None") {
				ret.push_back(p);
			}
			type = arg_parser.tokens->next->get_type();
			arg_parser.tokens->move_next();
		}

	}
	return ret;
}

std::vector<Expression> Parser::parse() {
	std::vector<Expression> exprs;
	while (!this->tokens->end) {
		exprs.push_back(next_expression(Expression()));
		this->tokens->move_next();
	}
	return exprs;
}