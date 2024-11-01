#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 1000005
#define MAXQUEUE 2000005

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int n;
        long long w;
        scanf("%d %lld", &n, &w);
        char S[n+1];
        scanf("%s", S);
        if(w < n){
            printf("0\n");
            continue;
        }
        // Compute prefix function
        int pi[n];
        pi[0] = 0;
        for(int i=1;i<n;i++){
            int j = pi[i-1];
            while(j > 0 && S[i] != S[j]){
                j = pi[j-1];
            }
            if(S[i] == S[j]){
                j++;
            }
            pi[i] = j;
        }
        // Collect all borders
        int borders[26];
        int b_count = 0;
        int k = pi[n-1];
        while(k > 0){
            borders[b_count++] = k;
            k = pi[k-1];
        }
        // Add k=0
        borders[b_count++] = 0;
        // Collect step sizes
        int steps[b_count];
        for(int i=0;i<b_count;i++) steps[i] = n - borders[i];
        // BFS
        // Allocate visited array
        // To handle w up to 1e6, use a byte array
        // Initialize to 0
        // Since w can be up to 1e6, and n up to similar, it's manageable
        // dynamically allocate
        char *visited = (char*)calloc(w+2, sizeof(char));
        // Queue implementation
        long long queue[MAXQUEUE];
        int front = 0, rear = 0;
        // Start from n
        queue[rear++] = n;
        visited[n] = 1;
        while(front < rear){
            long long current = queue[front++];
            for(int i=0;i<b_count;i++){
                long long next = current + steps[i];
                if(next > w) continue;
                if(!visited[next]){
                    visited[next] = 1;
                    queue[rear++] = next;
                    if(rear >= MAXQUEUE){
                        break;
                    }
                }
            }
        }
        // Count visited from n to w
        int count = 0;
        for(long long i=n;i<=w;i++) if(visited[i]) count++;
        printf("%d\n", count);
        free(visited);
    }
    return 0;
}