#include <stdio.h>
#include <string.h>

void print_digit(char digit, int k) {
    switch (digit) {
        case '0':
            for (int i = 0; i < k; i++) printf(" ");
            printf(" ");
            for (int i = 0; i < k; i++) printf("-");
            printf(" ");
            break;
        case '1':
            for (int i = 0; i < k + 2; i++) printf(" ");
            break;
        case '2':
            for (int i = 0; i < k; i++) printf(" ");
            printf(" ");
            for (int i = 0; i < k; i++) printf("-");
            printf(" ");
            break;
        case '3':
            for (int i = 0; i < k; i++) printf(" ");
            printf(" ");
            for (int i = 0; i < k; i++) printf("-");
            printf(" ");
            break;
        case '4':
            for (int i = 0; i < k; i++) printf(" ");
            printf(" ");
            for (int i = 0; i < k; i++) printf("-");
            printf(" ");
            break;
        case '5':
            for (int i = 0; i < k; i++) printf(" ");
            printf(" ");
            for (int i = 0; i < k; i++) printf("-");
            printf(" ");
            break;
        case '6':
            for (int i = 0; i < k; i++) printf(" ");
            printf(" ");
            for (int i = 0; i < k; i++) printf("-");
            printf(" ");
            break;
        case '7':
            for (int i = 0; i < k; i++) printf(" ");
            printf(" ");
            for (int i = 0; i < k; i++) printf("-");
            printf(" ");
            break;
        case '8':
            for (int i = 0; i < k; i++) printf(" ");
            printf(" ");
            for (int i = 0; i < k; i++) printf("-");
            printf(" ");
            break;
        case '9':
            for (int i = 0; i < k; i++) printf(" ");
            printf(" ");
            for (int i = 0; i < k; i++) printf("-");
            printf(" ");
            break;
    }
}

int main() {
    int k;
    char s[256];
    scanf("%d", &k);
    scanf("%s", s);

    int len = strlen(s);

    for (int i = 0; i < len; i++) {
        if (i > 0) printf(" ");
        print_digit(s[i], k);
    }
    printf("\n");

    return 0;
}