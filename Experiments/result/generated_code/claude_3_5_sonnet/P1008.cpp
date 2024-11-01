#include <stdio.h>
#include <stdbool.h>

bool used[10];

bool is_valid(int a, int b, int c) {
    return b == 2 * a && c == 3 * a;
}

void generate(int a, int b, int c) {
    if (a > 0 && b > 0 && c > 0 && is_valid(a, b, c)) {
        printf("%d %d %d\n", a, b, c);
    }
}

void permute(int depth, int a, int b, int c) {
    if (depth == 9) {
        generate(a, b, c);
        return;
    }
    
    for (int i = 1; i <= 9; i++) {
        if (!used[i]) {
            used[i] = true;
            if (depth < 3) permute(depth + 1, a * 10 + i, b, c);
            else if (depth < 6) permute(depth + 1, a, b * 10 + i, c);
            else permute(depth + 1, a, b, c * 10 + i);
            used[i] = false;
        }
    }
}

int main() {
    permute(0, 0, 0, 0);
    return 0;
}