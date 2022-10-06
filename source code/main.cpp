#include <iostream>

#include "glMath.h"
int main() {
	float a_vals[] = { 1, 0, 0, 1};
	float b_vals[] = { 8, 8, 8, 8,
					   8, 8, 5, 8,
					   8, 8, 8, 8,
					   8, 8, 8, 8 };
	matrix a(4, 1);
	a.set(a_vals);
	matrix b(4, 4);
	b.transform(1, 1, 1);
	//a = b * a;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << b.get(j, i) << "\t";
		}
		std::cout << std::endl;
	}
	return 0;
}