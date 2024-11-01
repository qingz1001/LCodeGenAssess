#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 100005
#define MAX_W 10005
#define MAX_QUEUE (10005)

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int n, w;
        scanf("%d %d", &n, &w);
        char S[MAX_N];
        scanf("%s", S);
        if(w < n){
            printf("0\n");
            continue;
        }
        // Compute prefix function
        int pi[MAX_N];
        pi[0] = 0;
        for(int i=1;i<n;i++){
            int j = pi[i-1];
            while(j >0 && S[j] != S[i]){
                j = pi[j-1];
            }
            if(S[j] == S[i]) j++;
            pi[i] = j;
        }
        // Collect all k where prefix k == suffix k
        int k_list[MAX_N];
        int k_count =0;
        k_list[k_count++] =0;
        int k = pi[n-1];
        while(k >0){
            k_list[k_count++] =k;
            k = pi[k-1];
        }
        // Compute allowed increments
        int c_list[MAX_N];
        int c_count =0;
        for(int i=0;i<k_count;i++) {
            c_list[c_count++] = n - k_list[i];
        }
        // BFS
        bool visited[MAX_W +1];
        memset(visited, 0, sizeof(visited));
        // Initialize queue
        int queue[MAX_QUEUE];
        int front =0, rear=0;
        if(n <=w){
            visited[n] = true;
            queue[rear++] =n;
        }
        while(front < rear){
            int current = queue[front++];
            for(int i=0;i<c_count;i++){
                int next = current + c_list[i];
                if(next <=w && !visited[next]){
                    visited[next] = true;
                    queue[rear++] = next;
                }
            }
        }
        // Count
        int count =0;
        for(int i=n;i<=w;i++) if(visited[i]) count++;
        printf("%d\n", count);
    }
    return 0;
}