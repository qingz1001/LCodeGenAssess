#include <stdio.h>
#include <stdlib.h>

#define MAX 200

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    long long a[MAX][MAX];
    for(int i=0;i<N;i++) {
        for(int j=0; j<M; j++) {
            scanf("%lld", &a[i][j]);
        }
    }
    long long sum[MAX];
    long long prefix[MAX+1];
    long long max_area = 0;
    for(int top=0; top<N; top++) {
        for(int j=0; j<M; j++) sum[j] = 0;
        for(int bottom=top; bottom<N; bottom++) {
            for(int j=0; j<M; j++) {
                sum[j] += a[bottom][j];
            }
            prefix[0] = 0;
            for(int j=0; j<M; j++) {
                prefix[j+1] = prefix[j] + sum[j];
            }
            long long min_prefix = prefix[0];
            int l_min = 0;
            for(int j=1; j<=M; j++) {
                if(prefix[j] > min_prefix){
                    long long width = j - l_min;
                    long long height = bottom - top +1;
                    long long area = width * height;
                    if(area > max_area){
                        max_area = area;
                    }
                }
                if(prefix[j] < min_prefix){
                    min_prefix = prefix[j];
                    l_min = j;
                }
            }
        }
    }
    printf("%lld", max_area);
    return 0;
}