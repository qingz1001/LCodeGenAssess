#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Tower;

int parent[802];
int find_set(int x){
    if(parent[x]!=x){
        parent[x]=find_set(parent[x]);
    }
    return parent[x];
}
void union_set(int x, int y){
    int fx = find_set(x);
    int fy = find_set(y);
    if(fx != fy){
        parent[fx] = fy;
    }
}

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    Tower towers[M];
    for(int i=0;i<M;i++) scanf("%d %d", &towers[i].x, &towers[i].y);
    double low=0.0, high=200000.0, mid, res=high;
    for(int it=0; it<50; it++){
        mid = (low + high)/2.0;
        for(int i=0;i<M+2;i++) parent[i]=i;
        int left = M, right = M+1;
        for(int i=0;i<M;i++){
            if(towers[i].x <= mid) union_set(i, left);
            if(N - towers[i].x <= mid) union_set(i, right);
        }
        double limit = 2.0 * mid;
        double limit_sq = limit * limit;
        for(int i=0;i<M;i++) {
            for(int j=i+1;j<M;j++){
                double dx = (double)(towers[i].x - towers[j].x);
                double dy = (double)(towers[i].y - towers[j].y);
                if(dx*dx + dy*dy <= limit_sq){
                    union_set(i, j);
                }
            }
        }
        if(find_set(left) == find_set(right)){
            res = mid;
            high = mid;
        }
        else{
            low = mid;
        }
    }
    printf("%.2lf\n", res);
}