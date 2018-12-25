#include "function_model.h"

#include <iostream>

int main(int argc, char * argv[]) {
	n_logic_var z(ZERO);
	n_logic_var one(ONE);
	n_logic_var nd(NOT_DEF);
	n_logic_var inf1(INF_VAR, 1);
	n_logic_var inf2(INF_VAR, 2);
	vector_function e(8);
	vector_function y(8,Y_0);
	vector_function x0(8,X_I,0);
	vector_function x1(8,X_I,1);
	vector_function x2(8,X_I,2);
	vector_function x3(8,X_I,3);
	vector_function x4(8,X_I,4);
}
