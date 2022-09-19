#pragma once
std::string _strvalue(Expression value) {
	return value.get_id();
}

void import(Environment* env,std::string name, func function) {
	env->set_func(name,function);

}