#pragma once
class Expression
{
	std::string type, id;
	Environment* env;
	std::vector<Expression> args = {};
	std::vector<Expression> body = {};

public:
	bool nothing = false;
	//type
	Expression(std::string type, std::string id) {
		this->type = type;
		this->id = id;
	}
	//Call
	Expression(Expression prev, std::vector<Expression> args){
		this->type = "call"; 
		this->args.push_back(prev);
		for (int i = 0; i < args.size(); i++) {
			this->args.push_back(args[i]);
		}
	}
	Expression(std::string type, std::vector<Expression> args) {
		this->type = type;
		this->args = (args);
	}
	//assignment
	Expression(Expression prev, Expression value) {
		this->type = "assignment";
		this->add_argument(prev);
		this->add_argument(value);

	}
	//operation
	Expression(std::string id) {
		this->type = "operation";
		this->id = id;
	}
	//function
	Expression(std::vector<Expression> args, std::vector<Expression> body, Environment* env = NULL, bool native = false) {
		if (!native) {
			this->type = "function";
		}
		else
			this->type = "native";
		this->body = body;
		this->args = args;
		this->env = env;
	}
	//base
	Expression() {
		nothing = true;
	}
	

	void add_argument(Expression arg) {
		args.push_back(arg);
	}
	void set_args(std::vector<Expression> args) {
		this->args = args;
	}
	std::string get_type() {
		return type;
	}
	std::string get_id() {
		return id;
	}
	std::vector<Expression> get_args() {
		return args;
	}
	std::vector<Expression> get_body() {
		return body;
	}
	Environment* get_env() {
		return env;
	}
};

