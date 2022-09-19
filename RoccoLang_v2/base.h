#pragma once
#define defArgs Environment * env, std::vector<Expression> vals
#define Nothing Expression("None", "")
Expression printf(defArgs) {
	for (int i = 0; i < vals.size(); i++)
		std::cout << _strvalue(eval_expr(vals[i],env));
	std::cout << std::endl;
	return Nothing;
}
Expression if_(defArgs) {
	Expression condition = vals[0];
	Expression _T;
	Expression _F;
	if (vals.size() > 1) _T = vals[1];
	if (vals.size() >= 3) {
		_F = vals[2];
	}
	condition = eval_expr(condition, env);
	if (condition.get_type() == "number") {
		if (condition.get_id() == "1") {
			Expression r(("call"), { _T });
			return eval_expr(r, env);
		}
		else if(vals.size() > 2) {
			Expression r(("call"), { _F });
			return eval_expr(r, env);
		}
	}
	exit(-99);
}




Expression loop_(defArgs) {
	Expression code_to_run("call", { vals[0] });
	Expression condition = vals[1];
	if(vals[0].get_type() != "function")
		exit(-93);
	else {
		do
			eval_expr(code_to_run, env);
		while (eval_expr(condition, env).get_id() == "1");
	}
	return Nothing;
}