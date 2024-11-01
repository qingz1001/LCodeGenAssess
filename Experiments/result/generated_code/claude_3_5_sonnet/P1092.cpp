#include <stdio.h>
#include <string.h>

#define MAX_N 26

int n;
char a[MAX_N + 1], b[MAX_N + 1], c[MAX_N + 1];
int map[MAX_N], used[MAX_N], ans[MAX_N];

int check(int x) {
    int i, carry = 0;
    for (i = n - 1; i >= 0; i--) {
        int sum = map[a[i] - 'A'] + map[b[i] - 'A'] + carry;
        if (sum % n != map[c[i] - 'A']) return 0;
        carry = sum / n;
    }
    return carry == 0;
}

int dfs(int x) {
    if (x == n) return check(x);
    int i;
    for (i = 0; i < n; i++) {
        if (!used[i]) {
            used[i] = 1;
            map[x] = i;
            if (dfs(x + 1)) {
                ans[x] = i;
                return 1;
            }
            used[i] = 0;
        }
    }
    return 0;
}

int main() {
    scanf("%d", &n);
    scanf("%s%s%s", a, b, c);
    
    dfs(0);
    
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    
    return 0;
}