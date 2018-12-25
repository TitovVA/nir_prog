#include "function_model.h"

vector_function::vector_function(unsigned s, generation_flag fl, unsigned number_of_x): size(s){
	deep = 0;
	if (fl == X_I){
		int len = size/(1 << number_of_x);
		int v = ZERO;
		hash = 0;
		for(unsigned i = 0; i < size; i += len){
			for (unsigned j = i; j < i+len; ++j){
				value.push_back(n_logic_var(v));
				hash = (hash << 1) | (1 & v); 
			}
			v = (!v)*ONE;
		}
		y_num = 0;
	}
	else if (fl == Y_0){
		hash = (1<<size);
		for(unsigned i = 0; i < size; ++i){
			value.push_back(n_logic_var(INF_VAR,0));
		}
		y_num = 1;
	}
	else{
		hash = 0;
		for(unsigned i = 0; i < size; ++i){
			value.push_back(n_logic_var(NOT_DEF));
		}
		y_num = 0;
	}	
}

const vector_function vector_function::operator & (const n_logic_var &v2){
	if (size != v2.size){throw("size_error!\n");}
	vector_function result(size,EMPTY);
	if (deep >= v2.deep){
		result.deep = deep;
	}
	else{
		result.deep = v2.deep;
	}
	result.hash = hash | v2.hash;
	for (unsigned i = 0; i < size; ++i){
		if ((value[i] == ZERO) || (v2.value[i] == ZERO)){
			result.hash = result.hash & ~(1<<i)
		}
	}
}
