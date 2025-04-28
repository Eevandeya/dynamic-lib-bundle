#include "func_eval.h"

#include <math.h>

#define MAX_ITERATIONS 1000000

const Color LIB_COLOR = {
    .text = 208,
    .background = 88
};

double calculate_cos_with_math(const double x) {
    return x * cos(3 * x);
}

// Each term of the series function is defined as:
// term(n) == (-1)**n * (3**(2n) * x**(2n + 1) / (2n)!

// increment(n) is essentially (term(n + 1) / term(n))
// so we can calculate term(n + 1) using term(n) and increment(n):
// term(n) * increment(n) == term(n + 1)
double increment(const double x, const int n) {
    return - (9 * pow(x, 2)) / ((2* (float) n + 2) * (2 * (float) n + 1));
}

double delta(const double value1, const double value2) {
    return sqrt(fabs(pow(value1, 2) - pow(value2, 2)));
}

double calculate_cos_with_series(const double x, const double epsilon) {

    // tern(0) = x
    double current_term = x;
    double f1 = current_term;
    current_term *= increment(x, 0);
    double f2 = f1 + current_term;

    int n = 1;
    while (fabs(f2 - f1) >= epsilon) {
        if (n >= MAX_ITERATIONS) {
            return NAN;
        }
        f1 = f2;

        current_term *= increment(x, n);
        f2 += current_term;

        n++;
    }
    return f2;
}

char *get_function_name() {
    return "x*cos(3x)";
}

double generate_and_print_table_row(
    const double x,
    const double epsilon,
    const double a,
    const RowType row_type,
    const Color local_color,
    void (*print_table_row)(
        EvalStatus status,
        double value1, double value2, double value3, double value4,
        Color local_color, Color external_color
        )
    ) {
    (void)a; // unused parameter

    EvalStatus status = EVAL_SUCCESS;

    const double series_value = calculate_cos_with_series(x, epsilon);
    const double target_value = calculate_cos_with_math(x);

    const double *first_row_value = row_type == TABLE_1_ROW ? &x : &epsilon;

    const double d = delta(series_value, target_value);
    if (isnan(series_value) || isnan(target_value) || isnan(d)
        || isinf(series_value) || isinf(target_value) || isinf(d)) {
        status = EVAL_ERROR;
    }

    print_table_row(status,
        *first_row_value, series_value, target_value, d,
        local_color, LIB_COLOR);

    return series_value;
}
