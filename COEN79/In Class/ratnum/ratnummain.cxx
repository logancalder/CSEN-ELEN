/*
 * Name: Sin-Yaw Wang
 * Email: swang24@scu.edu
 *
 * Assignment: Rational Number
 */
#include <cstdio>
#include <iomanip>
#include <iostream>

using namespace std; // for ostream
#include "ratnum.h"
using namespace coen79;

int main(int argc, char *argv[])
{
	RatNum x(1, 3);
	RatNum y(-55, 22);
	RatNum z(100, 305);
	RatNum a(x);
	RatNum b = z;

	// Replace these with your test code
	cout << x << endl;
	cout << y << endl;
	cout << z << endl;
	cout << a << endl;
	cout << b << endl;
	cout << "Try operators" << endl;
	cout << x + y << endl;
	cout << x - y << " OUR SUBTRACTION" << endl;
	cout << x * y << endl;
	cout << x / y << endl;
	if (x < y)
		cout << "less" << endl;
	if (x == y)
		cout << "equal" << endl;	
	return 0;
}
