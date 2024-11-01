#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long long ll;

int main(){
    int M, N;
    scanf("%d %d", &M, &N);
    int total = M * N;
    // Allocate elevation array
    int *elev = (int*)malloc(sizeof(int)*total);
    for(int i=0;i<total;i++) scanf("%d", &elev[i]);
    // Allocate signpost array
    int *is_sign = (int*)malloc(sizeof(int)*total);
    int sign_count=0;
    for(int i=0;i<total;i++) {
        scanf("%d", &is_sign[i]);
        if(is_sign[i]) sign_count++;
    }
    // If no or one signpost, D=0
    if(sign_count <=1 ){
        printf("0");
        free(elev);
        free(is_sign);
        return 0;
    }
    // Collect signpost indices
    int *signs = (int*)malloc(sizeof(int)*sign_count);
    int idx=0;
    for(int i=0;i<total;i++) if(is_sign[i]) signs[idx++]=i;
    // Initialize BFS variables
    int *vis = (int*)malloc(sizeof(int)*total);
    int timestamp = 1;
    // Binary search
    int left=0, right=1000000000, mid, res=right;
    // Directions: up, down, left, right
    int dirs[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };
    // Queue for BFS
    int *queue = (int*)malloc(sizeof(int)*total);
    while(left <= right){
        mid = left + (right - left)/2;
        // BFS from first signpost
        int head=0, tail=0;
        queue[tail++] = signs[0];
        vis[signs[0]] = timestamp;
        while(head < tail){
            int current = queue[head++];
            int r = current / N;
            int c = current % N;
            for(int d=0; d<4; d++){
                int nr = r + dirs[d][0];
                int nc = c + dirs[d][1];
                if(nr >=0 && nr < M && nc >=0 && nc < N){
                    int neighbor = nr * N + nc;
                    if(vis[neighbor] != timestamp && abs(elev[current] - elev[neighbor]) <= mid){
                        vis[neighbor] = timestamp;
                        queue[tail++] = neighbor;
                    }
                }
            }
        }
        // Check if all signposts are visited
        int all = 1;
        for(int i=1;i<sign_count;i++) {
            if(vis[signs[i]] != timestamp){
                all = 0;
                break;
            }
        }
        if(all){
            res = mid;
            right = mid -1;
        }
        else{
            left = mid +1;
        }
        timestamp++;
    }
    printf("%d", res);
    free(elev);
    free(is_sign);
    free(signs);
    free(vis);
    free(queue);
    return 0;
}