#include <stdio.h>

int find_nth(int n, int a, int b, int c)
{
if (n == 1) return a;
if (n == 2) return b;
if (n == 3) return c;
return find_nth(n-1, a, b, c)
 +find_nth(n-2, a, b, c)
 +find_nth(n-3, a, b, c);
}
int main()
{
int n, a, b, c;
scanf("%d", &n);
scanf("%d %d %d", &a, &b, &c);
printf("%d", find_nth(n, a, b, c));
return 0;
}
