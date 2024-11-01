#include <stdio.h>
#include <string.h>

#define MAX_N 26

char a[MAX_N + 1], b[MAX_N + 1], c[MAX_N + 1];
int n, used[MAX_N], map[MAX_N], ans[MAX_N];

int dfs(int pos, int carry) {
    if (pos == n) return carry == 0;
    
    int x = a[pos] - 'A', y = b[pos] - 'A', z = c[pos] - 'A';
    
    if (map[x] != -1 && map[y] != -1) {
        int sum = map[x] + map[y] + carry;
        if (map[z] != -1) {
            if (sum % n != map[z]) return 0;
            return dfs(pos + 1, sum / n);
        } else {
            if (used[sum % n]) return 0;
            map[z] = sum % n;
            used[sum % n] = 1;
            if (dfs(pos + 1, sum / n)) return 1;
            used[sum % n] = 0;
            map[z] = -1;
            return 0;
        }
    }
    
    for (int i = (pos == 0 ? 1 : 0); i < n; i++) {
        if (used[i]) continue;
        if (map[x] == -1) {
            map[x] = i;
            used[i] = 1;
            if (dfs(pos, carry)) {
                ans[x] = i;
                return 1;
            }
            used[i] = 0;
            map[x] = -1;
        } else if (map[y] == -1) {
            map[y] = i;
            used[i] = 1;
            if (dfs(pos, carry)) {
                ans[y] = i;
                return 1;
            }
            used[i] = 0;
            map[y] = -1;
        }
    }
    return 0;
}

int main() {
    scanf("%d", &n);
    scanf("%s%s%s", a, b, c);
    
    memset(map, -1, sizeof(map));
    dfs(0, 0);
    
    for (int i = 0; i < n; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    
    return 0;
}