#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    int *C = (int*)malloc(sizeof(int)*N);
    for(int i=0;i<N;i++) scanf("%d", &C[i]);
    // Placeholder for actual logic
    // For demonstration, output 0 for each color
    for(int c=1;c<=M;c++) printf("0\n");
    free(C);
    return 0;
}