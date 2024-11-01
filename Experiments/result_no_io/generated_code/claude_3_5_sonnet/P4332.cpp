#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 500005
#define MAX_M 1500005

int n, q;
int tree[MAX_N][3];
int input[MAX_M];
int output[MAX_N];
int stack[MAX_N], top;

void dfs(int node) {
    if (node > n) {
        output[node] = input[node];
        return;
    }
    
    for (int i = 0; i < 3; i++) {
        if (output[tree[node][i]] == -1) {
            dfs(tree[node][i]);
        }
    }
    
    int count_0 = 0, count_1 = 0;
    for (int i = 0; i < 3; i++) {
        if (output[tree[node][i]] == 0) count_0++;
        else count_1++;
    }
    
    output[node] = (count_1 > count_0);
}

void update(int x) {
    input[x] ^= 1;
    
    top = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            if (tree[i][j] == x) {
                stack[top++] = i;
                break;
            }
        }
    }
    
    while (top > 0) {
        int node = stack[--top];
        int old_output = output[node];
        
        int count_0 = 0, count_1 = 0;
        for (int i = 0; i < 3; i++) {
            if (output[tree[node][i]] == 0) count_0++;
            else count_1++;
        }
        
        output[node] = (count_1 > count_0);
        
        if (output[node] != old_output && node != 1) {
            for (int i = 1; i <= n; i++) {
                for (int j = 0; j < 3; j++) {
                    if (tree[i][j] == node) {
                        stack[top++] = i;
                        break;
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d", &tree[i][0], &tree[i][1], &tree[i][2]);
    }
    
    for (int i = n + 1; i <= 3 * n + 1; i++) {
        scanf("%d", &input[i]);
    }
    
    memset(output, -1, sizeof(output));
    dfs(1);
    
    scanf("%d", &q);
    
    for (int i = 0; i < q; i++) {
        int x;
        scanf("%d", &x);
        update(x);
        printf("%d\n", output[1]);
    }
    
    return 0;
}