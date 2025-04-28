#include <iostream>
#include <cmath>
#include "func_eval.h"

typedef void (*MyCallback)(EvalStatus status,
            double value1, double value2, double value3, double value4,
            Color local_color, Color external_color);

const Color LOCAL_COLOR = {
    .text = 13,
    .background = 10,
};

namespace math_ut {
    double next_el(size_t i, double x) {
        return -1 * x*(i-1)/i;
    }
    double alexandrov_log(double eps, double x=0, double a=0, double next_el=0, size_t i=2) {
        double cur_el;
        if (i > 10000) {
            return NAN;
        }
        if (i == 2) {
            cur_el = x;
        }
        else {
            cur_el = next_el;
        }
        double next = cur_el * math_ut::next_el(i, x);

        if (abs(next - cur_el) < eps){
             if (abs(eps) > 1 && abs(cur_el) > 1)
             {
                   return NAN;
             }
             if (abs(eps) > 1 && abs(cur_el) < 1){
                 return cur_el;
             }
            return next_el;
        }
        return cur_el + alexandrov_log(eps, x, a, next, ++i);
    }
}

using namespace math_ut;

double myf_math(double x, double a) {
    return log(x + 1);
}

const char* get_function_name()
{
    auto fn = "log(x + 1)";
    return fn;
}

double generate_and_print_table_row(double x, double eps, double a, RowType row_type, Color external_color, MyCallback callback){
    double my_func = math_ut::alexandrov_log(eps, x, a);
    double math_func = myf_math(x, a);
    double delta = sqrt(abs(pow(math_func, 2) - pow(my_func, 2)));

    if (row_type == RowType::TABLE_1_ROW) {
        callback(std::isnan(abs(delta)) || std::isinf(abs(delta)) ? EvalStatus::EVAL_ERROR : EvalStatus::EVAL_SUCCESS, x, my_func, math_func, delta, external_color, LOCAL_COLOR);
    }
    else{
        callback(std::isnan(abs(delta)) || std::isinf(abs(delta)) ? EvalStatus::EVAL_ERROR : EvalStatus::EVAL_SUCCESS, eps, my_func, math_func, delta, external_color, LOCAL_COLOR);
    }
    return my_func;
}

