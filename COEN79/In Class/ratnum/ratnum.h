/*
 * Name: Sin-Yaw Wang
 * Email: swang24@scu.edu
 *
 * Assignment: Rational Number
 */
#ifndef RATIONALNUMH
#define RATIONALNUMH

namespace coen79 {
	class RatNum {
	public:
		RatNum(int, unsigned int);

		// These are member functions
		RatNum operator+(RatNum const &n1);
		RatNum operator-(RatNum const &n1); // this
		RatNum operator*(RatNum const &n1);
		RatNum operator/(RatNum const &n1);
		bool operator<(RatNum const &n1);
		bool operator==(RatNum const &n1);

	private:
		int whole;
		int nom;
		unsigned int den;
		unsigned int gcd(unsigned, unsigned);

	// this is not a member function
	friend ostream& operator<<(ostream& os, const RatNum& n);
	};
}
#endif
