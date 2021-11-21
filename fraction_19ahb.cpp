
//import libraries
#include <stdlib.h>
#include <string>
#include <vector>
#include <time.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "fraction_19ahb.h"

using namespace std;

//constructors
Fraction::Fraction() : num(0), denom(1) {}
Fraction::Fraction(int i) : num(i), denom(1) {}
Fraction::Fraction(int numer, int denomin) {
    int top, bottom, returnedGCD;
    if(denomin == 0) //cant have 0 denominator.
    {
        throw FractionException("Error. Cannot divide by 0.");
    }

    if(denomin < 0) //if the denominator is negative, we don't want that --> we want - to appear 'attached' to numerator
    {
        top = numer * -1;
        bottom = denomin * -1;
    }//close if
    else{
        top = numer;
        bottom = denomin;
    }//close else

    //assignment statement stuff to return the values to the numerator and denominator in simplified forms
    returnedGCD = gcd(top, bottom);
    num = top / returnedGCD;
    denom = bottom / returnedGCD;

}//close fraction (int, int)

//accessors
int Fraction::numerator() const {
    return num;
}
int Fraction:: denominator() const {
    return denom;
}

//For Solving for the Greatest Common Denominator.
//uses given algorithm (the photo from assignment)
int gcd( int n, int m)
{
    n= abs(n);
    m = abs(m);
    if ((m<= n) && (n % m == 0)){
        return m;
    }
    else if( n < m){
        return gcd(m, n);
    }
    else gcd (m, n % m);
} //close gcd()

//overload negation
Fraction& Fraction::operator-() {
    this->num = this->num * -1;
    return *this;
}

//overload Post and Pre Increment
Fraction& Fraction :: operator++() {
    num += denom;
    return *this;
}

Fraction Fraction :: operator++(int dummy) {
    Fraction returnedFraction(num,denom);
    num += denom;
    return returnedFraction;
}

//overload + (addition)
Fraction operator+ (const Fraction& lhs, const Fraction& rhs) {
    //check if denominator is the same (easier to do addition this way)
    if (lhs.denominator() == rhs.denominator()) {
        return Fraction((lhs.numerator() + rhs.numerator()) , lhs.denominator());
    }

        //if not, calculate the common denominator and return value using an LCM calculation
    else {
        //I could have created an LCM function, but I was lazy. solve for the LCM then multiply the numerator accordingly
        //in order to calculate the new, combined fraction. Same thing applies for subtraction.
        int lcm;
        int theGCD, lhsMultiplier, rhsMultiplier;
        theGCD = gcd(lhs.denominator(), rhs.denominator());
        lcm = (lhs.denominator() * rhs.denominator()) / theGCD;
        lhsMultiplier = lcm / lhs.denominator();
        rhsMultiplier = lcm / rhs.denominator();
        return Fraction((lhsMultiplier * lhs.numerator())+ (rhsMultiplier* rhs.numerator()), lcm);
    }
} //close overloaded +

//overload - (subtraction)
Fraction operator- (const Fraction& lhs, const Fraction& rhs) {
    //check if denom is same (easier to do subtraction this way)
    if (lhs.denominator() == rhs.denominator()) {
        return Fraction((lhs.numerator() - rhs.numerator()) , lhs.denominator());
    }
        //if not, calculate the common denom and return value
    else {
        int lcm;
        int theGCD, lhsMultiplier, rhsMultiplier;
        theGCD = gcd(lhs.denominator(), rhs.denominator());
        lcm = (lhs.denominator() * rhs.denominator()) / theGCD;
        lhsMultiplier = lcm / lhs.denominator();
        rhsMultiplier = lcm / rhs.denominator();
        return Fraction((lhsMultiplier * lhs.numerator()) - (rhsMultiplier* rhs.numerator()), lcm);
    }//close else
}//close overloaded -

//overload for multiplication
Fraction operator*(const Fraction& lhs, const Fraction& rhs){

    return Fraction((lhs.numerator() * rhs.numerator()) , (lhs.denominator() * rhs.denominator()));
}//close overloaded *

//overload for division
Fraction operator/(const Fraction& lhs, const Fraction& rhs){

    return Fraction((lhs.numerator() * rhs.denominator()) , lhs.denominator() * rhs.numerator());
}//close overloaded /

//overload for addition and assignment
Fraction& Fraction :: operator+=(const Fraction& p) {
    *this = *this + p;
    return *this;
}//close overload for addition and assignment

//overload the < operator.
bool operator<(const Fraction& lhs, const Fraction& rhs) {
    return (lhs.numerator() * rhs.denominator()) < (rhs.numerator() * lhs.denominator());
}//close overload for <

//overload the > operator.
bool operator>(const Fraction& lhs, const Fraction& rhs) {
    return (lhs.numerator() * rhs.denominator()) > (rhs.numerator() * lhs.denominator());
} //close overload for >

//overload the <= operator.
bool operator<=(const Fraction& lhs, const Fraction& rhs) {
    return (lhs.numerator() * rhs.denominator()) <= (rhs.numerator() * lhs.denominator());
} //close overload for <=

//overload the >= operator.
bool operator>=(const Fraction& lhs, const Fraction& rhs) {
    return (lhs.numerator() * rhs.denominator()) >= (rhs.numerator() * lhs.denominator());
}//close overload for >=

//overload the == operator.
bool operator==(const Fraction& lhs, const Fraction& rhs) {
    return (lhs.numerator() == rhs.numerator()) && (lhs.denominator() == rhs.denominator());
}//close overload for ==

//overload the != operator.
bool operator!=(const Fraction& lhs, const Fraction& rhs) {
    return (lhs.numerator() != rhs.numerator()) || (lhs.denominator() != rhs.denominator());
}//close overload for !=

//overload << (used with cout)
ostream& operator<<(ostream& out, const Fraction& value) {
    out << value.num << "/" << value.denom;
    return out;
}//close << overload

//overload >> (used with cin)
istream& operator>>(istream& in, Fraction& returnedFraction){
    char kms;
    //    returnedFraction.denom = 1; is needed for the final check due to the way I did the comparators
    //you'll end up with 0 numerator but != 0 denominator
    returnedFraction.denom = 1;

    cin >> returnedFraction.num;
    if(returnedFraction.num == 0)
        return in;
    else
        cin>>kms>>returnedFraction.denom;
    return in;

}//close >> overload


//error exception for invalid fraction
FractionException::FractionException(const string& m) : message(m) {}
string& FractionException::what()  {
    return message;
}













