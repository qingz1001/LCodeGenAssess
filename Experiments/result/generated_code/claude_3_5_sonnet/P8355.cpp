#include <stdio.h>
#include <string.h>

#define MAX_N 1000001

char s[MAX_N];
int n;

int max(int a, int b) {
    return a > b ? a : b;
}

int solve() {
    int left = 0, right = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') left++;
        else right++;
    }
    
    return 2 * (left < right ? left : right);
}

int main() {
    scanf("%d", &n);
    scanf("%s", s);
    
    printf("%d\n", solve());
    
    return 0;
}