#include <stdio.h>
#include <string.h>

#define MAX_LEN 101

int main() {
    int n;
    char x[MAX_LEN], y[MAX_LEN], z[MAX_LEN];
    
    scanf("%d", &n);
    scanf("%s", x);
    scanf("%s", y);
    
    int valid = 1;
    for (int i = 0; i < n; i++) {
        if (y[i] > x[i]) {
            valid = 0;
            break;
        }
        z[i] = (y[i] == x[i]) ? 'a' : y[i] + 1;
    }
    
    if (valid) {
        z[n] = '\0';
        printf("%s\n", z);
    } else {
        printf("-1\n");
    }
    
    return 0;
}