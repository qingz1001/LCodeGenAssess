#include<stdio.h>
#include<stdlib.h>
#define MOD 1000000007
typedef long long ll;

ll power_pow(ll a, ll b){
    ll res=1;a %= MOD;
    while(b>0){
        if(b&1) res=res*a%MOD;
        a=a*a%MOD; b>>=1;
    }
    return res;
}

int main(){
    int N,M;
    scanf("%d %d",&N,&M);
    long long sum=0;
    for(int i=0;i<M;i++){
        int c; scanf("%d",&c);
        sum += (c+1);
    }
    if(sum > N){
        printf("0\n");
        return 0;
    }
    int rem = N - sum;
    int max_n = rem + M -1;
    int size = max_n +1;
    ll *fac = (ll*)malloc(sizeof(ll)*(size));
    ll *inv = (ll*)malloc(sizeof(ll)*(size));
    fac[0]=1;
    for(int i=1;i<size;i++) fac[i]=fac[i-1]*i%MOD;
    inv[size-1]=power_pow(fac[size-1], MOD-2);
    for(int i=size-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%MOD;
    ll res = fac[max_n]*inv[M-1]%MOD * inv[rem]%MOD;
    printf("%lld\n", res);
    free(fac); free(inv);
}