#include <stdio.h>
#include <ctype.h>


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

    size_t l = 1;
    int prev_is_digit = 0;
    int line_printed = 0;
    int c = fgetc(in);
    while (c != EOF) {
        if (isdigit(c) && prev_is_digit) {
            putchar(c);
            prev_is_digit = 1;
        }

        if (isdigit(c) && !prev_is_digit) {
            if (!line_printed) {
                printf("L%d: ", l);
                line_printed = 1;
            }
            putchar(c);
            prev_is_digit = 1;
        }

        if (!isdigit(c) && prev_is_digit) {
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

    fclose(in);
}