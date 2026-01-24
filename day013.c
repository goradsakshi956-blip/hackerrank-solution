#include <stdio.h>

int main() 
{
char s[1000];
gets(s);
for (int i = 0; s[i] ; i++) 
{
if (s[i] == ' ')
printf("\n");
else
printf("%c", s[i]);
}
return 0;
}
