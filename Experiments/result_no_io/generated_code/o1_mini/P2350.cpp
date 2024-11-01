#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PRIME 100005

unsigned int spf[MAX_PRIME];

void sieve() {
    for(int i=0;i<MAX_PRIME;i++) spf[i]=i;
    for(int i=2;i*i<MAX_PRIME;i++) {
        if(spf[i]==i){
            for(int j=i*i;j<MAX_PRIME;j+=i){
                if(spf[j]==j) spf[j]=i;
            }
        }
    }
}

typedef struct {
    int p;
    long long q;
} factor;

int factorize(int num, int *factors, int *counts){
    int cnt=0;
    if(num==1) return 0;
    while(num >1){
        int prime = spf[num];
        int power=0;
        while(num%prime ==0){
            power++;
            num /= prime;
        }
        factors[cnt] = prime;
        counts[cnt] = power;
        cnt++;
    }
    return cnt;
}

int main(){
    sieve();
    int test;
    scanf("%d",&test);
    while(test--){
        int m;
        scanf("%d",&m);
        factor current_factors[4000000];
        int current_cnt =0;
        for(int i=0;i<m;i++){
            int pi;
            long long qi;
            scanf("%d %lld", &pi, &qi);
            current_factors[current_cnt].p = pi;
            current_factors[current_cnt].q = qi;
            current_cnt++;
        }
        int x=0;
        while(current_cnt >0){
            // Check if N ==1
            if(current_cnt==0){
                break;
            }
            // Apply phi
            factor next_factors[4000000];
            int next_cnt=0;
            for(int i=0;i<current_cnt;i++){
                int p = current_factors[i].p;
                long long q = current_factors[i].q;
                if(q >=2){
                    // Add p^{q-1}
                    int found = -1;
                    for(int j=0;j<next_cnt;j++) if(next_factors[j].p == p){ found = j; break;}
                    if(found != -1){
                        next_factors[found].q += (q-1);
                    }
                    else{
                        next_factors[next_cnt].p = p;
                        next_factors[next_cnt].q = q-1;
                        next_cnt++;
                    }
                }
                // Factorize p-1
                int pfactors[20];
                int pcounts[20];
                int fc = factorize(p-1, pfactors, pcounts);
                for(int j=0;j<fc;j++){
                    int prime = pfactors[j];
                    int power = pcounts[j];
                    int found = -1;
                    for(int k=0;k<next_cnt;k++) if(next_factors[k].p == prime){ found = k; break;}
                    if(found != -1){
                        next_factors[found].q += power;
                    }
                    else{
                        next_factors[next_cnt].p = prime;
                        next_factors[next_cnt].q = power;
                        next_cnt++;
                    }
                }
            }
            // Remove factors with q=0
            current_cnt = next_cnt;
            memcpy(current_factors, next_factors, sizeof(factor)*current_cnt);
            x++;
        }
        printf("%d\n",x);
    }
}