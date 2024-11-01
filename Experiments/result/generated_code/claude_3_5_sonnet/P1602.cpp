#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000

void sramoc(int k, int m) {
    int queue[MAX_LEN], front = 0, rear = 0;
    int visited[1000] = {0};
    int parent[1000], digit[1000];
    
    queue[rear++] = 0;
    visited[0] = 1;
    
    while (front < rear) {
        int curr = queue[front++];
        
        if (curr == 0 && front > 1) {
            int result[MAX_LEN], len = 0;
            while (curr != 0 || len == 0) {
                result[len++] = digit[curr];
                curr = parent[curr];
            }
            
            for (int i = len - 1; i >= 0; i--) {
                printf("%d", result[i]);
            }
            printf("\n");
            return;
        }
        
        for (int i = 0; i < k; i++) {
            int next = (curr * k + i) % m;
            if (!visited[next]) {
                visited[next] = 1;
                parent[next] = curr;
                digit[next] = i;
                queue[rear++] = next;
            }
        }
    }
}

int main() {
    int k, m;
    scanf("%d %d", &k, &m);
    sramoc(k, m);
    return 0;
}