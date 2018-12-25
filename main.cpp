#include "sim_sfe.h"

using namespace std;

void test_func(){
	func x1(2, 'x', 1);
	func x2(8, 'x', 2);
	func x3(8, 'x', 1);
	//x3 = x2 & x1;
	//x2 = x2 | x1;
	//x1 = !x1;
	x1.print();
	//x2.print();
	//x3.print();
	func y1(2, 'y');
	func y2(2, 'y');
	func y3(8, 'y');
	y1.print();
	y2.print();
	//y3.print();
	y2 = y1 & x1;
	y2.print();
	y2 = x1 & y1;
	y2.print();
	y2 = y1 | x1;
	y2.print();
	y2 = x1 | y1;
	y2.print();
	//y3 = y3 | y2;
	//y3.print();
}

int main(int argc, char * argv[]) {
	int n = atoi(argv[1]);
	my_best_sol A(n);
	cout << "//////////// 0 ///////////////\n";
	A.print();
	for (int i = 1; i <=  n + 2; ++i){
		cout << "//////////// "<< i <<" ///////////////\n";
		A.step();
		A.print(i);
	}
	/*
	cout << "////////////n///////////////\n";
	A.remove_n();
	A.print(n + 1);
	cout << "////////////y///////////////\n";
	A.remove_y(1 << (n - 1), 1);
	A.print(n + 1);
	cout << "////////////last///////////////\n";
	A.step();
	A.print(n + 2);*/
	cout << "////////////test///////////////\n";
	//test_func();
}
