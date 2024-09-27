/* 
 * INF559 Data Lab 
 * 
 * <name: Zhicheng HUI> <userid: zhicheng.hui>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Run ./driver.pl on the lab machines before submitting.  
 *      If you don't, you are on your own.
 */

#endif

/* bit manipulation */

/*
 * func1 - returns 1 if x == 0, and 0 otherwise 
 *   Examples: func1(5) = 0, func1(0) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int func1(int x) {
  return !x;
}

/* 
 * func2 - ~(x|y) using only ~ and & 
 *   Example: func2(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int func2(int x, int y) {
  // De Morgan's laws: ~(x | y) = (~x) & (~y)
  return (~x) & (~y);
}

/* 
 * func3 - pads n upper bits with 1's
 *  You may assume 0 <= n <= 32
 *  Example: func3(4) = 0xF0000000
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 1
 */
int func3(int n) {
  int result;
  int n1;
  int n2;
  
  /* Having n upper 1's amounts to having (32 - n) lower 0's, so we could
     compute the value of 0xFFFFFFFF << (32 - n)
  */
  result = ~0;
  // (32 - n) = (32 + (~n + 1)) = (33 + ~n), by two's complement
  n = 33 + ~n;
  /* However, when n equals 0, (32 - n) equals 32 and left-shifting 32 bits
     on a 32-bit integer is undefined behavior, we should divide (32 - n) into
     two parts smaller than 32 and use : (x << n1) << n2 = x << (n1 + n2)
  */
  n1 = n >> 1;
  n2 = n1 + (n & 1);
  result = result << n1;
  result = result << n2;
  
  return result;
}

/* 
 * func4 - set all bits of result to least significant bit of x
 *   Example: func4(5) = 0xFFFFFFFF, func4(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int func4(int x) {
  int bit;
  int result;
  // x & 1 gives the first bit of x
  bit = x & 1;
  /* Since right shifts are arithmetic, right shifting 31 bits would set all
     bits equal to the highest bit
  */
  result = bit << 31;
  result = result >> 31;
  return result;
}

/* 
 * func5 - return 1 if all even-numbered bits in word set to 1
 *   Examples func5(0xFFFFFFFE) = 0, func5(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int func5(int x) {
  int mask;
  int result;
  
  /* We check 8 bits every time since the biggest allowed constant is 0xFF,
     we perform bit-wise and on every 8 bits and 0x55 = 01010101, if the result
     does not equal to 0x55 = 01010101, then at least one even-numbered bit is 0
  */
  mask = 0x55;
  result = mask & x;
  result = result & (x >> 8);
  result = result & (x >> 16);
  result = result & (x >> 24);
  /* Equality check can be implemented by minus (two's complement) and not:
     (a == b) = (a - b == 0) = !(a - b) = !(a + ~b + 1)
  */
  result = result + ~mask + 1;
  return !result;
}

/* 
 * func6 - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: func6(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int func6(int x, int n) {
  int result;
  int bitmask;
  int n1;
  int n2;
  
  /* We can perform an arithmetic right shift and manually
     set all the high bits to zero. This can be done by
     doing a bit-wise and with a bitmask
  */
  result = x >> n;
  
  /* The bitmask starts with n 0's and ends with 1's
     , we imitate what is done in func3
  */
  bitmask = ~0;
  n = 33 + ~n;
  n1 = n >> 1;
  n2 = n1 + (n & 1);
  bitmask = bitmask << n1;
  bitmask = bitmask << n2;
  bitmask = ~bitmask;
  
  return result & bitmask;
}

/*
 * func7 - returns 1 if x contains an odd number of 0's
 *   Examples: func7(5) = 0, func7(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int func7(int x) {
  int count1;
  int count2;
  
  /* The result of performing exclusive or on two 1's is 0.
     We want to xor together all 32 bits of x and check the result,
     if the result is 1, we have an odd number of 0's
  */
  
  // We start by xoring every 8 bits
  count1 = x ^ (x >> 8);
  count1 = count1 ^ (x >> 16);
  count1 = count1 ^ (x >> 24);
  
  // Then we xor every 2 bits
  count2 = count1 ^ (count1 >> 2);
  count2 = count2 ^ (count1 >> 4);
  count2 = count2 ^ (count1 >> 6);

  // Finally we merge the remaining 2 bits
  return (count2 & 1) ^ ((count2 >> 1) & 1);
}


/* 2's complement */

/* 
 * func8 - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int func8(void) {
  // minimum two's complement 32-bit integer is 0x80000000
  return 1 << 31;
}

/*
 * func9 - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int func9(int x) {
  /* The maximum two's complement number max = 0x7FFFFFFF satisfies
     ~max = 0x80000000, and ~max + ~max = 0 when overflow induces truncation.
     However, another value satisfying this equation is ~max = 0, so
     we have to eliminate this case:
     
     (~x != 0) && (~x + ~x == 0) = (!(!(~x))) & !(~x + ~x) = !((!(~x)) | (~x + ~x))
  */
  return !((!(~x)) | (~x + ~x));
}

/* 
 * func10 - return -x 
 *   Example: func10(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int func10(int x) {
  // Two's complement: -x = ~x + 1
  return ~x + 1;
  
  // However, -min = min due to integer overflow
}

/* 
 * func11 - Determine if can compute x+y without overflow
 *   Example: func11(0x80000000,0x80000000) = 0,
 *            func11(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int func11(int x, int y) {
  int sign_x;
  int sign_y;
  int sign_xplusy;
  int pos_overflow;
  int neg_overflow;
  
  /* Overflow can happen in two cases:
     positive: when the highest bit of both operands are zero but that
               of the result is one
     negative: when the highest bit of both operands are one but that
               of the result is zero
  */
  sign_x = 1 & (x >> 31);
  sign_y = 1 & (y >> 31);
  sign_xplusy = 1 & ((x + y) >> 31);
  
  pos_overflow = sign_xplusy & (!sign_x) & (!sign_y);
  neg_overflow = (!sign_xplusy) & sign_x & sign_y;
  
  return (!pos_overflow) & (!neg_overflow);
}

/* 
 * func12 - return 1 if x > 0, return 0 otherwise 
 *   Example: func12(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int func12(int x) {
  int sign;
  
  /* In two's complement, the highest bit of positive numbers is zero
     and that of strictly negative numbers is one
  */
  /* Here, sign = 0 if and only if x >= 0
           sign = 1 if and only if x < 0
  */
  sign = 1 & (x >> 31);
  sign = sign | (!x);
  return !sign;
}

/*
 * func13 - adds two numbers but when positive overflow occurs, returns
 *          maximum possible value, and when negative overflow occurs,
 *          it returns minimum positive value.
 *   Examples: func13(0x40000000,0x40000000) = 0x7fffffff
 *             func13(0x80000000,0xffffffff) = 0x80000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 */
int func13(int x, int y) {
  int result;
  int xplusy;
  int sign_x;
  int sign_y;
  int sign_xplusy;
  int pos_overflow;
  int neg_overflow;
  int not_overflow;
  int max;
  int min;
  
  /* We imitate what is done in func11 to know whether and what kind
     of overflow has taken place or not
  */
  xplusy = x + y;
  sign_x = 1 & (x >> 31);
  sign_y = 1 & (y >> 31);
  sign_xplusy = 1 & (xplusy >> 31);
  
  pos_overflow = sign_xplusy & !(sign_x | sign_y);
  neg_overflow = (!sign_xplusy) & sign_x & sign_y;
  not_overflow = !(pos_overflow | neg_overflow);
  
  min = 1 << 31;
  max = ~min;
  
  /* Performing a bit-wise and with 0xFFFFFFFF makes the result unchanged,
     and performing a bit-wise and with 0 produces a zero. We perform bit-wise
     and the expected answer with 0xFFFFFFFF and other answers with 0 and add them
  */
  result = xplusy & ((not_overflow << 31) >> 31);
  result = result + (max & ((pos_overflow << 31) >> 31));
  result = result + (min & ((neg_overflow << 31) >> 31));
  return result;
}
