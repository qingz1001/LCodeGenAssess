#include <stdio.h>
#include <stdlib.h>

#define MAX_PRIME 100005
#define MAX_FACTORS 200000
#define MAX_TEMP 40000

typedef struct {
    int prime;
    long long exp;
} Factor;

// Comparator for qsort
int cmp_factors(const void *a, const void *b){
    Factor fa = *(Factor*)a;
    Factor fb = *(Factor*)b;
    if(fa.prime < fb.prime) return -1;
    if(fa.prime > fb.prime) return 1;
    return 0;
}

// Sieve of Eratosthenes to compute smallest prime factor
int SPF_arr[MAX_PRIME];
void sieve(){
    for(int i=0;i<MAX_PRIME;i++) SPF_arr[i] = i;
    for(int i=2;i*i < MAX_PRIME;i++){
        if(SPF_arr[i]==i){
            for(int j=i*i; j<MAX_PRIME; j+=i){
                if(SPF_arr[j]==j){
                    SPF_arr[j] = i;
                }
            }
        }
    }
}

// Factorize a number using SPF, returns the number of factors
int factorize(int num, Factor *factors){
    int count =0;
    if(num ==1){
        return count;
    }
    while(num >1){
        int p = SPF_arr[num];
        if(count ==0 || factors[count-1].prime != p){
            factors[count].prime = p;
            factors[count].exp =1;
            count++;
        }
        else{
            factors[count-1].exp++;
        }
        num /=p;
    }
    return count;
}

int main(){
    sieve();
    int test;
    if(scanf("%d", &test)!=1) return 0;
    while(test--){
        int m;
        if(scanf("%d", &m)!=1) break;
        // Initialize N_factors
        Factor N_factors[MAX_FACTORS];
        int N_size =0;
        for(int i=0;i<m;i++){
            int p;
            long long q;
            if(scanf("%d %lld", &p, &q)!=2) break;
            if(q >0){
                N_factors[N_size].prime = p;
                N_factors[N_size].exp = q;
                N_size++;
            }
        }
        // Sort N_factors by prime
        qsort(N_factors, N_size, sizeof(Factor), cmp_factors);
        // Merge duplicates if any
        int merged =0;
        for(int i=0;i<N_size;i++){
            if(merged==0 || N_factors[i].prime != N_factors[merged-1].prime){
                N_factors[merged++] = N_factors[i];
            }
            else{
                N_factors[merged-1].exp += N_factors[i].exp;
            }
        }
        N_size = merged;
        // Compute x
        int x =0;
        while(N_size >0){
            // Compute phi(N)
            Factor temp_factors[MAX_TEMP];
            int temp_size =0;
            for(int i=0;i<N_size;i++){
                int p = N_factors[i].prime;
                long long q = N_factors[i].exp;
                // Factorize (p-1)
                Factor f_list[20];
                int f_size = factorize(p-1, f_list);
                for(int j=0;j<f_size;j++){
                    temp_factors[temp_size++] = f_list[j];
                }
                // If q >1, add p^{q-1}
                if(q >1){
                    temp_factors[temp_size].prime = p;
                    temp_factors[temp_size].exp = q-1;
                    temp_size++;
                }
            }
            if(temp_size ==0){
                break;
            }
            // Sort temp_factors by prime
            qsort(temp_factors, temp_size, sizeof(Factor), cmp_factors);
            // Merge duplicates
            Factor new_factors[MAX_FACTORS];
            int new_size =0;
            for(int i=0;i<temp_size;i++){
                if(new_size ==0 || temp_factors[i].prime != new_factors[new_size-1].prime){
                    new_factors[new_size++] = temp_factors[i];
                }
                else{
                    new_factors[new_size-1].exp += temp_factors[i].exp;
                }
            }
            // Update N_factors
            for(int i=0;i<new_size;i++){
                N_factors[i] = new_factors[i];
            }
            N_size = new_size;
            x++;
        }
        printf("%d\n", x);
    }
    return 0;
}