#include <stdio.h>
#include <stdbool.h>

#define MAX_N 20
#define MAX_SUM 5000001

int n, k;
int numbers[MAX_N];
int count = 0;

bool isPrime(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

void dfs(int start, int selected, int sum) {
    if (selected == k) {
        if (isPrime(sum)) {
            count++;
        }
        return;
    }
    
    for (int i = start; i < n; i++) {
        dfs(i + 1, selected + 1, sum + numbers[i]);
    }
}

int main() {
    scanf("%d %d", &n, &k);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &numbers[i]);
    }
    
    dfs(0, 0, 0);
    
    printf("%d\n", count);
    
    return 0;
}