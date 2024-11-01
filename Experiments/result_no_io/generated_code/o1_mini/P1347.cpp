#include <stdio.h>
#include <string.h>

#define MAX 26

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    int adj[MAX][MAX];
    memset(adj, 0, sizeof(adj));
    int in_degree[MAX];
    memset(in_degree, 0, sizeof(in_degree));
    
    int determined = 0;
    int inconsistent = 0;
    char result[MAX+1];
    
    for(int x=1; x<=m; x++){
        char a, op, b;
        scanf(" %c %c %c", &a, &op, &b);
        int u = a - 'A';
        int v = b - 'A';
        if(!adj[u][v]){
            adj[u][v] = 1;
            in_degree[v]++;
        }
        
        // Copy in_degree and adj for processing
        int tmp_in_degree[MAX];
        memcpy(tmp_in_degree, in_degree, sizeof(tmp_in_degree));
        
        // Kahn's algorithm
        char temp_result[MAX+1];
        int count = 0;
        int unique = 1;
        int processed[MAX];
        memset(processed, 0, sizeof(processed));
        
        while(count < n){
            int zero = -1;
            int multiple = 0;
            for(int i=0;i<n;i++) if(!processed[i] && tmp_in_degree[i]==0){
                if(zero == -1) zero = i;
                else { multiple = 1; break;}
            }
            if(zero == -1){
                inconsistent = 1;
                break;
            }
            if(multiple){
                unique = 0;
                break;
            }
            processed[zero] = 1;
            temp_result[count++] = 'A' + zero;
            for(int j=0;j<n;j++) if(adj[zero][j]){
                tmp_in_degree[j]--;
            }
        }
        
        if(inconsistent){
            printf("Inconsistency found after %d relations.\n", x);
            return 0;
        }
        if(unique && count == n){
            temp_result[count] = '\0';
            printf("Sorted sequence determined after %d relations: %s.\n", x, temp_result);
            return 0;
        }
    }
    printf("Sorted sequence cannot be determined.\n");
    return 0;
}