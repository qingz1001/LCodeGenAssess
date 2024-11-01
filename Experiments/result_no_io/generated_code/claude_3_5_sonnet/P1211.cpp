#include <stdio.h>

int n, nums[10], count = 0;

int check(int a, int b, int c, int d, int e) {
    int num1 = 100*a + 10*b + c;
    int num2 = 10*d + e;
    
    if (num1 * e % 1000 != 100*c + 10*b + a) return 0;
    if (num1 * d % 1000 != 100*b + 10*a + 0) return 0;
    if (num1 * num2 != 1000*e + 100*d + 10*c + a) return 0;
    
    return 1;
}

void dfs(int depth, int used, int a, int b, int c, int d, int e) {
    if (depth == 5) {
        count += check(a, b, c, d, e);
        return;
    }
    
    for (int i = 0; i < n; i++) {
        if (!(used & (1 << i))) {
            int next_used = used | (1 << i);
            if (depth == 0) dfs(depth+1, next_used, nums[i], b, c, d, e);
            else if (depth == 1) dfs(depth+1, next_used, a, nums[i], c, d, e);
            else if (depth == 2) dfs(depth+1, next_used, a, b, nums[i], d, e);
            else if (depth == 3) dfs(depth+1, next_used, a, b, c, nums[i], e);
            else dfs(depth+1, next_used, a, b, c, d, nums[i]);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }
    
    dfs(0, 0, 0, 0, 0, 0, 0);
    
    printf("%d\n", count);
    
    return 0;
}