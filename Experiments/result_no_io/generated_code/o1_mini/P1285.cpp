#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100

int mutual[MAXN+1][MAXN+1];
int n;
int color[MAXN+1];
int complement[MAXN+1][MAXN+1];
int visited[MAXN+1];
int queue[MAXN+1];
int head, tail;

typedef struct {
    int size0;
    int size1;
} Component;

int main(){
    scanf("%d", &n);
    for(int i=1;i<=n;i++){
        int x;
        while(scanf("%d", &x) && x !=0){
            mutual[i][x] =1;
        }
    }
    // Build mutual adjacency
    // Now build complement adjacency
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i !=j){
                if(!(mutual[i][j] && mutual[j][i])){
                    complement[i][j]=1;
                }
                else{
                    complement[i][j]=0;
                }
            }
            else{
                complement[i][j]=0;
            }
        }
    }
    // Bipartition complement graph
    memset(color, -1, sizeof(color));
    Component components[MAXN];
    int comp_cnt=0;
    int possible=1;
    for(int i=1;i<=n && possible;i++){
        if(color[i]==-1){
            // BFS
            head=0;
            tail=0;
            queue[tail++]=i;
            color[i]=0;
            int cnt0=1, cnt1=0;
            while(head < tail && possible){
                int u = queue[head++];
                for(int v=1; v<=n && possible; v++){
                    if(complement[u][v]){
                        if(color[v]==-1){
                            color[v]=1 - color[u];
                            if(color[v]==0) cnt0++;
                            else cnt1++;
                            queue[tail++]=v;
                        }
                        else{
                            if(color[v]==color[u]){
                                possible=0;
                            }
                        }
                    }
                }
            }
            if(possible){
                components[comp_cnt].size0 = cnt0;
                components[comp_cnt].size1 = cnt1;
                comp_cnt++;
            }
        }
    }
    if(!possible){
        printf("No solution\n");
        return 0;
    }
    // DP to find possible group sizes
    int dp[n+1];
    memset(dp, -1, sizeof(dp));
    dp[0]=0;
    for(int i=0;i<comp_cnt;i++){
        for(int j=n; j>=0; j--){
            if(dp[j]!=-1){
                // Take size0
                if(j + components[i].size0 <=n){
                    if(dp[j + components[i].size0]==-1){
                        dp[j + components[i].size0]=j;
                    }
                }
                // Take size1
                if(j + components[i].size1 <=n){
                    if(dp[j + components[i].size1]==-1){
                        dp[j + components[i].size1]=j;
                    }
                }
            }
        }
    }
    // Find the closest to n/2
    int target = -1;
    int min_diff = n;
    for(int s=0;s<=n;s++){
        if(dp[s]!=-1){
            int diff = abs(s - (n - s));
            if(diff < min_diff){
                min_diff = diff;
                target = s;
            }
        }
    }
    if(target == -1){
        printf("No solution\n");
        return 0;
    }
    // Reconstruct the assignment
    int assign[comp_cnt];
    memset(assign, -1, sizeof(assign));
    int s = target;
    for(int i=comp_cnt-1;i>=0;i--){
        if(s - components[i].size0 >=0 && dp[s - components[i].size0] != -1){
            assign[i]=0;
            s -= components[i].size0;
        }
        else{
            assign[i]=1;
            s -= components[i].size1;
        }
    }
    // Assign groups
    int group1[MAXN], g1=0, group2[MAXN], g2=0;
    for(int i=0;i<comp_cnt;i++){
        int choice = assign[i];
        for(int u=1; u<=n; u++){
            // Find which component u belongs to
            // Recompute color during assignment
            // It's easier to assign based on color and component choice
        }
    }
    // To assign members, iterate components again
    // Re-run BFS to assign group
    memset(color, -1, sizeof(color));
    int group_assignment[MAXN+1]; // 0 or 1
    int comp_index =0;
    for(int i=1;i<=n;i++){
        if(color[i]==-1){
            // BFS
            head=0;
            tail=0;
            queue[tail++]=i;
            color[i]=0;
            while(head < tail){
                int u = queue[head++];
                for(int v=1; v<=n; v++){
                    if(complement[u][v]){
                        if(color[v]==-1){
                            color[v]=1 - color[u];
                            queue[tail++]=v;
                        }
                    }
                }
            }
            // Assign based on component assignment
            if(assign[comp_index]==0){
                for(int u=1; u<=n; u++) {
                    if(color[u]!=-1 && mutual[i][u] && mutual[u][i]){
                        if(color[u]==0){
                            group_assignment[u]=0;
                        }
                        else{
                            group_assignment[u]=1;
                        }
                    }
                }
            }
            else{
                for(int u=1; u<=n; u++) {
                    if(color[u]!=-1 && mutual[i][u] && mutual[u][i]){
                        if(color[u]==0){
                            group_assignment[u]=1;
                        }
                        else{
                            group_assignment[u]=0;
                        }
                    }
                }
            }
            comp_index++;
        }
    }
    // Now collect groups
    for(int u=1; u<=n; u++){
        if(group_assignment[u]==0){
            group1[g1++]=u;
        }
        else{
            group2[g2++]=u;
        }
    }
    // If any group is empty, invalid
    if(g1 ==0 || g2 ==0){
        printf("No solution\n");
        return 0;
    }
    // Sort groups
    for(int i=0;i<g1-1;i++) {
        for(int j=i+1;j<g1;j++) {
            if(group1[i] > group1[j]){
                int tmp = group1[i]; group1[i] = group1[j]; group1[j] = tmp;
            }
        }
    }
    for(int i=0;i<g2-1;i++) {
        for(int j=i+1;j<g2;j++) {
            if(group2[i] > group2[j]){
                int tmp = group2[i]; group2[i] = group2[j]; group2[j] = tmp;
            }
        }
    }
    // Check if both groups are cliques
    int valid =1;
    // For group1
    for(int i=0;i<g1 && valid;i++) {
        for(int j=0;j<g1 && valid;j++) {
            if(i !=j && !(mutual[group1[i]][group1[j]] && mutual[group1[j]][group1[i]])){
                valid =0;
            }
        }
    }
    // For group2
    for(int i=0;i<g2 && valid;i++) {
        for(int j=0;j<g2 && valid;j++) {
            if(i !=j && !(mutual[group2[i]][group2[j]] && mutual[group2[j]][group2[i]])){
                valid =0;
            }
        }
    }
    if(!valid){
        printf("No solution\n");
        return 0;
    }
    // Print group1
    printf("%d", g1);
    for(int i=0;i<g1;i++) printf(" %d", group1[i]);
    printf("\n");
    // Print group2
    printf("%d", g2);
    for(int i=0;i<g2;i++) printf(" %d", group2[i]);
    printf("\n");
    return 0;
}