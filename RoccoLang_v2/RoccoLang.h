#pragma once
void set_up(Environment* env) {

    import(env, "if", if_);
    import(env, "print", printf);
    import(env, "loop", loop_);
}
std::vector<Expression> get_eval_iter(StringIter stringIter) {
    Iterator<Token> t = lex(&stringIter);

    Parser n_parser(&t, ";");
    return n_parser.parse();
}
Expression run_program(std::string _program) {

    Environment env;
    set_up(&env);
    auto w = eval_list(get_eval_iter(StringIter(_program)), &env);

    return w;
}

std::string load_program(std::string filename) {
    std::string program = "";
    std::ifstream myfile(filename);


    if (myfile.is_open())
    {
        std::string line;
        std::cout << "loading program...\n";
        while (std::getline(myfile, line))
        {
            program += (line + '\n');
        }
        myfile.close();
    }
    return program;
}

Expression run() {
    std::string program = load_program("program.txt");
    std::cout << "loaded.\nrunning...\n";
    if (program.size() > 0)
        return run_program(program);
    return Expression();

}