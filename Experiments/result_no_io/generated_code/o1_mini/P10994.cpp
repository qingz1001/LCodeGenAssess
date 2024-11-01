#include <stdio.h>
#include <string.h>

int main(){
    int a, b;
    scanf("%d %d", &a, &b);
    char s[100005];
    scanf("%s", s);
    int cnt_S=0, cnt_T=0;
    int n = strlen(s);
    for(int i=0;i<n;i++){
        if(s[i]=='S') cnt_S++;
        else if(s[i]=='T') cnt_T++;
    }
    if(a + b > n){
        printf("-1");
        return 0;
    }
    int mod1 = a > cnt_S ? a - cnt_S : 0;
    int mod2 = b > cnt_T ? b - cnt_T : 0;
    int ans = mod1 > mod2 ? mod1 : mod2;
    printf("%d", ans);
}