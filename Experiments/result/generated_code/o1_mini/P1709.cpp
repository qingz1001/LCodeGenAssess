#include <stdio.h>
#include <stdlib.h>

int least_rotation(char *s, int n){
    int i=0, j=1, k=0;
    while(i < n && j < n && k < n){
        char a = s[(i+k)%n];
        char b = s[(j+k)%n];
        if(a == b){
            k++;
        }
        else{
            if(a > b){
                i = i + k +1;
            }
            else{
                j = j + k +1;
            }
            if(i == j){
                i++;
            }
            k=0;
        }
    }
    if(i < n){
        return i;
    }
    else{
        return j;
    }
}

int main(){
    int N;
    if(scanf("%d", &N)!=1){
        return 1;
    }
    char *s = (char*)malloc(N * sizeof(char));
    if(!s){
        return 1;
    }
    int count=0;
    while(count < N){
        int c = getchar();
        if(c == EOF){
            break;
        }
        if(c != '\n'){
            s[count++] = (char)c;
        }
    }
    int pos = least_rotation(s, N);
    printf("%d\n", pos);
    free(s);
    return 0;
}