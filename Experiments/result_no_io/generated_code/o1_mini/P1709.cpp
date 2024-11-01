#include <stdio.h>
#include <stdlib.h>

int main(){
    int N;
    if(scanf("%d", &N)!=1){
        return 1;
    }
    
    // Allocate memory for S and S duplicated
    char *S = (char*)malloc(2L * N * sizeof(char));
    if(!S){
        return 1;
    }
    
    // Read S, skipping newlines
    int idx =0;
    int c;
    while(idx < N && (c = getchar()) != EOF){
        if(c != '\n'){
            S[idx++] = (char)c;
        }
    }
    
    // Duplicate S to S+S
    for(int i=0; i<N; i++){
        S[N +i] = S[i];
    }
    
    // Booth's algorithm to find least rotation
    int i=0, j=1, k=0;
    while(i < N && j < N && k < N){
        char a = S[i +k];
        char b = S[j +k];
        if(a == b){
            k++;
        }
        else{
            if(a < b){
                j += k +1;
            }
            else{
                i += k +1;
            }
            if(i == j){
                i++;
            }
            k =0;
        }
    }
    
    int pos = (i < j) ? i : j;
    printf("%d\n", pos);
    
    free(S);
    return 0;
}