#include <stdio.h>

int main()
{
int a, b;
scanf("%d %d", &a, &b);
char *w[] = {"one","two","three","four","five","six","seven","eight","nine"};
for (int i = a; i <= b; i++)
{
if (i >= 1 && i <= 9)
{
   printf("%s\n", w[i - 1]);
}    
else if (i % 2 == 0) 
{
    printf("even\n");
}    
else printf("odd\n");
}
return 0;
}
