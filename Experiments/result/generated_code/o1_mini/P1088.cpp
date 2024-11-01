#include <stdio.h>

int main(){
    int N, M;
    scanf("%d", &N);
    scanf("%d", &M);
    int P[N];
    for(int i=0;i<N;i++) scanf("%d", &P[i]);
    for(int m=0; m<M; m++){
        int i = N-2;
        while(i >=0 && P[i] >= P[i+1]) i--;
        // According to problem statement, i >=0
        int j = N-1;
        while(j >=0 && P[j] <= P[i]) j--;
        // Swap P[i] and P[j]
        int temp = P[i];
        P[i] = P[j];
        P[j] = temp;
        // Reverse from i+1 to N-1
        int start = i+1, end = N-1;
        while(start < end){
            temp = P[start];
            P[start] = P[end];
            P[end] = temp;
            start++;
            end--;
        }
    }
    for(int i=0;i<N;i++){
        if(i !=0) printf(" ");
        printf("%d", P[i]);
    }
    printf("\n");
    return 0;
}