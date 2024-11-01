#include <stdio.h>
#include <string.h>

#define MAX_LEN 2048

char result[MAX_LEN];
int res_idx = 0;

char determine_type(char *S, int l, int r){
    int has0 = 0, has1 = 0;
    for(int i=l; i<r; i++){
        if(S[i] == '0') has0 = 1;
        else if(S[i] == '1') has1 = 1;
        if(has0 && has1) return 'F';
    }
    if(has0) return 'B';
    return 'I';
}

void build_post_order(char *S, int l, int r){
    if(l >= r) return;
    if(r - l == 1){
        result[res_idx++] = (S[l] == '0') ? 'B' : 'I';
        return;
    }
    int m = (l + r) / 2;
    build_post_order(S, l, m);
    build_post_order(S, m, r);
    char type = determine_type(S, l, r);
    result[res_idx++] = type;
}

int main(){
    int N;
    scanf("%d", &N);
    int length = 1 << N;
    char S[length + 1];
    scanf("%s", S);
    build_post_order(S, 0, length);
    result[res_idx] = '\0';
    printf("%s\n", result);
    return 0;
}