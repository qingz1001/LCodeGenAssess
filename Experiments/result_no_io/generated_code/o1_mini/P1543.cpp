#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000001

int main(){
    int n;
    scanf("%d", &n);
    
    // Allocate memory
    int *a = (int*)malloc((n+1) * sizeof(int));
    int *head = (int*)calloc(n+1, sizeof(int));
    int *next = (int*)malloc((n+1) * sizeof(int));
    for(int i=1;i<=n;i++){
        scanf("%d", &a[i]);
        next[i] = head[a[i]];
        head[a[i]] = i;
    }
    
    // Arrays for DFS
    int *state = (int*)calloc(n+1, sizeof(int)); // 0: unvisited, 1: visiting, 2: visited
    // Arrays for DP
    int *dp0 = (int*)malloc((n+1) * sizeof(int));
    int *dp1 = (int*)malloc((n+1) * sizeof(int));
    
    long long result = 0;
    
    // Function to perform DFS and compute MIS
    // Implemented iteratively to avoid stack overflow
    for(int i=1;i<=n;i++){
        if(state[i]==0){
            int stack_size = 0;
            int stack[MAX];
            int parent[MAX];
            stack[stack_size] = i;
            parent[stack_size] = -1;
            stack_size++;
            while(stack_size >0){
                int u = stack[stack_size-1];
                if(state[u]==0){
                    state[u] = 1; // visiting
                    // Push all children
                    for(int v = head[u]; v !=0; v = next[v]){
                        if(state[v]==0){
                            stack[stack_size] = v;
                            parent[stack_size] = u;
                            stack_size++;
                        }
                    }
                }
                else{
                    stack_size--;
                    if(state[u]==1){
                        state[u]=2; // visited
                        // Compute DP
                        dp1[u] =1;
                        dp0[u] =0;
                        for(int v = head[u]; v !=0; v = next[v]){
                            dp1[u] += dp0[v];
                            if(dp0[v] > dp1[v]){
                                dp0[u] += dp0[v];
                            }
                            else{
                                dp0[u] += dp1[v];
                            }
                        }
                        // Update result
                        if(dp0[u] > dp1[u]){
                            result += dp0[u];
                        }
                        else{
                            result += dp1[u];
                        }
                    }
                }
            }
        }
    }
    
    printf("%lld\n", result);
    
    // Free memory
    free(a);
    free(head);
    free(next);
    free(state);
    free(dp0);
    free(dp1);
    
    return 0;
}