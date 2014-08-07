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
