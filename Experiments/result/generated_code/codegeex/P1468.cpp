#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int n, c;
int on[101], off[101];
int possible[101];
int count = 0;

void generate(int pos, int steps) {
    if (pos > n) {
        if (steps == c) {
            int valid = 1;
            for (int i = 1; i <= n; i++) {
                if ((possible[i] && off[i]) || (!possible[i] && on[i])) {
                    valid = 0;
                    break;
                }
            }
            if (valid) {
                for (int i = 1; i <= n; i++) {
                    putchar(possible[i] ? '1' : '0');
                }
                putchar('\n');
                count++;
            }
        }
        return;
    }
    possible[pos] = 0;
    generate(pos + 1, steps);
    possible[pos] = 1;
    generate(pos + 1, steps + 1);
}

int main() {
    scanf("%d%d", &n, &c);
    int x;
    scanf("%d", &x);
    while (x != -1) {
        on[x] = 1;
        scanf("%d", &x);
    }
    scanf("%d", &x);
    while (x != -1) {
        off[x] = 1;
        scanf("%d", &x);
    }
    generate(1, 0);
    if (count == 0) {
        printf("IMPOSSIBLE\n");
    }
    return 0;
}