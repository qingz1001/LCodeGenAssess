#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int p;
    int a;
} Factor;

int factorize(int num, Factor *factors) {
    int count = 0;
    if (num < 1) return 0;
    for(int i=2;i*i<=num;i++){
        if(num%i ==0){
            int cnt=0;
            while(num%i ==0){
                cnt++;
                num /=i;
            }
            factors[count].p = i;
            factors[count].a = cnt;
            count++;
        }
    }
    if(num >1){
        factors[count].p = num;
        factors[count].a =1;
        count++;
    }
    return count;
}

int main(){
    int N;
    if(scanf("%d", &N)!=1) return 0;
    long long m1, m2;
    if(scanf("%lld %lld", &m1, &m2)!=2) return 0;
    Factor factors[20];
    int nf = factorize(m1, factors);
    int S;
    long long min_t = -1;
    for(int i=0;i<N;i++){
        if(scanf("%d", &S)!=1) return 0;
        int valid =1;
        long long t_i =0;
        int temp_S = S;
        for(int j=0;j<nf;j++){
            int cnt=0;
            while(temp_S % factors[j].p ==0){
                cnt++;
                temp_S /= factors[j].p;
            }
            if(cnt ==0){
                valid =0;
                break;
            }
            long long t_req = (factors[j].a * m2 + cnt -1) / cnt;
            if(t_req > t_i) t_i = t_req;
        }
        if(valid){
            if(min_t == -1 || t_i < min_t){
                min_t = t_i;
            }
        }
    }
    printf("%lld\n", min_t);
    return 0;
}