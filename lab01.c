#include <stdio.h>
#include <ctype.h>
#include <string.h>
 
void encrypt(char *message, char *key);
 
int main()
{
    char *text;
    char *message;
    char *key;
 
    scanf("%m[^\n]", &text);
    printf("message len --> %d\n", strlen(text));
 
    message = text;
    text = NULL;
 
    scanf("%ms[^\n]", &key);
    printf("key len --> %d\n\n", strlen(key));
 
    encrypt(message, key);
    free(message);
    free(key);
 
    return 0;
}
 
void encrypt(char *message, char *key)
{
    int c, j = 0;
    int msglen = strlen(message);
    int keylen = strlen(key);
 
    for(int i = 0; i < msglen; i++)
    {
        if(isalpha(message[i]))
        {
            c = ((toupper(message[i]) + toupper(key[j])) % 26) + 65;  
            printf("%c", c);      
            j ++;
        }
 
        else
        {
            printf("%c", message[i]);
        }
 
        if(j == keylen)
            j = 0;
    }
    printf("\n");
}