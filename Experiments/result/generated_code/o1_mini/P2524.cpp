#include <stdio.h>
#include <string.h>

int main(){
    int N;
    scanf("%d", &N);
    char str[10];
    scanf("%s", str);
    int perm[10];
    for(int i=0;i<N;i++){
        perm[i] = str[i]-'0';
    }
    long long fact[10];
    fact[0]=1;
    for(int i=1;i<=N;i++){
        fact[i]=fact[i-1]*i;
    }
    int used[10];
    memset(used, 0, sizeof(used));
    long long rank=1;
    for(int i=0;i<N;i++){
        int count=0;
        for(int d=1; d<perm[i]; d++){
            if(!used[d]) count++;
        }
        rank += count * fact[N-1-i];
        used[perm[i]]=1;
    }
    printf("%lld\n", rank);
    return 0;
}