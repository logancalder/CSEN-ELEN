/*
 * Name: Sin-Yaw Wang
 * Email: swang24@scu.edu
 *
 * Assignment: Rational Number
 */
#include <cstdio>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <iostream>

using namespace std; // for ostream
#include "ratnum.h"

namespace coen79
{
	RatNum::RatNum(int n, unsigned int d)
		: whole(0), nom(0), den(0)
	{

		if (d == 0)
			return;

		this->whole = (int)(n / (int)d);
		if (this->whole != 0)
			n = abs(n) % d;
		int todivide = this->gcd(abs(n), d);
		this->nom = n / todivide;
		this->den = d / todivide;
	}

	// trivial implementaion of GCD
	unsigned int RatNum::gcd(unsigned int a, unsigned int b)
	{
		if (a == 0)
			return b;
		return this->gcd(b % a, a);
	}

	ostream &operator<<(ostream &os, const RatNum &n)
	{
		if (n.whole != 0)
			cout << n.whole << " ";
		cout << n.nom << '/' << n.den;
		return os;
	}

	// replace one of these with your code
	RatNum RatNum::operator+(RatNum const &n1) { return RatNum(1, 2); }

	RatNum RatNum::operator-(RatNum const &n1)
	{
		unsigned int temp_den1 = this->den;

		int passed_nom;

		if (this->whole != 0)
		{
			this->nom = abs(this->whole) * this->den + this->nom;
		}

		if (n1.whole != 0)
		{
			int mult = 1;
			if (n1.whole < 0 || n1.nom < 0)
			{
				mult = -1;
			}
			passed_nom = abs(n1.whole) * n1.den + abs(n1.nom);
			passed_nom *= mult;
		}
		else
		{
			passed_nom = n1.nom * temp_den1;
		}

		// first fraction
		this->nom *= n1.den;
		this->den *= n1.den;

		// second fraction
		unsigned int passed_den = n1.den * temp_den1;
		passed_nom *= temp_den1;

		return RatNum(this->nom - passed_nom, passed_den);
	}
	RatNum RatNum::operator*(RatNum const &n1) { return RatNum(1, 2); }
	RatNum RatNum::operator/(RatNum const &n1) { return RatNum(1, 2); }
	bool RatNum::operator<(RatNum const &n1) { return true; }
	bool RatNum::operator==(RatNum const &n1) { return true; }
}
