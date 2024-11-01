#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 1001

int adj[MAX][MAX];
int adj_size[MAX];
int within2[MAX][MAX];
int within2_size[MAX];
int covered[MAX];
int n;

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        adj_size[i]=0;
        within2_size[i]=0;
    }
    for(int i=2;i<=n;i++){
        int a;
        scanf("%d",&a);
        adj[i][adj_size[i]++] = a;
        adj[a][adj_size[a]++] = i;
    }
    // Precompute nodes within distance 2
    for(int i=1;i<=n;i++){
        int visited[MAX];
        memset(visited, 0, sizeof(visited));
        // distance 0
        within2[i][within2_size[i]++] = i;
        visited[i]=1;
        // distance 1
        for(int j=0;j<adj_size[i];j++){
            int child = adj[i][j];
            if(!visited[child]){
                within2[i][within2_size[i]++] = child;
                visited[child]=1;
            }
        }
        // distance 2
        for(int j=0;j<adj_size[i];j++){
            int child = adj[i][j];
            for(int k=0;k<adj_size[child];k++){
                int grand = adj[child][k];
                if(!visited[grand]){
                    within2[i][within2_size[i]++] = grand;
                    visited[grand]=1;
                }
            }
        }
    }
    memset(covered, 0, sizeof(covered));
    int count=0;
    while(1){
        int max_cover = -1;
        int best = -1;
        for(int i=1;i<=n;i++){
            if(within2_size[i]==0) continue;
            int cnt=0;
            for(int j=0;j<within2_size[i];j++) if(!covered[within2[i][j]]) cnt++;
            if(cnt > max_cover){
                max_cover = cnt;
                best = i;
            }
        }
        if(max_cover <=0) break;
        count++;
        for(int j=0;j<within2_size[best];j++) covered[within2[best][j]]=1;
    }
    printf("%d",count);
}