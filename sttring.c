#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BAD_NUM (-1)
#define NO_ALLOC (-2)

struct BigNum {
    char* num;
    size_t len;
    size_t cap;
};

typedef struct BigNum BigNum;

int correct(int c, int base)
{
    if (isdigit(c) && c - '0' >= base) {
        return 0;
    }
    if (isalpha(c) && (toupper(c) - 'A' + 10) >= base) {
        return 0;
    }
    return 1;
}

void bn_free(BigNum* bn) {
    free(bn->num);
    bn->num = NULL;
    bn->len = 0;
    bn->cap = 0;
}

BigNum bn_resize(BigNum bn, size_t new_cap)
{
    char* new_num = calloc(new_cap, sizeof(char));
    if (new_num == NULL) {
        errno = NO_ALLOC;
        return bn;
    }
    memcpy(new_num, bn.num, bn.len);
    free(bn.num);
    bn.num = new_num;
    bn.cap = new_cap;
    return bn;
}

// f_get_bn reads number from file "in", "last_char" contains char after number.
BigNum f_get_bn(FILE* in, int base, int *last_char)
{
    errno = 0;
    BigNum cur = {
            .num = calloc(256, sizeof(char)),
            .len = 0, .cap = 256
    };
    if (cur.num == NULL) {
        errno = NO_ALLOC;
        return cur;
    }

    int c;
    int zeros_cut = 0;
    int spaces_cut = 0;
    do {
        c = fgetc(in);
        if (c == ' ' && spaces_cut == 0) { // Skip leading spaces
            continue;
        }
        if (c == '0' && zeros_cut == 0) { // Skip leading zeros
            spaces_cut = 1;
            continue;
        }
        if (c == ' ' || c == '.') {
            if (cur.len == 0) { // If number is of form 000...00, write 0
                cur.num[cur.len] = '0';
                cur.len++;
            }
            *last_char = c;
            break;
        }
        else if (correct(c, base)) {
            if (cur.len >= cur.cap - 1)
            {
                cur = bn_resize(cur, cur.cap*2);
                if (errno) return cur;
            }
            cur.num[cur.len] = (char) toupper(c);
            cur.len++;
            zeros_cut = spaces_cut = 1;
        } else {
            errno = BAD_NUM;
            bn_free(&cur);
            return cur;
        }
    } while (1);

    return cur;
}

// bn_cmp returns 1 if f > s, 0 if f == s, -1 if f < s
int bn_cmp(BigNum f, BigNum s)
{
    if (f.len > s.len) {
        return 1;
    } else if (f.len < s.len) {
        return -1;
    }

    for (size_t i = 0; i < f.len; i++)
    {
        if (f.num[i] > s.num[i]) {
            return 1;
        } else if (f.num[i] < s.num[i]) {
            return -1;
        }
    }

    return 0;
}

BigNum find_max(FILE* in, int base)
{
    errno = 0;
    int last_char = '0';

    BigNum cur = f_get_bn(in, base, &last_char);
    if (errno) return cur;
    BigNum max = cur;

    while (last_char == ' ') {
        cur = f_get_bn(in, base, &last_char);
        if (errno) return max;

        if (bn_cmp(cur, max) == 1) {
            max = cur;
        } else {
            bn_free(&cur);
        }
    }

    return max;
}

int main(int argc, char** argv) {
    FILE *in;
    if (argc == 1)
    {
        in = stdin;
    } else {
        in = fopen(argv[1], "r");
        if (errno != 0) {
            fprintf(stderr, "Couldn't open file: %s\n", strerror(errno));
            return -1;
        }
    }

    int base = 10;
    fscanf(in, "%d", &base);
    if (errno != 0) {
        fprintf(stderr, "Couldn't read base: %s\n", strerror(errno));
        return -1;
    } else if (base < 2 || base > 36) {
        fprintf(stderr, "Base should be a number between 2 and 36\n");
        return -1;
    }

    BigNum max = find_max(in, base);
    switch (errno) {
    case 0:
        printf("Max is %s\n", max.num);
        free(&max);
        break;
    case NO_ALLOC:
        fprintf(stderr, "Couldn't allocate memory!\n");
        break;
    case BAD_NUM:
        fprintf(stderr, "Bad input format!\n");
        break;
    }

    if (in != stdin)
    {
        fclose(in);
    }
}