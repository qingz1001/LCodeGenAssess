#include <stdio.h>
#include <stdlib.h>

long long max_ll(long long a, long long b) {
    return a > b ? a : b;
}

int main(){
    long long n, m, p, q;
    scanf("%lld %lld %lld %lld", &n, &m, &p, &q);
    
    long long *d = (long long*)malloc(sizeof(long long)*m);
    long long *c = (long long*)malloc(sizeof(long long)*m);
    for(long long i=0;i<m;i++) scanf("%lld %lld", &d[i], &c[i]);
    
    long long *s = NULL;
    if(p >0){
        s = (long long*)malloc(sizeof(long long)*p);
        for(long long i=0;i<p;i++) scanf("%lld", &s[i]);
    }
    
    long long *t = NULL;
    if(q >0){
        t = (long long*)malloc(sizeof(long long)*q);
        for(long long i=0;i<q;i++) scanf("%lld", &t[i]);
    }
    
    long long a = n - p - q;
    if(a >0){
        long long W = (m + n -1)/n;
        printf("%lld\n", W);
    }
    else{
        if(p ==0 && q ==0){
            if(m ==0) printf("0\n");
            else printf("-1\n");
        }
        else{
            long long s_min = 0;
            if(p >0){
                s_min = s[0];
                for(long long i=1;i<p;i++) if(s[i] < s_min) s_min = s[i];
            }
            long long t_max = 0;
            if(q >0){
                t_max = t[0];
                for(long long i=1;i<q;i++) if(t[i] > t_max) t_max = t[i];
            }
            long long Sp=0, Sq=0, Sb=0;
            for(long long i=0;i<m;i++){
                int can_p=0, can_q=0;
                if(p >0 && d[i] >= s_min) can_p=1;
                if(q >0 && c[i] <= t_max) can_q=1;
                if(can_p) Sp++;
                if(can_q) Sq++;
                if(can_p && can_q) Sb++;
            }
            if(p >0 && q >0){
                long long S_p_only = Sp - Sb;
                long long S_q_only = Sq - Sb;
                if(S_p_only + S_q_only + Sb !=m){
                    printf("-1\n");
                }
                else{
                    long long W1 = (S_p_only + p -1)/p;
                    long long W2 = (S_q_only + q -1)/q;
                    long long W3 = (m + p + q -1)/(p + q);
                    long long W = W1;
                    W = max_ll(W, W2);
                    W = max_ll(W, W3);
                    printf("%lld\n", W);
                }
            }
            else if(p >0){
                if(Sp ==m){
                    long long W = (m + p -1)/p;
                    printf("%lld\n", W);
                }
                else{
                    printf("-1\n");
                }
            }
            else{ // q >0
                if(Sq ==m){
                    long long W = (m + q -1)/q;
                    printf("%lld\n", W);
                }
                else{
                    printf("-1\n");
                }
            }
        }
    }
    free(d);
    free(c);
    if(p >0) free(s);
    if(q >0) free(t);
    return 0;
}