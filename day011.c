#include <stdio.h>

int main() 
{
int n;
scanf("%d", &n);
int *a = (int *)malloc(n * sizeof(int));
int sum = 0;
for (int i = 0; i < n; i++)
{
scanf("%d", &a[i]);
sum += a[i];
}
printf("%d", sum);
free(a);
return 0;
}
