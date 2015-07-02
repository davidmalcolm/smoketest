/* Some simple code for smoketesting my gcc builds and gdbhooks.py */

int test_phi (int i, int j)
{
  int k;

  if (i)
    k = 3;
  else
    k = 2;
  return j * k;
}

int test_switch (int p, int q, int r)
{
  switch (p)
    {
    case 0:
      return q + r;
    case 1:
      return q - r;
    case 2:
      return q * r;
    case 3:
      return q / r;
    case 4 ... 14:
      return p - 4;
    }

  return 0;
}

struct coord
{
  double x;
  double y;
};

struct coord test_returning_struct (double x, double y)
{
  struct coord result;
  result.x = x;
  result.y = y;
}

int test_inline_asm (int i)
{
  int j;

  /* Move  i to j; then j += 1: */
  asm ("mov %1, %0\n\t"
       "add $1, %0"
       : "=r" (j)
       : "r" (i));

  return j;
}

int test_constants (int i, int j)
{
  return (i & 1000) * (j & 8675309);
}

void *test_forced_label (void)
{
  /* See https://gcc.gnu.org/onlinedocs/gcc/Labels-as-Values.html */

 my_label:
  return &&my_label;
}

float test_float (float a, float b, float c, float d)
{
  float accum = a ;
  accum *= b;
  accum *= c;
  accum *= d;
  accum += ((a * b) + (c * d)) / accum;
  return accum + a;
}

__complex__ double
test_complex (__complex__ double x,
              __complex__ double y,
              __complex__ double z)
{
  return (x + z) * (y - z);
}

extern float called_many_args (float a00, float a01, float a02, float a03, float a04,
                               float a05, float a06, float a07, float a08, float a09,
                               float a10, float a11, float a12, float a13, float a14,
                               float a15, float a16, float a17, float a18, float a19,
                               float a20, float a21, float a22, float a23, float a24,
                               float a25, float a26, float a27, float a28, float a29);
float
test_many_live_regs (float a00, float a01, float a02, float a03, float a04,
                     float a05, float a06, float a07, float a08, float a09,
                     float a10, float a11, float a12, float a13, float a14,
                     float a15, float a16, float a17, float a18, float a19,
                     float a20, float a21, float a22, float a23, float a24,
                     float a25, float a26, float a27, float a28, float a29)
{
  a00 += 0.5; a01 *= 1.5; a02 -= 2.5; a03 /= 3.5;
  a04 += 4.5; a05 *= 5.5; a06 -= 6.5; a07 /= 7.5;
  a10 += 0.5; a11 *= 1.5; a12 -= 2.5; a13 /= 3.5;
  a14 += 4.5; a15 *= 5.5; a16 -= 6.5; a17 /= 7.5;
  a20 += 0.5; a21 *= 1.5; a22 -= 2.5; a23 /= 3.5;
  a24 += 4.5; a25 *= 5.5; a26 -= 6.5; a27 /= 7.5;
  a00 += called_many_args (a29, a28, a27, a26, a25, a24, a23, a22, a21, a20,
                           a19, a18, a17, a16, a15, a14, a13, a12, a11, a10,
                           a09, a08, a07, a06, a05, a04, a03, a02, a01, a00);
  return a00;
}

/* Based on CVE-2014-1266 aka "goto fail" */
extern int foo (int);
int test_misleading_indentation (int a, int b, int c)
{
	int err;

	/* ... */
	if ((err = foo (a)) != 0)
		goto fail;
	if ((err = foo (b)) != 0)
		goto fail;
		goto fail;
	if ((err = foo (c)) != 0)
		goto fail;
	/* ... */

fail:
	return err;
}
