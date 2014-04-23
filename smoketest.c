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
