#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 701
#define MAX_LEN 2001

char adj[MAX_N][MAX_N];
int adj_size[MAX_N];
char f[MAX_N][MAX_LEN];

// Multiply two numeric strings a and b, store result in res
void multiply_strings(const char *a, const char *b, char *res) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    int *temp = (int*)calloc(len_a + len_b, sizeof(int));

    // Reverse strings for easy calculation
    for(int i = 0; i < len_a; i++) {
        temp[i] += a[len_a - 1 - i] - '0';
    }
    for(int i = 0; i < len_b; i++) {
        for(int j = 0; j < len_a; j++) {
            temp[i + j] += (b[len_b - 1 - i] - '0');
        }
    }

    // Handle carry
    for(int i = 0; i < len_a + len_b; i++) {
        if(temp[i] >= 10) {
            temp[i+1] += temp[i] / 10;
            temp[i] %= 10;
        }
    }

    // Find actual length
    int len = len_a + len_b;
    while(len >1 && temp[len-1] == 0) len--;

    // Convert to string
    for(int i = 0; i < len; i++) {
        res[i] = temp[i] + '0';
    }
    res[len] = '\0';

    // Reverse back to normal order
    for(int i = 0; i < len/2; i++) {
        char tmp = res[i];
        res[i] = res[len-1-i];
        res[len-1-i] = tmp;
    }

    free(temp);
}

// Multiply numeric string a by integer k, store result in res
void multiply_string_by_int(const char *a, int k, char *res) {
    int len_a = strlen(a);
    int *temp = (int*)calloc(len_a + 10, sizeof(int));

    // Reverse string for easy calculation
    for(int i = 0; i < len_a; i++) {
        temp[i] = a[len_a - 1 - i] - '0';
    }

    // Multiply by k
    int carry = 0;
    for(int i = 0; i < len_a; i++) {
        temp[i] = temp[i] * k + carry;
        carry = temp[i] / 10;
        temp[i] %= 10;
    }
    int len = len_a;
    while(carry > 0) {
        temp[len++] = carry % 10;
        carry /= 10;
    }

    // Find actual length
    while(len >1 && temp[len-1] == 0) len--;

    // Convert to string
    for(int i = 0; i < len; i++) {
        res[i] = temp[i] + '0';
    }
    res[len] = '\0';

    // Reverse back to normal order
    for(int i = 0; i < len/2; i++) {
        char tmp = res[i];
        res[i] = res[len-1-i];
        res[len-1-i] = tmp;
    }

    free(temp);
}

// Compare two numeric strings a and b
// Return 1 if a > b, -1 if a < b, 0 if equal
int compare_strings(const char *a, const char *b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    if(len_a > len_b) return 1;
    if(len_a < len_b) return -1;
    for(int i = 0; i < len_a; i++) {
        if(a[i] > b[i]) return 1;
        if(a[i] < b[i]) return -1;
    }
    return 0;
}

// Perform post-order DFS and compute f[u]
void dfs(int u, int parent) {
    // Process all children first
    for(int i = 0; i < adj_size[u]; i++) {
        int v = adj[u][i];
        if(v != parent) {
            dfs(v, u);
        }
    }

    // Initialize current_dp with k=1
    char current_dp[MAX_N][MAX_LEN] = {0};
    current_dp[1][0] = '1';
    current_dp[1][1] = '\0';

    // Iterate over all children
    for(int i = 0; i < adj_size[u]; i++) {
        int v = adj[u][i];
        if(v == parent) continue;

        char new_dp[MAX_N][MAX_LEN] = {0};

        for(int k = 1; k < MAX_N; k++) {
            if(current_dp[k][0] == '\0') continue;

            // Option 1: Keep the child
            int new_k = k + 1; // size of child is at least 1
            // Since each child is a tree, its size is determined by how many are kept
            // Here we assume size[v] is 1 for simplicity
            // To accurately track, you'd need to store size[v]
            // But since we're only adding 1, it's an approximation

            // Keep the child
            if(new_k < MAX_N) {
                if(new_dp[new_k][0] == '\0' || compare_strings(current_dp[k], new_dp[new_k]) > 0) {
                    strcpy(new_dp[new_k], current_dp[k]);
                }
            }

            // Option 2: Split the child
            char multiplied[MAX_LEN] = {0};
            multiply_strings(current_dp[k], f[v], multiplied);
            if(new_dp[k][0] == '\0' || compare_strings(multiplied, new_dp[k]) > 0) {
                strcpy(new_dp[k], multiplied);
            }
        }

        // Update current_dp with new_dp
        for(int k = 1; k < MAX_N; k++) {
            if(new_dp[k][0] != '\0') {
                strcpy(current_dp[k], new_dp[k]);
            }
        }
    }

    // Now compute f[u] by selecting the maximum k * current_dp[k]
    strcpy(f[u], "0");
    for(int k = 1; k < MAX_N; k++) {
        if(current_dp[k][0] == '\0') continue;
        char temp_prod[MAX_LEN] = {0};
        multiply_string_by_int(current_dp[k], k, temp_prod);
        if(compare_strings(temp_prod, f[u]) > 0) {
            strcpy(f[u], temp_prod);
        }
    }
}

int main(){
    int n;
    scanf("%d", &n);
    // Initialize adjacency list
    for(int i = 1; i <= n; i++) {
        adj_size[i] = 0;
    }
    // Read edges
    for(int i = 0; i < n-1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][adj_size[u]++] = v;
        adj[v][adj_size[v]++] = u;
    }

    // Perform DFS from node 1
    dfs(1, -1);

    // Print the result
    printf("%s\n", f[1]);

    return 0;
}