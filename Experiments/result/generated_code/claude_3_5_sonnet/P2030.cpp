#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 10000
#define MAX_M 10000
#define MAX_LEN 255

char names[MAX_N][MAX_LEN];
char queries[MAX_M][MAX_LEN];
int n, m;

bool is_prefix(const char* prefix, const char* str) {
    while (*prefix) {
        if (*prefix != *str) {
            return false;
        }
        prefix++;
        str++;
    }
    return true;
}

int count_playable() {
    int count = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (is_prefix(queries[i], names[j])) {
                count++;
                break;
            }
        }
    }
    return count;
}

long long count_arrangements() {
    long long result = 1;
    for (int i = 0; i < n; i++) {
        if (i == 0 || i == n - 1) {
            result *= 2;
        } else {
            result *= 3;
        }
    }
    return result;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        scanf("%s", names[i]);
    }
    
    for (int i = 0; i < m; i++) {
        scanf("%s", queries[i]);
    }
    
    int playable = count_playable();
    long long arrangements = count_arrangements();
    
    printf("%d\n%lld\n", playable, arrangements);
    
    return 0;
}