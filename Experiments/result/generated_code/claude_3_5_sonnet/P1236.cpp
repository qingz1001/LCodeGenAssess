#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 4

int nums[MAXN];
char ops[] = {'+', '-', '*', '/'};
int perm[MAXN];
bool used[MAXN];

bool dfs(int depth, int res) {
    if (depth == MAXN) {
        return res == 24;
    }
    
    for (int i = 0; i < MAXN; i++) {
        if (!used[i]) {
            used[i] = true;
            perm[depth] = nums[i];
            
            for (int j = 0; j < 4; j++) {
                int new_res;
                switch (ops[j]) {
                    case '+': new_res = res + nums[i]; break;
                    case '-': new_res = res - nums[i]; break;
                    case '*': new_res = res * nums[i]; break;
                    case '/': 
                        if (nums[i] != 0 && res % nums[i] == 0)
                            new_res = res / nums[i];
                        else
                            continue;
                        break;
                }
                
                if (dfs(depth + 1, new_res)) {
                    if (depth == 0) {
                        printf("%d%c%d=%d\n", res, ops[j], nums[i], new_res);
                    } else if (depth == 1) {
                        printf("%d%c%d=%d\n", res, ops[j], nums[i], new_res);
                    } else if (depth == 2) {
                        printf("%d%c%d=24\n", res, ops[j], nums[i]);
                    }
                    return true;
                }
            }
            
            used[i] = false;
        }
    }
    
    return false;
}

bool solve() {
    for (int i = 0; i < MAXN; i++) {
        used[i] = true;
        perm[0] = nums[i];
        if (dfs(1, nums[i])) {
            return true;
        }
        used[i] = false;
    }
    return false;
}

int main() {
    for (int i = 0; i < MAXN; i++) {
        scanf("%d", &nums[i]);
    }
    
    if (!solve()) {
        printf("No answer!\n");
    }
    
    return 0;
}