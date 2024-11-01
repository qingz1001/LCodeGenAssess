#include <stdio.h>
#include <string.h>

int main(){
    int N;
    scanf("%d", &N);
    char s[20];
    scanf("%s", s);
    int perm[N];
    for(int i=0;i<N;i++) perm[i]=s[i]-'0';
    int fact[10];
    fact[0]=1;
    for(int i=1;i<=N;i++) fact[i]=fact[i-1]*i;
    int used[10]={0};
    int rank=1;
    for(int i=0;i<N;i++){
        int cnt=0;
        for(int j=1;j<perm[i];j++) if(!used[j]) cnt++;
        rank += cnt * fact[N-i-1];
        used[perm[i]]=1;
    }
    printf("%d", rank);
}