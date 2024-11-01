#include <stdio.h>
#include <stdlib.h>

int main(){
    int N;
    scanf("%d", &N);
    unsigned int* a = (unsigned int*)malloc(sizeof(unsigned int) * N);
    int* distance = (int*)malloc(sizeof(int) * N);
    for(int i = 0; i < N; i++){
        scanf("%u", &a[i]);
        if(a[i] == 0){
            distance[i] = 0;
        }
        else{
            distance[i] = -1;
        }
    }
    int* queue = (int*)malloc(sizeof(int) * N);
    int head = 0, tail = 0;
    for(int i = 0; i < N; i++){
        if(a[i] == 0){
            queue[tail++] = i;
        }
    }
    while(head < tail){
        int u = queue[head++];
        if(u > 0 && distance[u-1] == -1){
            distance[u-1] = distance[u] + 1;
            queue[tail++] = u-1;
        }
        if(u < N-1 && distance[u+1] == -1){
            distance[u+1] = distance[u] + 1;
            queue[tail++] = u+1;
        }
    }
    unsigned long long p1 = 0, p2 = 0;
    for(int i = 0; i < N; i++){
        if(a[i] > 0){
            if(distance[i] % 2 == 1){
                p1 += a[i];
            }
            else{
                p2 += a[i];
            }
        }
    }
    printf("%llu %llu\n", p1, p2);
    free(a);
    free(distance);
    free(queue);
    return 0;
}