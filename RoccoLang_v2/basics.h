#pragma once
Expression print(defArgs) {
    for (int i = 0; i < vals.size(); i++)
        x.print(_strvalue(eval_expr(vals[i], env)));
    return Nothing;
}

Expression sense(defArgs) {
    auto name = eval_expr(vals[0], env);
    auto value = Expression("number",std::to_string(x.getSensor(name.get_id())->getReading()));
    return value;
}