#include <stdio.h>

int main() 
{
char s[1000];
int count[10] = {0};
scanf("%s", s);
for (int i = 0; s[i]; i++) 
{
if (s[i] >= '0' && s[i] <= '9') 
{
count[s[i]-'0']++;
}
}
for (int i = 0; i < 10; i++) 
{
printf("%d ", count[i]);
}
return 0;
}
