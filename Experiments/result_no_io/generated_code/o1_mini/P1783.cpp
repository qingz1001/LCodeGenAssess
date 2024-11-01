#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Tower;

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    Tower towers[M];
    for(int i=0;i<M;i++) scanf("%lf %lf", &towers[i].x, &towers[i].y);
    
    // Binary search
    double low=0.0, high=200000.0, mid, eps=1e-4;
    // Union-Find structures
    int parent[M];
    int connected_left[M];
    int connected_right[M];
    
    while(high - low > eps){
        mid = (low + high)/2.0;
        // Initialize
        for(int i=0;i<M;i++){
            parent[i]=i;
            connected_left[i] = (towers[i].x <= mid) ? 1 : 0;
            connected_right[i] = (N - towers[i].x <= mid) ? 1 : 0;
        }
        // Find
        double twoR = 2.0 * mid;
        double twoR_sq = twoR * twoR;
        // Union
        for(int i=0;i<M;i++) {
            for(int j=i+1;j<M;j++) {
                double dx = towers[i].x - towers[j].x;
                double dy = towers[i].y - towers[j].y;
                if(dx*dx + dy*dy <= twoR_sq){
                    // Union i and j
                    int pi = i, pj = j;
                    // Find roots
                    while(parent[pi]!=pi) pi = parent[pi];
                    while(parent[pj]!=pj) pj = parent[pj];
                    if(pi != pj){
                        parent[pj] = pi;
                        connected_left[pi] |= connected_left[pj];
                        connected_right[pi] |= connected_right[pj];
                    }
                }
            }
        }
        // Check
        int blocked=0;
        for(int i=0;i<M;i++){
            int pi = i;
            while(parent[pi]!=pi) pi = parent[pi];
            if(connected_left[pi] && connected_right[pi]){
                blocked=1;
                break;
            }
        }
        if(blocked) {
            high = mid;
        }
        else{
            low = mid;
        }
    }
    printf("%.2lf\n", high);
}