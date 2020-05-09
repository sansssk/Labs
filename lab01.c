#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

char* vigenere_decryption(char* encrypted_text, char* key)        // функция, которая расшивровывает сообщение
{
    char *decrypted_text=malloc(sizeof(char)*strlen(encrypted_text));   //создаем динамический массив для расшифрованного сообщения
    int lin=0;
    for(int pos=0;pos<strlen(encrypted_text);pos++, lin++ )         // берем позицию равную 0-> strlen  функция,которая высчитывает длину зашифрованнаого сообщения
    {
        if(lin == strlen(key)) lin=0;
        if(!(isalpha(encrypted_text[pos])))
        {
            decrypted_text[pos]=encrypted_text[pos];
            continue;
        }
        int a;
        if(islower(encrypted_text[pos])) a='a';
        else a='A';
        char ted=encrypted_text[pos]-a;
        char kl=key[lin]-'a';
        decrypted_text[pos]=((ted+26-kl)%26)+a;    // расшифрованное сообщение расшифровываем как и шифруем
    }
    return decrypted_text;     // возврат динамического массива
};

int main()
{
    char phrase[255];
    fgets(phrase, 254,stdin);        // вводим с консоли слово
    char key[5];                //длина ключа равна 5
    key[5]='\0';                // для функции strlen
    for(int i1=97; i1<123;i1++)         // цикл в цикле....
    {
        key[0]=i1;
        for(int i2=97; i2<123;i2++)
        {
            key[1]=i2;
            for(int i3=97; i3<123;i3++)
            {
                key[2]=i3;
                for(int i4=97; i4<123;i4++)
                {
                    key[3]=i4;
                    for(int i5=97; i5<123;i5++)
                    {
                        key[4]=i5;
                        char *decrypted_phrase = vigenere_decryption(phrase,key);   // создаем новый массив, который получен расшвровкой
                        char* new= strstr(decrypted_phrase," flag ");
                        if(new)
                        {
                            printf("Key: %s\nPhrase:%s\n",key,decrypted_phrase);
                        }
                    }
                }
            }
        }
    }
    return 0;
}
