#include <stdio.h>

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    // Calculate total rectangles
    long long total_rectangles = ((long long)(N+1)*N/2) * ((long long)(M+1)*M/2);
    // Calculate squares
    int k_max = N < M ? N : M;
    long long squares = 0;
    for(int k=1; k<=k_max; k++){
        squares += (N - k +1)*(M - k +1);
    }
    // Rectangles excluding squares
    long long rectangles = total_rectangles - squares;
    printf("%lld %lld\n", squares, rectangles);
    return 0;
}