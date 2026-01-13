#include <stdio.h>
int main()
{
    char ch;
 char s[100];
    char sen[100];
   scanf("%c\n",&ch);
   scanf("%s\n",s);
   scanf("%[^\n]",sen);
    printf("%c\n",ch);
    printf("%s\n",s);
    printf("%s\n",sen);
    
    return 0;
    
}
