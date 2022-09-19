#pragma once


typedef Expression (*func) (Environment*, std::vector<Expression>);
class Environment
{
	std::map < Expression*, func> native_funcs;
	std::map <std::string, Expression> items;
	Environment* parent;
public:
	Environment(Environment* env = NULL) {
        this->parent = env;
        if (env != NULL) 
            this->native_funcs = env->native_funcs;
	}
    
    // this should only ever be called when setting a library
    void set_func(std::string f_name, func x) {
        items[f_name] = Expression({}, {}, this, true);
        native_funcs[&items[f_name]] = x;
    }
    bool contains(std::string name) {
        auto search = items.find(name);
        if (search != items.end()) {
            return true;
        }
        if (parent != NULL) {
            return parent->contains(name);
        }
        return false;
    }
    void set(std::string var_name, Expression x) {
        if ((parent == NULL) ) {
            items[var_name] = x;
        }
        else if ((!parent->contains(var_name))) {
            items[var_name] = x;
        }
        else {
            parent->set(var_name, x);
        }
    }

    bool is_func(std::string name) {
        if (contains(name)) {
            std::string t = get(name)->get_type();
            return (t == "native" || t == "function") ? true: false;
        }
    }
    Expression* get(std::string name) {
        auto search = items.find(name);
        if (search == items.end()) {
            if (parent != NULL) {
                return parent->get(name);
            }
            else {
                return NULL;
            }
        }
        return &items[name];
    }
    
    // this will get natively defined functions...
    func run(std::string f_name) {
        if (contains(f_name) && (get(f_name)->get_type() == "native")) {
            return native_funcs[get(f_name)];
        }
        return NULL;
    }
};

