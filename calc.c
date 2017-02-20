/******************************************************************************
* Daniel Bachler
* 1-12-16
* calc.c
* CS120
* 	FracCalc!  Capable of addition, subtraction, multiplication, and simplification
*	of fractions.
*******************************************************************************/
#include <stdlib.h>
#include <stdio.h>

struct FRACTION {
  int numerator;
  int denominator;
};

struct MIXED_FRACTION {
  int whole_number;
  struct FRACTION proper_fraction;
};

/*Takes 2 ints, and finds the GCD, returns the value*/
int GCD(int a, int b) {
	/*For gcd you only need abs, so its taken*/
	int i, min;
	a = abs(a);
	b = abs(b);
	/*Zero check*/
	if(a == 0 || b == 0) {
		if(a>b) {
			i = a;
		} else {
			i = b;
		}
	/*If both numbers aren't zero, uses a for loop to find GCD*/	
	} else {
		if(a<b) {
			min = a;
		} else {
			min = b;
		}
		for(i = min; i > 0; i--) {
			if(a % i == 0 && b %i == 0)
				break;
		}
	}
	return i;
}

struct FRACTION add_fractions(const struct FRACTION *a, const struct FRACTION *b) {
	/*Creates a new struct that is returned, and the GCD variable*/
	struct FRACTION c;
	int divideMe;
	/*Adds together fractions into unsimplfied, then finds GCD and simplifies*/
	c.numerator = a->numerator * b->denominator + b->numerator * a->denominator;
	c.denominator = a->denominator * b->denominator;
	divideMe = GCD(c.numerator, c.denominator);
	if(divideMe != 0) {
		c.numerator /= divideMe;
		c.denominator /= divideMe;
	}
	return c;
}

struct FRACTION subtract_fractions(const struct FRACTION *a, const struct FRACTION *b) {
	/*Creates 2 structs, c holds negA, and d is returned answer struct*/
	struct FRACTION c;
	struct FRACTION d;
	/*Makes c the negative version of A, then adds fractions
	stores result in d and returns it*/
	c.numerator = a->numerator;
	c.denominator = a->denominator;
	c.numerator *= -1;
	d = add_fractions(&c, b);
	/*Makes answer correct, without it answer is wrong*/
	d.numerator *= -1;
	return d;
}

struct FRACTION multiply_fractions(const struct FRACTION *a, const struct FRACTION *b) {
	/*Creates answer struct and GCD variable*/
	struct FRACTION c; 
	int divisor; 
	/*Multiplies fractions into unsimplified form
	simplifies it and returns value*/
	c.numerator = a->numerator * b->numerator;
	c.denominator = a->denominator * b->denominator;
	divisor = GCD(c.numerator, c.denominator);
	if(divisor != 0) {
		c.numerator /= divisor;
		c.denominator /= divisor;
	}
	return c;
}

struct MIXED_FRACTION reduced_to_mixed(const struct FRACTION *fraction) {
	/*creates struct that holds proper_fraction for mixed, then creates mixed struct*/
	struct FRACTION b;
	struct MIXED_FRACTION c;
	/*makes b the same values as fraction*/
	b.numerator = fraction->numerator;
	b.denominator = fraction->denominator;
	c.whole_number = 0; 
	c.proper_fraction = b;
	/*Simplifies proper_fraction by subtracting denominator from numerator unti numerator is less than denominator*/
	while(c.proper_fraction.numerator >= c.proper_fraction.denominator && (c.proper_fraction.numerator != 0 || c.proper_fraction.denominator != 0)) {
		c.whole_number++;
		c.proper_fraction.numerator -= c.proper_fraction.denominator;
	}
	return c;
}


