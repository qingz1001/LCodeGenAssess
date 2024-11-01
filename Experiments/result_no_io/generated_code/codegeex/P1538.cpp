#include <stdio.h>
#include <string.h>

void printNumber(int number, int k) {
    switch (number) {
        case 0:
            printf(" %d  %d\n %d%d%d\n  %d %d\n  %d %d\n  %d %d\n", k, k, k, k, k, k, k, k, k, k, k, k);
            break;
        case 1:
            printf("    %d\n    %d\n    %d\n    %d\n    %d\n    %d\n", k, k, k, k, k, k);
            break;
        case 2:
            printf(" %d  %d\n  %d %d\n    %d\n  %d %d\n%d  %d\n", k, k, k, k, k, k, k, k, k, k);
            break;
        case 3:
            printf(" %d  %d\n  %d %d\n    %d\n  %d %d\n  %d %d\n %d  %d\n", k, k, k, k, k, k, k, k, k, k, k, k);
            break;
        case 4:
            printf("  %d %d\n  %d %d\n  %d %d\n %d%d%d\n    %d\n    %d\n", k, k, k, k, k, k, k, k, k, k, k);
            break;
        case 5:
            printf("%d  %d\n%d  %d\n%d  %d\n  %d %d\n  %d %d\n %d  %d\n", k, k, k, k, k, k, k, k, k, k, k, k, k, k);
            break;
        case 6:
            printf("%d  %d\n%d  %d\n%d  %d\n%d%d%d\n  %d %d\n  %d %d\n %d  %d\n", k, k, k, k, k, k, k, k, k, k, k, k, k, k);
            break;
        case 7:
            printf(" %d  %d\n  %d %d\n    %d\n    %d\n    %d\n    %d\n    %d\n", k, k, k, k, k, k, k, k, k, k);
            break;
        case 8:
            printf("%d  %d\n%d%d%d\n  %d %d\n %d  %d\n%d%d%d\n  %d %d\n %d  %d\n", k, k, k, k, k, k, k, k, k, k, k, k, k, k, k, k, k, k);
            break;
        case 9:
            printf("%d  %d\n%d%d%d\n  %d %d\n %d%d%d\n    %d\n  %d %d\n %d  %d\n", k, k, k, k, k, k, k, k, k, k, k, k, k, k, k, k);
            break;
    }
}

int main() {
    int k;
    char s[256];
    scanf("%d", &k);
    scanf("%s", s);
    int length = strlen(s);
    for (int i = 0; i < length; i++) {
        if (i > 0) printf(" ");
        printNumber(s[i] - '0', k);
    }
    return 0;
}