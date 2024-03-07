// Logan Calder, COEN79L TH 2:10
// Lab #4, poly
//
// This file contains all the method initializations for the class polynomial.
// It also contains the initializations for operator overrides, and the mathematical operations
// for calculating derivatives & integrals.
//
// File 1/3: Other files: intr_poly_tester.cpp, poly.h

#include <iostream>
#include <iomanip>
#include <cmath>
#include <climits>
#include "poly.h"

using namespace std;

namespace coen79_lab4
{

    // CONSTRUCTOR for the polynomial class
    polynomial::polynomial(double c, unsigned int exponent)
    {
        clear(); // Same as clear, so just call it here
        data[exponent] = c;
    }

    // MODIFICATION MEMBER FUNCTIONS for the polynomial class
    void polynomial::assign_coef(double coefficient, unsigned int exponent)
    {
        data[exponent] = coefficient;
    }

    void polynomial::add_to_coef(double amount, unsigned int exponent)
    {
        data[exponent] += amount;
    }

    void polynomial::clear()
    {
        for (int i = 0; i < CAPACITY; i++) // Same as constructor
        {
            data[i] = 0;
        }
    }

    // CONSTANT MEMBER FUNCTIONS for the polynomial class
    polynomial polynomial::antiderivative() const
    {
        polynomial integral(0, 0);
        for (int i = 0; i < MAXIMUM_DEGREE; i++)
        {
            integral.data[i + 1] = data[i] / (i + 1);
        }
        return integral;
    }

    double polynomial::coefficient(unsigned int exponent) const
    {
        return (exponent > MAXIMUM_DEGREE) ? 0 : data[exponent];
    }

    double polynomial::definite_integral(double x0, double x1) const
    {
        polynomial integral;
        integral = antiderivative();
        double u, l;
        u = l = 0.0;

        for (int i = 0; i < MAXIMUM_DEGREE; i++)
        {
            u += (integral.data[i] * pow(x1, i));
            l += (integral.data[i] * pow(x0, i));
        }
        return u - l;
    }

    unsigned int polynomial::degree() const
    {
        // Since exponents are in order, we can start from highest and work our way down
        for (int i = CAPACITY - 1; i >= 0; i--)
        {
            if (data[i] != 0)
            {
                return i;
            }
        }
        return 0;
    }

    polynomial polynomial::derivative() const
    {
        polynomial deriv;
        for (int i = 1; i < MAXIMUM_DEGREE; i++)
        {
            deriv.data[i - 1] = data[i] * i;
        }
        return deriv;
    }

    double polynomial::eval(double x) const
    {
        double plugged = 0.0;
        for (int i = 0; i < CAPACITY; i++)
        {
            plugged += data[i] * pow(x, i);
        }
        return plugged;
    }

    bool polynomial::is_zero() const
    {
        for (int i = 0; i < MAXIMUM_DEGREE; i++)
        {
            if (data[i] != 0)
                return false;
        }
        return true;
    }

    unsigned int polynomial::next_term(unsigned int e) const
    {
        for (int i = e + 1; i < MAXIMUM_DEGREE; i++)
        {
            if (data[i] != 0)
            {
                return i;
            }
        }
        return 0;
    }

    unsigned int polynomial::previous_term(unsigned int e) const
    {
        for (int i = e - 1; i >= MAXIMUM_DEGREE; i--)
        {
            if (data[i] != 0)
            {
                return i;
            }
        }
        return UINT_MAX;
    }

    double polynomial::operator()(double x) const
    {
        return eval(x);
    }

    polynomial operator+(const polynomial &p1, const polynomial &p2)
    {
        polynomial dummy;
        for (int i = 0; i < polynomial::CAPACITY; i++)
        {
            dummy.assign_coef(p1.coefficient(i) + p2.coefficient(i), i);
        }
        return dummy;
    }

    polynomial operator-(const polynomial &p1, const polynomial &p2)
    {
        polynomial dummy; // I experimented but couldn't figure out how to use the *
                          // operator to limit repeating code.
        for (int i = 0; i < polynomial::CAPACITY; i++)
        {
            dummy.assign_coef(p1.coefficient(i) - p2.coefficient(i), i);
        }
        return dummy;
    }

    polynomial operator*(const polynomial &p1, const polynomial &p2)
    {
        polynomial dummy;
        for (int i = 0; i <= p1.degree(); i++)
        {
            for (int j = 0; j <= p2.degree(); j++)
            {
                dummy.add_to_coef(p1.coefficient(i) * p2.coefficient(j), i + j);
            }
        }
        return dummy;
    }

    // NON-MEMBER OUTPUT FUNCTIONS for the polynomial Class
    std::ostream &operator<<(std::ostream &out, const polynomial &p)
    {
        streamsize s = out.precision();
        unsigned int degree = p.degree();

        for (int i = p.degree(); i >= 0; i--)
        {
            if (p.degree() == 0)
            {
                out << p.coefficient(0);
            }
            else
            {
                if (i == p.degree())
                {
                    out << p.coefficient(i) << "x^" << i << " ";
                }
                else if (i < p.degree() && i > 1)
                {
                    (p.coefficient(i) >= 0) ? out << "+ " : out << "- ";
                    out << fabs(p.coefficient(i)) << "x^" << i << " ";
                }
                else if (i == 1)
                {
                    if (p.coefficient(i) < 0)
                    {
                        out << "- ";
                    }
                    else
                    {
                        out << "+ ";
                    }
                    out << fabs(p.coefficient(i)) << "x ";
                }
                else if (i == 0)
                {
                    if (p.coefficient(i) < 0)
                    {
                        out << "- ";
                    }
                    else
                    {
                        out << "+ ";
                    }
                    out << fabs(p.coefficient(i));
                }
            }
        }
        return out;
    }

}