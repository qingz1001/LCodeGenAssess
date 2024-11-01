#include <stdio.h>
#include <string.h>

int main(){
    int a, b;
    scanf("%d %d", &a, &b);
    char s[100005];
    scanf("%s", s);
    int cnt_S = 0, cnt_T = 0;
    for(int i=0; s[i]; i++){
        if(s[i] == 'S') cnt_S++;
        else if(s[i] == 'T') cnt_T++;
    }
    int n = cnt_S + cnt_T;
    if(n < a + b){
        printf("-1\n");
        return 0;
    }
    int D1 = a - cnt_S;
    int D2 = b - cnt_T;
    int D = D1 > D2 ? D1 : D2;
    if(D <= 0){
        printf("0\n");
        return 0;
    }
    if(cnt_T >= D){
        printf("%d\n", D);
    }
    else{
        printf("-1\n");
    }
}