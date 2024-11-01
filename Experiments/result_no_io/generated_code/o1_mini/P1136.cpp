#include <stdio.h>
#include <string.h>

int min(int a, int b) {
    return a < b ? a : b;
}

int main(){
    int N, K;
    scanf("%d %d", &N, &K);
    char s[501];
    scanf("%s", s);
    
    int j_count = 0, z_count = 0, initial_jz = 0;
    for(int i=0; i<N; i++){
        if(s[i] == 'j') j_count++;
        if(s[i] == 'z') z_count++;
        if(i < N-1 && s[i] == 'j' && s[i+1] == 'z') initial_jz++;
    }
    
    int min_jz = min(j_count, z_count);
    int additional_jz = 0;
    if(initial_jz < min_jz){
        additional_jz = min(K, min_jz - initial_jz);
    }
    int result = initial_jz + additional_jz;
    if(result > min_jz) result = min_jz;
    
    printf("%d\n", result);
    return 0;
}