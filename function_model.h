#include <vector>

using namespace std;

#define ZERO 0
#define INF_VAR 1
#define NOT_DEF 2
#define ONE 3

class n_logic_var{
	unsigned value;
	unsigned y_n;
public:
	n_logic_var(unsigned type, unsigned n = 0): value(type), y_n(n){}
	int get(){return value;}
	const n_logic_var operator & (const n_logic_var &v2);
	const n_logic_var operator | (const n_logic_var &v2);
	const n_logic_var operator ! ();
};

enum generation_flag {EMPTY, Y_0, X_I};

class vector_function{
	vector <n_logic_var> value;
	unsigned hash;
	unsigned deep;
	unsigned y_num;
	unsigned size;
public:
	vector_function(unsigned size, generation_flag fl = EMPTY, unsigned number_of_x = 0);
	const vector_function operator & (const n_logic_var &v2);
	const vector_function operator | (const n_logic_var &v2);
	const vector_function operator ! ();
};

class func_dict{
	vector <pair <int, vector < vector_function > > > data;
	const unsigned int func_size;
public:
	func_dict(unsigned size): func_size(size){}
	void add(vector_function new_f);
};
