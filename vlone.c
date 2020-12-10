#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

struct BigNum {
    int* num;  // указатель на строку, представляющую число
    size_t len; // длина числа (строки)
    size_t cap; // то, сколько памяти выделенно для строки//числа
};

typedef struct BigNum BigNum;

void bn_free(BigNum* bn) {
    if (bn->num != NULL) {
        free(bn->num);
    }
    bn->num = NULL;
    bn->len = 0;
    bn->cap = 0;
}

int bn_resize(BigNum* bn, size_t new_cap)
{
    int* new_num = calloc(new_cap, sizeof(int));
    if (new_num == NULL) {
        return 0;
    }

    for (size_t i = 0; i < bn->len; i++) {
        new_num[i] = bn->num[i];
    }

    free(bn->num);
    bn->num = new_num;
    bn->cap = new_cap;
    return 1;
}

BigNum bn_create(size_t cap) {
    BigNum bn = {NULL, 0, 0};

    bn.num = calloc(cap, sizeof(int));
    if (bn.num == NULL) {
        return bn;
    }

    bn.cap = cap;
    return bn;
}

void bn_print(BigNum bn) {
    for (size_t i = 0; i < bn.len; i++) {
        putchar(bn.num[i]);
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Program takes one argument: file name");
        return 0xF;
    }

    FILE* in = fopen(argv[1], "r");
    if (in == NULL) {
        fprintf(stderr, "Couldn't open file %s\n", argv[1]);
        return 0xF;
    }

    const size_t init_cap = 9;
    BigNum bn;

    size_t l = 1;
    int prev_is_digit = 0;
    int line_printed = 0;
    int c = fgetc(in);
    while (c != EOF) {
        if (isdigit(c) && prev_is_digit) {
            if (bn.len == bn.cap - 2) {
                int is_ok = bn_resize(&bn, bn.cap * 2);
                if (!is_ok) {
                    fprintf(stderr, "Couldn't allocate memory for a number!\n");
                    return 0xDEAD;
                }
            }
            bn.num[bn.len] = c;
            bn.len++;
            prev_is_digit = 1;
        }

        if (isdigit(c) && !prev_is_digit) {
            bn_free(&bn);
            bn = bn_create(init_cap);
            bn.num[bn.len] = c;
            bn.len++;
            prev_is_digit = 1;
        }

        if (!isdigit(c) && prev_is_digit) {
            if (!line_printed) {
                printf("L%d: ", l);
                line_printed = 1;
            }
            bn_print(bn);
            putchar(' ');
            prev_is_digit = 0;
        }

        if (c == '\n') {
            l++;
            if (line_printed) {
                putchar('\n');
            }
            line_printed = 0;
        }

        c = fgetc(in);
    }

    if (prev_is_digit) {
        if (!line_printed) {
            printf("L%d: ", l);
        }
        bn_print(bn);
        putchar(' ');
    }

    bn_free(&bn);
    fclose(in);
}