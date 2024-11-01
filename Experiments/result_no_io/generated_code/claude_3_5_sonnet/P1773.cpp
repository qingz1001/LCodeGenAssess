#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_LEN 1001

long long dp_min[MAX_LEN][51];
long long dp_max[MAX_LEN][51];
int k_min[MAX_LEN][51];
int k_max[MAX_LEN][51];

int main() {
    char num[MAX_LEN];
    int m;
    
    scanf("%s", num);
    scanf("%d", &m);
    
    int len = strlen(num);
    
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < m; j++) {
            dp_min[i][j] = LLONG_MAX;
            dp_max[i][j] = LLONG_MIN;
        }
    }
    
    long long value = 0;
    for (int i = 0; i < len; i++) {
        value = (value * 10 + num[i] - '0') % m;
        dp_min[i][value] = dp_max[i][value] = value;
    }
    
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < m; j++) {
            if (dp_min[i][j] != LLONG_MAX) {
                value = 0;
                for (int k = i + 1; k < len; k++) {
                    value = (value * 10 + num[k] - '0') % m;
                    long long new_val = (j * value) % m;
                    if (dp_min[k][new_val] > dp_min[i][j]) {
                        dp_min[k][new_val] = dp_min[i][j];
                        k_min[k][new_val] = k_min[i][j] + 1;
                    }
                    if (dp_max[k][new_val] < dp_max[i][j]) {
                        dp_max[k][new_val] = dp_max[i][j];
                        k_max[k][new_val] = k_max[i][j] + 1;
                    }
                }
            }
        }
    }
    
    long long min_x = LLONG_MAX, max_x = LLONG_MIN;
    int min_k = 0, max_k = 0;
    
    for (int j = 0; j < m; j++) {
        if (dp_min[len-1][j] < min_x) {
            min_x = dp_min[len-1][j];
            min_k = k_min[len-1][j];
        }
        if (dp_max[len-1][j] > max_x) {
            max_x = dp_max[len-1][j];
            max_k = k_max[len-1][j];
        }
    }
    
    printf("%lld %d %lld %d\n", min_x, min_k, max_x, max_k);
    
    return 0;
}