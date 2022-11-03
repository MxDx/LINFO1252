int mp(int ecx, int edx)
{
  int eax = ecx;
  eax = eax + ecx;
  eax = eax + ecx;
  if (eax <= edx)
    return eax;
  else
    return edx;
}

int m1(int *a, int b) {
   return a[b];
}


int f(int ebx, int ecx, int edx) {
  ecx = ecx + ebx;
  if (ecx <= edx) {
    return ecx;
  } else {
    return edx;
  }
}

int fct(int eax) {
  if (eax > 0) {
    int ebx = 0;
    int ecx = eax;
    eax = 0;
    int edx = 0;
    do {
      ebx += 2;
      eax += ebx;
      edx += 1; 
    } while (edx < ecx);
    return eax;
  } else {
    return -1;
  }
}
