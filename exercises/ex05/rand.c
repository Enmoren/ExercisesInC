/*  Implementations of several methods for generating random floating-point.

Author: Enmo Ren
Copyright (c) Enmo Corporation.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software.

Output from running time_rand.c
194.282000 ms 	 dummy
593.142000 ms 	 dummy2
612.988000 ms 	 random_float
678.098000 ms 	 my_random_float
1677.001000 ms 	 my_random_float2
2147.799000 ms 	 my_random_double
644.223000 ms 	 random_double

The dummy2 is the fastest random number generator, since it only call
random() and cast the result to a float.

random_double is much faster than my_random_double.

*/

#include <stdlib.h>

// generate a random float using the algorithm described
// at http://allendowney.com/research/rand
float my_random_float()
{
    int x, exp, mant;
    float f;

    // this union is for assembling the float.
    union {
        float f;
        int i;
    } b;

    // generate 31 random bits (assuming that RAND_MAX is 2^31 - 1
    x = random();

    // use bit-scan-forward to find the first set bit and
    // compute the exponent
    asm ("bsfl %1, %0"
    :"=r"(exp)
    :"r"(x)
    );
    exp = 126 - exp;

    // use the other 23 bits for the mantissa (for small numbers
    // this means we are re-using some bits)
    mant = x >> 8;
    b.i = (exp << 23) | mant;

    return b.f;
}

// alternative implementation of my algorithm that doesn't use
// embedded assembly
float my_random_float2()
{
    int x;
    int mant;
    int exp = 126;
    int mask = 1;

    union {
        float f;
        int i;
    } b;

    // generate random bits until we see the first set bit
    while (1) {
        x = random();
        if (x == 0) {
            exp -= 31;
        } else {
            break;
        }
    }

    // find the location of the first set bit and compute the exponent
    while (x &  geneartormask) {
        mask <<= 1;
        exp--;
    }

    // use the remaining bit as the mantissa
    mant = x >> 8;
    b.i = (exp << 23) | mant;

    return b.f;
}

// compute a random double using my algorithm
double my_random_double()
{
  // declare all variables to be 64 bits integers
  int64_t s;
  int64_t mant;
  int64_t exp = 1022;
  int64_t mask = 1;

  union {
      double d;
      int64_t i;
  } b;

  // generate random bits until we see the first set bit
  while (1) {
      // Since random() generate 31 random bits, we need to call random() twice
      // to get 64 bits result. This is done by shifting first random() output
      // to the left by 32 bits and using '|' to setting last 32 bits with another
      // call of random().
      s = (random() << 32) | random();
      if (s == 0) {
          exp -= 63;
      } else {
          break;
      }
  }

  // find the location of the first set bit and compute the exponent
  while (s & mask) {
      mask <<= 1;
      exp--;
  }

  // use the remaining bit as the mantissa
  mant = s >> 11;
  // For 64 bits, we are gonna shift exp to the left by 52 and setting the bits
  // with mantissa.
  b.i = (exp << 52) | mant;

  return b.d;
}

// return a constant (this is a dummy function for time trials)
float dummy()
{
    float f = 0.5;
    return f;
}

// generate a random integer and convert to float (dummy function)
float dummy2()
{
    int x;
    float f;

    x = random();
    f = (float) x;

    return f;
}

// generate a random float using the standard algorithm
float random_float()
{
    int x;
    float f;

    x = random();
    f = (float) x / (float) RAND_MAX;

    return f;
}


// generate a random double using the standard algorithm
float random_double()
{
    int x;
    double f;

    x = random();
    f = (double) x / (double) RAND_MAX;

    return f;
}
