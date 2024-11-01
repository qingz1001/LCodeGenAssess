#include <stdio.h>
#include <stdbool.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    bool visited[n + 1] = {false};
    for (int i = 0; i < n; i++) {
        visited[a[i]] = true;
    }
    
    int max_length = 0;
    for (int i = 1; i <= 1000000000; i++) {
        if (visited[i]) {
            int length = 1;
            while (visited[i + length]) {
                length++;
            }
            if (length > max_length) {
                max_length = length;
            }
        }
    }
    
    printf("%d\n", max_length);
    
    return 0;
}