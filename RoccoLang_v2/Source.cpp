#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

#include "mregexp.h"

class Environment;


#include "Token.h"
#include "Expression.h"
#include "Environment.h"
#include "Iterator.h"
#include "Lexer.h"
#include "Parser_2.h"
#include "Evaluator.h"


#include "library.h"
#include "base.h"
#include "Fake_Funcs.h"
#include "RoccoLang.h"

#include "Robot.h" 
Robot x;
#include "basics.h"

void initialise_robot() {


    std::string program = load_program("program.txt");
    Environment env;
    set_up(&env);
    import(&env, "print", print);
    import(&env, "sense", sense);
    if (program.size() > 0) {
        Expression w = eval_list(get_eval_iter(StringIter(program)), &env);
        std::cout << "final output: (" << w.get_type() << " : " << w.get_id() << ")\n";
    }
    return;
}

int main() {
#ifdef FAKE_FUNCS
    initialise_robot();
#else
    std::cout << "---\noutput: " << run().get_id();
#endif // FAKE_FUNCS
    return 0;
}