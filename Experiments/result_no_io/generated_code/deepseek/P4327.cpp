#include <stdio.h>
#include <string.h>

#define MAX_LEN 15

void print_frame(char c, int is_wendy) {
    if (is_wendy) {
        printf("..*..");
    } else {
        printf("..#..");
    }
}

void print_middle(char c, int is_wendy) {
    if (is_wendy) {
        printf("*.%c.*", c);
    } else {
        printf("#.%c.#", c);
    }
}

int main() {
    char input[MAX_LEN + 1];
    scanf("%s", input);
    int len = strlen(input);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < len; j++) {
            if (i == 0 || i == 4) {
                if (j % 3 == 2) {
                    print_frame(input[j], 1);
                } else {
                    print_frame(input[j], 0);
                }
            } else if (i == 1 || i == 3) {
                if (j % 3 == 2) {
                    printf(".*.*.");
                } else {
                    printf(".#.#.");
                }
            } else {
                if (j % 3 == 2) {
                    print_middle(input[j], 1);
                } else {
                    print_middle(input[j], 0);
                }
            }
            if (j < len - 1) {
                if (i == 0 || i == 4) {
                    if (j % 3 == 2) {
                        printf("*");
                    } else {
                        printf("#");
                    }
                } else if (i == 1 || i == 3) {
                    if (j % 3 == 2) {
                        printf("*");
                    } else {
                        printf("#");
                    }
                } else {
                    if (j % 3 == 2) {
                        printf("*");
                    } else {
                        printf("#");
                    }
                }
            }
        }
        printf("\n");
    }

    return 0;
}