#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long long ll;

#define MAX_N 1000001

ll a[MAX_N];
ll sum_y[MAX_N];
int SPF[MAX_N];

void sieve() {
    for(int i=0;i<MAX_N;i++) SPF[i]=i;
    for(int i=2;i*i < MAX_N;i++) {
        if(SPF[i]==i){
            for(int j=i*i;j<MAX_N;j+=i){
                if(SPF[j]==j) SPF[j]=i;
            }
        }
    }
}

int divisors[100];
int div_cnt;

void get_divisors(int j) {
    div_cnt = 0;
    if(j ==0) return;
    int factors[20];
    int exponents[20];
    int num = 0;
    while(j >1){
        int p = SPF[j];
        int cnt =0;
        while(j%p==0){
            cnt++;
            j /=p;
        }
        factors[num] = p;
        exponents[num] = cnt;
        num++;
    }
    divisors[0]=1;
    div_cnt=1;
    for(int i=0;i<num;i++){
        int current_size = div_cnt;
        ll p_power=1;
        for(int e=0;e<exponents[i];e++){
            p_power *= factors[i];
            for(int k=0;k<current_size;k++) {
                if(div_cnt >= 100) break;
                divisors[div_cnt++] = divisors[k] * p_power;
            }
        }
    }
}

int main(){
    sieve();
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) scanf("%lld", &a[i]);
    for(int i=0;i<m;i++){
        int type;
        scanf("%d", &type);
        if(type ==1){
            int x;
            ll y;
            scanf("%d %lld", &x, &y);
            if(x < MAX_N) sum_y[x] += y;
        }
        else{
            int j;
            scanf("%d", &j);
            if(j <1 || j >n){
                printf("0\n");
                continue;
            }
            ll res = a[j];
            get_divisors(j);
            for(int d=0; d<div_cnt; d++) {
                int x = divisors[d];
                if(x < MAX_N) res += sum_y[x];
            }
            printf("%lld\n", res);
        }
    }
    return 0;
}