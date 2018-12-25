#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;

class func{
	int size_vv;
	int max_y;
	vector <int> value_vec;
	void normalization();
public:
	func(int size, char kind = 'y', unsigned int value = 0);
	void print();
	bool check(unsigned int yn);
	const func operator & (const func &f2);
	const func operator | (const func &f2);
	const func operator ! ();
	const bool operator == (const func &f2);
	const bool operator >= (const func &f2);
	bool any_n();
	bool windows(int num_of_val, int val);
};

class my_best_sol{
	unsigned int num_of_x;
	vector <vector <func> > base_func;
public:
	my_best_sol(int n_x);
	void step();
	bool find(func &f);
	bool find_be(func &f);
	void remove_n();
	void remove_y(int w, int val);
	void print(int step = 0);
};

