#include <stdio.h>
#include <string.h>

int main(){
    int N, K;
    scanf("%d %d", &N, &K);
    char S[501];
    scanf("%s", S);
    int initial_P = 0, J = 0, Z = 0;
    for(int i=0;i<N;i++){
        if(S[i] == 'j') J++;
        if(S[i] == 'z') Z++;
        if(i < N-1 && S[i] == 'j' && S[i+1] == 'z') initial_P++;
    }
    int min_JZ = (J < Z) ? J : Z;
    int max_P = initial_P + K;
    if(max_P > min_JZ) max_P = min_JZ;
    printf("%d\n", max_P);
    return 0;
}