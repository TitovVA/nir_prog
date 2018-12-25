#include "function_model.h"


const n_logic_var n_logic_var::operator & (const n_logic_var &v2){
	if (((value == NOT_DEF) || (value == INF_VAR)) && ((v2.value == NOT_DEF) || (v2.value == INF_VAR))){
		return n_logic_var(NOT_DEF);
	}
	else{
		return n_logic_var(value & v2.value, y_n + v2.y_n);
	}
}

const n_logic_var n_logic_var::operator | (const n_logic_var &v2){
	if (((value == NOT_DEF) || (value == INF_VAR)) && ((v2.value == NOT_DEF) || (v2.value == INF_VAR))){
		return n_logic_var(NOT_DEF);
	}
	else{
		return n_logic_var(value | v2.value, y_n + v2.y_n);
	}
}

const n_logic_var n_logic_var::operator ! (){
	if (value == NOT_DEF){
		return n_logic_var(NOT_DEF);
	}
	else{
		return n_logic_var((~value) & ONE);
	}
}
