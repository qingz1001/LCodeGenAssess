#include <stdio.h>
#include <string.h>

#define MAXN 200005

char S[MAXN];
int n, m;

void flip(int l, int r) {
    for (int i = l - 1; i < r; i++) {
        S[i] = (S[i] == '0') ? '1' : '0';
    }
}

int countOnes(int l, int r) {
    int count = 0;
    for (int i = l - 1; i < r; i++) {
        if (S[i] == '1') {
            count++;
        }
    }
    return count;
}

int main() {
    scanf("%d %d", &n, &m);
    scanf("%s", S);

    for (int i = 0; i < m; i++) {
        int op, l, r;
        scanf("%d %d %d", &op, &l, &r);
        if (op == 0) {
            flip(l, r);
        } else if (op == 1) {
            printf("%d\n", countOnes(l, r));
        }
    }

    return 0;
}