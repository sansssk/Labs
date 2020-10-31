#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char* encrypt(char* message, char* key) // функция, которая зашивровывает сообщение
{
    int msglen = strlen(message); //strlen  функция,которая высчитывает длину сообщения
    int keylen = strlen(key);

    char* encrypted_text = malloc(sizeof(char) * msglen);   //создаем динамический массив для зашифрованного сообщения
    int lin = 0;
    for (int pos = 0; pos < msglen; pos++, lin++)  // берем позицию равную 0->
    {
        if (lin == keylen) lin = 0;

        if (!(isalpha(message[pos])))
        {
            encrypted_text[pos] = message[pos];
            continue;
        }

        int a;
        if (islower(message[pos])) a = 'a';
        else a = 'A';

        char ted = message[pos] - a;
        char kl = key[lin] - 'a';
        encrypted_text[pos] = ((ted + kl) % 26) + a;
    }

    return encrypted_text;  // возврат динамического массива
}

char* vigenere_decryption(char* encrypted_text, char* key)        // функция, которая расшивровывает сообщение
{
    int msglen = strlen(encrypted_text); // strlen  функция,которая высчитывает длину зашифрованнаого сообщения
    int keylen = strlen(key);

    char* decrypted_text = malloc(sizeof(char) * msglen);   //создаем динамический массив для расшифрованного сообщения
    int lin = 0;
    for (int pos = 0; pos < msglen; pos++, lin++)         // берем позицию равную 0->
    {
        if (lin == keylen) lin = 0;

        if (!(isalpha(encrypted_text[pos])))
        {
            decrypted_text[pos] = encrypted_text[pos];
            continue;
        }

        int a;
        if (islower(encrypted_text[pos])) a = 'a';
        else a = 'A';

        char ted = encrypted_text[pos] - a;
        char kl = key[lin] - 'a';
        decrypted_text[pos] = ((ted + 26 - kl) % 26) + a;
    }

    return decrypted_text;     // возврат динамического массива
};

void decrypt(char* encrypted_text) // функция, которая расшивровывает сообщение
{
    char* decrypted_text;
    char key[5];                //длина ключа равна 5
    key[5] = '\0';                // для функции strlen
    for (int i1 = 97; i1 < 123; i1++)         // цикл в цикле....
    {
        key[0] = i1;
        for (int i2 = 97; i2 < 123; i2++)
        {
            key[1] = i2;
            for (int i3 = 97; i3 < 123; i3++)
            {
                key[2] = i3;
                for (int i4 = 97; i4 < 123; i4++)
                {
                    key[3] = i4;
                    for (int i5 = 97; i5 < 123; i5++)
                    {
                        key[4] = i5;
                        decrypted_text = vigenere_decryption(encrypted_text, key);   // создаем новый массив, который получен расшивровкой
                        char* str = strstr(decrypted_text, "flag");

                        if (str)
                        {
                            printf("Key: %s\nPhrase: %s\n", key, decrypted_text);
                        }
                        free(decrypted_text);
                    }
                }
            }
        }
    }
}

int main()
{
    char* message;
    char* key;

    scanf("%m[^\n]", &message);
    printf("message len --> %d\n", strlen(message));

    scanf("%ms[^\n]", &key);
    printf("key len --> %d\n\n", strlen(key));

    char* encrypted_text = encrypt(message, key);
    free(message);
    free(key);
    printf("Phrase: %s\n", encrypted_text);

    decrypt(encrypted_text);
    free(encrypted_text);

    return 0;
}
