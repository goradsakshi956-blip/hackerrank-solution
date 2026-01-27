#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void swap(char **a, char **b)
{
char *temp = *a;
*a = *b;
*b = temp;
}

int lexicographic_sort(char *a, char *b) 
{
return strcmp(a, b);
}

int lexicographic_sort_reverse(char *a, char *b) 
{
return strcmp(b, a);
}

int distinct_count(char *s) 
{
int cnt[26] = {0}, total = 0;
for (int i = 0; s[i]; i++) 
{
if (cnt[s[i] - 'a'] == 0) 
{
cnt[s[i] - 'a'] = 1;
total++;
}
}
return total;
}

int sort_by_number_of_distinct_characters(char *a, char *b) 
{
int da = distinct_count(a);
int db = distinct_count(b);
if (da == db)
return strcmp(a, b);
return da - db;
}

int sort_by_length(char *a, char *b) 
{
int la = strlen(a);
int lb = strlen(b);
if (la == lb)
return strcmp(a, b);
return la - lb;
}

void string_sort(char **arr, const int n, int (*cmp_func)(char*, char*))
{
for (int i = 0; i < n - 1; i++) 
{
for (int j = i + 1; j < n; j++) 
{
if (cmp_func(arr[i], arr[j]) > 0)
{
swap(&arr[i], &arr[j]);
}
}
}
}


int main() 
{
    int n;
    scanf("%d", &n);
  
    char** arr;
	arr = (char**)malloc(n * sizeof(char*));
  
    for(int i = 0; i < n; i++){
        *(arr + i) = malloc(1024 * sizeof(char));
        scanf("%s", *(arr + i));
        *(arr + i) = realloc(*(arr + i), strlen(*(arr + i)) + 1);
    }
  
    string_sort(arr, n, lexicographic_sort);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, lexicographic_sort_reverse);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");

    string_sort(arr, n, sort_by_length);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);    
    printf("\n");

    string_sort(arr, n, sort_by_number_of_distinct_characters);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");
}