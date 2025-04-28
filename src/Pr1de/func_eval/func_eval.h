#pragma once

#ifndef FUNC_EVAL_LIBRARY_H
#define MYDLL_API __attribute__((visibility("default")))
#define FUNC_EVAL_LIBRARY_H

#endif //FUNC_EVAL_LIBRARY_H

typedef struct {
    int text;
    int background;
} Color;

typedef enum {
    EVAL_SUCCESS,
    EVAL_ERROR
} EvalStatus;

typedef enum {
    TABLE_1_ROW,
    TABLE_2_ROW
} RowType;

typedef void (*MyCallback)(EvalStatus status,
            double value1, double value2, double value3, double value4,
            Color local_color, Color external_color);


extern "C" MYDLL_API const char* get_function_name();

extern "C" MYDLL_API double myf_math(double x, double a);

extern "C" MYDLL_API double generate_and_print_table_row(
    double x,
    double eps,
    double a,
    RowType row_type,
    Color local_color,
    MyCallback callback);
