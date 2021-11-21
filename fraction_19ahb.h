
#ifndef INC_320_ASSIGNMENT_2_FRACTION_19AHB_H
#define INC_320_ASSIGNMENT_2_FRACTION_19AHB_H

#include <stdlib.h>
#include <string>
#include <vector>
#include <time.h>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

class Fraction {
public:
    //default constructor
    Fraction();
    Fraction(int);
    Fraction(int, int);
    //the two accessors, for numerator and denominator, returns the associated values
    int numerator() const;
    int denominator() const;

    //unary operator overloading things
    Fraction & operator - (); // negation, not subtraction
    Fraction & operator++(); //post incre
    Fraction operator++(int); // pre incre

    //addition and assignment operator
    Fraction & operator += (const Fraction & p);

private:
    //private integers for numerator and denominator
    int num;
    int denom;

    friend ostream & operator << (ostream & out,
                                  const Fraction & value);
    friend istream & operator >> (istream & in , Fraction & returnedFraction);
}; //close class Fraction

//overload addition, subtraction, multiplication, division
//addition and subtraction in cpp will make use of a lcm calculation to display the correct result.
//other two overloads can happen easily.
Fraction operator + (const Fraction & lhs,
                     const Fraction & rhs);
Fraction operator - (const Fraction & lhs,
                     const Fraction & rhs);
Fraction operator * (const Fraction & lhs,
                     const Fraction & rhs);
Fraction operator / (const Fraction & lhs,
                     const Fraction & rhs);

//comparison operators --> will check using the numerator values.
bool operator < (const Fraction & lhs,
                 const Fraction & rhs); // < comparison operator
bool operator <= (const Fraction & lhs,
                  const Fraction & rhs); // <= comparison operator
bool operator == (const Fraction & lhs,
                  const Fraction & rhs); // == comparison operator
bool operator != (const Fraction & lhs,
                  const Fraction & rhs); // != comparison operator
bool operator >= (const Fraction & lhs,
                  const Fraction & rhs); // >= comparison operator
bool operator > (const Fraction & lhs,
                 const Fraction & rhs); // > comparison operator

//gcd. for finding the greatest common divisor.
int gcd(int n, int m);

//fractionException, used when attempting to have a 0 denominator. Displays the associated error message.
class FractionException {
public:
    FractionException(const string & m);
    string & what();
private:
    string message;

};

#endif //INC_320_ASSIGNMENT_2_FRACTION_19AHB_H