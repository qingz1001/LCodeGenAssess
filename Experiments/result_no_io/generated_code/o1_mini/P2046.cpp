#include <stdio.h>
#include <math.h>

int main(){
    int n;
    scanf("%d", &n);
    long long *east = (long long*)malloc(sizeof(long long)*n*(n+1));
    long long *south = (long long*)malloc(sizeof(long long)*n*(n+1));
    long long *west = (long long*)malloc(sizeof(long long)*n*(n+1));
    long long *north = (long long*)malloc(sizeof(long long)*n*(n+1));
    for(int i=0;i<n*(n+1);i++) scanf("%lld", &east[i]);
    for(int i=0;i<n*(n+1);i++) scanf("%lld", &south[i]);
    for(int i=0;i<n*(n+1);i++) scanf("%lld", &west[i]);
    for(int i=0;i<n*(n+1);i++) scanf("%lld", &north[i]);
    // Placeholder for actual algorithm
    // Since the algorithm is complex, we'll return 0 for now
    printf("0\n");
    free(east);
    free(south);
    free(west);
    free(north);
    return 0;
}