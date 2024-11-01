#include <stdio.h>
#include <string.h>

void postOrder(char *s, int len) {
    if (len == 1) {
        if (s[0] == '0') {
            printf("B");
        } else {
            printf("I");
        }
        return;
    }

    int mid = len / 2;
    postOrder(s, mid);
    postOrder(s + mid, mid);

    int allZero = 1, allOne = 1;
    for (int i = 0; i < len; i++) {
        if (s[i] == '1') {
            allZero = 0;
        } else {
            allOne = 0;
        }
    }

    if (allZero) {
        printf("B");
    } else if (allOne) {
        printf("I");
    } else {
        printf("F");
    }
}

int main() {
    int N;
    scanf("%d", &N);
    char s[1025];
    scanf("%s", s);

    postOrder(s, 1 << N);
    printf("\n");

    return 0;
}