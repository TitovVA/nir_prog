#include "sim_sfe.h"

#define NOT_DEF 2
#define Y_0 3

func::func(int size, char kind, unsigned int value){
	size_vv = size;
	if (kind == 'y'){
		max_y = Y_0;
		for (int i = 0; i < size; ++i){
			value_vec.push_back(Y_0);
		}
	}
	else if (kind == 'x'){
		max_y = NOT_DEF;
		for (int i = 0; i < size; ++i){
			if ((i/value) % 2 != 0){
				value_vec.push_back(1);
			}
			else{
				value_vec.push_back(0);
			}
		}
	}
	else{
		throw("func_kind");
	}
}

void func::print(){
	for (unsigned int i = 0; i < value_vec.size(); ++i){
		if (value_vec[i] >= Y_0){
			cout << "y:" << value_vec[i] - Y_0 << ' ';
		}
		else if (value_vec[i] == NOT_DEF){
			cout << "ND ";
		}
		else{
			cout << value_vec[i] << ' ';
		}
	}
	cout << "      m_y:" << max_y - Y_0 <<"\n";
}

bool func::check(unsigned int deep){
	if (deep > 2){
		if (max_y - Y_0 < (1 << (deep - 2)) - 1){ return false;}
	}
	if (any_n()){return false;}
	return true;
}


void func::normalization(){
	if (max_y == NOT_DEF){return;}
	int next_y = Y_0;
	for (unsigned int i = 0; i < value_vec.size(); ++i){                    //
		if (value_vec[i] == next_y){
			++next_y;
		}
		else if (value_vec[i] > next_y){
			int bad_y = value_vec[i];
			value_vec[i] = next_y;
			for (unsigned int j = i + 1; j < value_vec.size(); ++j){
				if (value_vec[j] == bad_y){
					value_vec[j] = next_y;
				}
				else if (value_vec[j] == next_y){
					value_vec[j] = bad_y;
				}
			}
			++next_y;
		}
	}
	max_y = next_y - 1;
}

const func func::operator& (const func &f2){
	func f(size_vv, 'y');
	f.max_y = max_y;
	for (unsigned int i = 0; i < value_vec.size(); ++i){
		if ((value_vec[i] == 0) || (f2.value_vec[i] <= 1)){
			f.value_vec[i] = value_vec[i] * f2.value_vec[i];
		}
		else if (value_vec[i] == 1){
			if (f2.value_vec[i] == NOT_DEF){
				f.value_vec[i] = NOT_DEF;
			}
			else{
				f.value_vec[i] = max_y + 1 + f2.value_vec[i];
				if (f.value_vec[i] > f.max_y){
					f.max_y = f.value_vec[i];
				}
			}
		}
		else{
			f.value_vec[i] = NOT_DEF;
		}
	}
	f.normalization();
	return f;
}

const func func::operator| (const func &f2){
	func f(size_vv, 'y');
	f.max_y = max_y;
	for (unsigned int i = 0; i < value_vec.size(); ++i){
		if ((value_vec[i] == 1) || (f2.value_vec[i] == 1)){
			f.value_vec[i] = 1;
		}
		else if ((f2.value_vec[i] == 0)){
			f.value_vec[i] = value_vec[i];
		}
		else if (value_vec[i] == 0){
			if (f2.value_vec[i] == NOT_DEF){
				f.value_vec[i] = NOT_DEF;
			}
			else{
				f.value_vec[i] = max_y + 1 + f2.value_vec[i];
				if (f.value_vec[i] > f.max_y){
					f.max_y = f.value_vec[i];
				}
			}
		}
		else{
			f.value_vec[i] = NOT_DEF;
		}
	}
	f.normalization();
	return f;
}
const func func::operator! (){
	func f(size_vv, 'y');
	f.max_y = NOT_DEF;
	for (unsigned int i = 0; i < value_vec.size(); ++i){
		if (value_vec[i] <= 1){
			f.value_vec[i] = !value_vec[i];
		}
		else{
			f.value_vec[i] = NOT_DEF;
		}
	}
	return f;
}

const bool func::operator == (const func &f2){
	for (unsigned int i = 0; i < value_vec.size(); ++i){
		if (value_vec[i] != f2.value_vec[i]){
			return false;
		}
	}
	return true;
}

const bool func::operator >= (const func &f2){
	int next_y = Y_0;
	for (unsigned int i = 0; i < value_vec.size(); ++i){
		if (value_vec[i] <= NOT_DEF){
			if ((f2.value_vec[i] != value_vec[i]) && (f2.value_vec[i] != NOT_DEF)){             ////// 1 -> y * >1
				return false;
			}
		}
		else if (value_vec[i] == next_y){
			if (f2.value_vec[i] <= 1){return false;}
			++next_y;
			int f2_y = f2.value_vec[i];
			int y = value_vec[i];
			for (unsigned int j = i + 1; j < value_vec.size(); ++j){
				if (value_vec[j] == y){
					if ((f2.value_vec[j] != NOT_DEF) && (f2.value_vec[j] != f2_y)){
						return false;
					}
				}
			}
		}
	}
	return true;
}

bool func::windows(int num_of_val, int val){
	int q = 0;
	for (unsigned int i = 0; i < value_vec.size(); ++i){
		if (value_vec[i] <= val){
			++q;
		}
	}
	return q >= num_of_val;
}

bool func::any_n(){
	for (unsigned int i = 0; i < value_vec.size(); ++i){
		if (value_vec[i] == NOT_DEF){
			return true;
		}
	}
	return false;
}

my_best_sol::my_best_sol(int n_x){
	num_of_x = n_x;
	base_func.push_back(vector <func> ());
	int func_size = 1 << num_of_x;
	for (int n = func_size >> 1; n > 0; n = n >> 1){
		base_func[0].push_back( func(func_size, 'x', n) );
		base_func[0].push_back( !base_func[0].back() );                           /////////////////////basis///////////////////
	}
	base_func[0].push_back( func ( func_size, 'y' ) );
}

bool my_best_sol::find(func &f){
	for(unsigned int i = 0; i < base_func.back().size(); ++i){
		if (f == base_func.back()[i]){
			return true;
		}
	}
	return false;
}

bool my_best_sol::find_be(func &f){
	unsigned int i = 0;
	while (i < base_func.back().size()){
		if (f >= base_func.back()[i]){
			/*cout << "///////////////////////////\n";
			f.print();
			base_func.back()[i].print();
			cout << "///////////////////////////\n";
			*/base_func.back().erase(base_func.back().begin() + i);
		}
		else{
			if (base_func.back()[i] >= f){
				/*cout << "///////////////////////////\n";
				base_func.back()[i].print();
				f.print();
				cout << "///////////////////////////\n";
				*/return true;
			}
			++i;
		}
	}
	return false;
}
/*
void my_best_sol::remove_n(){
	unsigned int i = 0;
	while ( i < base_func.back().size()){
		if (base_func.back()[i].any_n()){
			 base_func.back().erase(base_func.back().begin() + i);
		}
		else{++i;}
	}
}

void my_best_sol::remove_y(int w, int val){
	unsigned int i = 0;
	while ( i < base_func.back().size()){
		if (!base_func.back()[i].windows(w,val)){
			 base_func.back().erase(base_func.back().begin() + i);
		}
		else{++i;}
	}
}
*/
void my_best_sol::step(){
	unsigned int next = base_func.size();
	int deep = next;
	base_func.push_back(base_func[next-1]);
	unsigned int i = 0;
	while (i < base_func[next].size()){
		if (!base_func[next][i].check(deep)){
			base_func[next].erase(base_func[next].begin() + i);
		}
		else{
			++i;
		}
	}
	if (next == 1){
		for (unsigned int i = 0; i < base_func[next-1].size(); ++i){
			func f = !base_func[next-1][i];
			if (f.windows(1,1)){
					base_func[next].push_back(f);
			}
		}
	}
	for (unsigned int i = 0; i < base_func[next-1].size(); ++i){
		if (i % 1000 == 0){
			cout << i << ": " << base_func[next].size() << "\n";
		}
		for (unsigned int j = i + 1; j < base_func[next-1].size(); ++j){
			func f = base_func[next-1][i] & base_func[next-1][j];
			if (f.check(deep)){
				if (!find_be(f)){
					if (deep == 5){
						base_func[next-1][i].print();
						base_func[next-1][j].print();
					}
					else{
						base_func[next].push_back(f);
					}
				}
			}
			f = base_func[next-1][i] | base_func[next-1][j];
			if (f.check(deep)){
				if (!find_be(f)){
					if (deep == 5){
						base_func[next-1][i].print();
						base_func[next-1][j].print();
					}
					else{
						base_func[next].push_back(f);
					}
				}
			}
		}
	}
}

void my_best_sol::print(int step){
	for (unsigned int i = 0; i < base_func[step].size(); ++i){
		cout << i + 1 << "  ";
		base_func[step][i].print();
	}
}
