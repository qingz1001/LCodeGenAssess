#include <stdio.h>
#include <string.h>

char res_buffer[2048];
int res_pos = 0;

void process(const char *s, int start, int len, char *res, int *pos) {
    int has0 = 0, has1 = 0;
    for(int i = start; i < start + len; i++) {
        if(s[i] == '0') has0 = 1;
        else if(s[i] == '1') has1 = 1;
        if(has0 && has1) break;
    }
    
    if(len > 1){
        int mid = len / 2;
        process(s, start, mid, res, pos);
        process(s, start + mid, mid, res, pos);
    }
    
    if(has0 && !has1){
        res[*pos] = 'B';
    }
    else if(!has0 && has1){
        res[*pos] = 'I';
    }
    else{
        res[*pos] = 'F';
    }
    (*pos)++;
}

int main(){
    int N;
    scanf("%d", &N);
    int length = 1;
    for(int i = 0; i < N; i++) length *= 2;
    char S[1025];
    scanf("%s", S);
    process(S, 0, length, res_buffer, &res_pos);
    res_buffer[res_pos] = '\0';
    printf("%s\n", res_buffer);
    return 0;
}