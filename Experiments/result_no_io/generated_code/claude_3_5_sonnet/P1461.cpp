#include <stdio.h>

#define MAX_N 64

int n, b, d;
int codes[MAX_N];
int count = 0;

int hammingDistance(int x, int y) {
    int dist = 0;
    int xor = x ^ y;
    while (xor) {
        dist += xor & 1;
        xor >>= 1;
    }
    return dist;
}

int isValid(int code) {
    for (int i = 0; i < count; i++) {
        if (hammingDistance(code, codes[i]) < d) {
            return 0;
        }
    }
    return 1;
}

void findCodes(int code) {
    if (count == n) {
        return;
    }
    
    if (isValid(code)) {
        codes[count++] = code;
        if (count == n) {
            return;
        }
    }
    
    for (int i = code + 1; i < (1 << b); i++) {
        findCodes(i);
        if (count == n) {
            return;
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &b, &d);
    
    findCodes(0);
    
    for (int i = 0; i < n; i++) {
        printf("%d", codes[i]);
        if ((i + 1) % 10 == 0 || i == n - 1) {
            printf("\n");
        } else {
            printf(" ");
        }
    }
    
    return 0;
}