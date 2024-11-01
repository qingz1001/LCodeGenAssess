#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    int grid[200][200];
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    ll max_area = 0;
    ll col_sum[200];
    ll prefix[201];
    int stack_indices[201];
    for(int top=0; top<N; top++) {
        for(int j=0; j<M; j++) {
            col_sum[j] = 0;
        }
        for(int bottom=top; bottom<N; bottom++) {
            for(int j=0; j<M; j++) {
                col_sum[j] += grid[bottom][j];
            }
            prefix[0] = 0;
            for(int j=0; j<M; j++) {
                prefix[j+1] = prefix[j] + col_sum[j];
            }
            int stack_size = 0;
            for(int i=0; i<=M; i++) {
                if(stack_size == 0 || prefix[i] < prefix[stack_indices[stack_size-1]]) {
                    stack_indices[stack_size++] = i;
                }
            }
            for(int j=M; j>=0; j--) {
                while(stack_size > 0 && prefix[j] > prefix[stack_indices[stack_size-1]]) {
                    int i = stack_indices[--stack_size];
                    ll width = j - i;
                    ll height = bottom - top + 1;
                    ll area = width * height;
                    if(area > max_area){
                        max_area = area;
                    }
                }
            }
        }
    }
    printf("%lld\n", max_area);
    return 0;
}