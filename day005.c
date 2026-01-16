#include <stdio.h>
void sum(int *a, int *b)
{
int sum = *a + *b;
int diff = *a - *b;
if (diff < 0)
diff = -diff;
*a = sum;
*b = diff;
}
int main()
{
int a, b;
int *pa = &a, *pb = &b;
scanf("%d %d", &a, &b);
sum(pa, pb);
printf("%d\n", a);
printf("%d",b);
return 0;
}
