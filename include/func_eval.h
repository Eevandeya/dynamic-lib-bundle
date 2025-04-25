#pragma once
#ifndef FUNC_EVAL_LIBRARY_H
#define FUNC_EVAL_LIBRARY_H

#ifdef __cplusplus
extern "C" {
#endif

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

    char *get_function_name();

    double generate_and_print_table_row(
        double x,
        double epsilon,
        double a,
        RowType row_type,
        Color local_color,
        void (*print_table_row)(
            EvalStatus status,
            double value1, double value2, double value3, double value4,
            Color local_color, Color external_color
            )
    );

#ifdef __cplusplus
}
#endif

#endif // FUNC_EVAL_LIBRARY_H