#include <stdio.h>

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    int min = N < M ? N : M;
    long long total_rect = ((long long)N * (N + 1) / 2) * ((long long)M * (M + 1) / 2);
    long long squares = 0;
    for(int k=1; k<=min; k++){
        squares += (N - k +1) * (M - k +1);
    }
    long long rectangles = total_rect - squares;
    printf("%lld %lld\n", squares, rectangles);
    return 0;
}