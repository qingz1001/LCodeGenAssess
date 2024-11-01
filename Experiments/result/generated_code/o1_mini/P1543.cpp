#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    scanf("%d", &n);
    int *parent = (int*)malloc((n+1)*sizeof(int));
    int *in_degree = (int*)calloc(n+1, sizeof(int));
    for(int i=1;i<=n;i++){
        scanf("%d", &parent[i]);
        in_degree[parent[i]]++;
    }
    // Count nodes with in_degree >=1
    long long cnt1=0;
    for(int i=1;i<=n;i++) if(in_degree[i]>=1) cnt1++;
    // Count cycles
    char *color = (char*)calloc(n+1, sizeof(char));
    long long cnt_cycles=0;
    for(int i=1;i<=n;i++){
        if(color[i]==0){
            int current = i;
            while(1){
                if(color[current]==1){
                    cnt_cycles++;
                    break;
                }
                if(color[current]==2){
                    break;
                }
                color[current]=1;
                current = parent[current];
            }
            // Mark all visited nodes
            current = i;
            while(color[current]==1){
                color[current]=2;
                current = parent[current];
                if(current == i) break;
            }
        }
    }
    printf("%lld", cnt1 - cnt_cycles);
    free(parent);
    free(in_degree);
    free(color);
    return 0;
}