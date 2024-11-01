#include <stdio.h>

#define MAX 65

int n, b, d;
int code[MAX];
int count = 0;

int hamming_distance(int x, int y) {
    int dist = 0;
    int diff = x ^ y;
    while (diff) {
        dist += diff & 1;
        diff >>= 1;
    }
    return dist;
}

int is_valid(int num) {
    for (int i = 0; i < count; i++) {
        if (hamming_distance(num, code[i]) < d) {
            return 0;
        }
    }
    return 1;
}

void find_codes() {
    for (int i = 0; i < (1 << b) && count < n; i++) {
        if (is_valid(i)) {
            code[count++] = i;
        }
    }
}

void print_codes() {
    for (int i = 0; i < n; i++) {
        printf("%d", code[i]);
        if ((i + 1) % 10 == 0 || i == n - 1) {
            printf("\n");
        } else {
            printf(" ");
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &b, &d);
    find_codes();
    print_codes();
    return 0;
}