#pragma once
Expression eval_expr(Expression expr, Environment* env);
Expression eval_list(Iterator<Expression> expression_iterator, Environment* env);
Expression _operation(Expression expr, Environment* env) {
	Expression arg1 = eval_expr(expr.get_args()[0], env);
	Expression arg2 = eval_expr(expr.get_args()[1], env);
	if (expr.get_id() == "+") {
		return (Expression("number", std::to_string(atof(arg1.get_id().c_str()) + atof(arg2.get_id().c_str()))));
	}
	else if (expr.get_id() == "-") {
		return Expression("number", std::to_string(atof(arg1.get_id().c_str()) + atof(arg2.get_id().c_str())));
	}
	else if (expr.get_id() == "*") {
		return Expression("number", std::to_string(atof(arg1.get_id().c_str()) * atof(arg2.get_id().c_str())));
	}
	else if (expr.get_id() == "/") {
		return Expression("number", std::to_string(atof(arg1.get_id().c_str()) / atof(arg2.get_id().c_str())));
	}
	else if (expr.get_id() == "<") {
		return Expression("number",atof(arg1.get_id().c_str()) < atof(arg2.get_id().c_str()) ? "1" : "0");
	}
	else if (expr.get_id() == ">") {
		return Expression("number", atof(arg1.get_id().c_str()) > atof(arg2.get_id().c_str()) ? "1" : "0");
	}
	else {
		abort();
	}
}
Expression _function_call(Expression expr, Environment* env) {
	Expression fn = eval_expr(expr.get_args()[0], env); // step 1: evaluate expressions being passed in to function
	std::vector<Expression> args;
	for (int i = 1; i < expr.get_args().size(); i++) {
		//args.push_back(eval_expr(expr.get_args()[i], env));
		args.push_back(expr.get_args()[i]);
	}
	if (fn.get_type() == "function") {
		auto params = fn.get_args();
		if (params.size() != (args.size())) {
			exit(-1); // parameters aren't correct
		}
		auto body = fn.get_body();
		auto n_env = Environment(env);
		for (int i = 0; i < args.size(); i++) {
			n_env.set(params[i].get_id(), args[i]);
		}
		Iterator<Expression> temp_iter(body);
		auto output = eval_list(temp_iter, &n_env);
		return output;

	}
	else if (fn.get_type() == "native") {
		func to_run = env->run(expr.get_args()[0].get_id());
		return to_run(env, args);
	}
	exit(-12);
}
Expression eval_expr(Expression expr, Environment* env) {
	if ((expr.get_type() == "number") || (expr.get_type() == "string") || (expr.get_type() == "none")) {
		return Expression(expr.get_type(), expr.get_id());
	}
	else if (expr.get_type() == "operation") {
		return _operation(expr, env);
	}
	else if (expr.get_type() == "symbol") {
		// are we looking for a function?
		if (env->contains(expr.get_id())) {
			return *env->get(expr.get_id());
		}
		exit(-2); // if doesn't exist: crash
	}
	else if (expr.get_type() == "assignment") {
		Expression value = eval_expr(expr.get_args()[1], env);
		if (env->contains(expr.get_args()[0].get_id())) {
			if (env->get(expr.get_args()[0].get_id())->get_type() != value.get_type())
				exit(-3);
		}
		env->set(expr.get_args()[0].get_id(), value);
		return value;
	}
	else if (expr.get_type() == "call") {
		return _function_call(expr, env);
	}
	else if (expr.get_type() == "function") {
		return Expression(expr.get_args(), expr.get_body(), env);
	}
	exit(-4);
}

Expression eval_list(Iterator<Expression> expression_iterator, Environment* env) {
	Expression ret = Expression();
	std::vector<Expression> rets = {};
	while (expression_iterator.next != NULL) {
		auto expr = *expression_iterator.next;
		if (!expr.nothing) {
			rets.push_back(eval_expr(expr, env));
		}
		expression_iterator.move_next();
	}
	return rets.back();
}