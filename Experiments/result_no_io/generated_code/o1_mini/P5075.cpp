#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to compute inverse modulo P using Extended Euclidean Algorithm
int invmod(int a, int P){
    int t = 0, newt = 1;
    int r = P, newr = a;
    while(newr != 0){
        int quotient = r / newr;
        int tmp = t - quotient * newt;
        t = newt;
        newt = tmp;
        tmp = r - quotient * newr;
        r = newr;
        newr = tmp;
    }
    if(r > 1) return 0; // Inverse does not exist
    if(t < 0) t += P;
    return t;
}

int main(){
    int M, P;
    scanf("%d %d", &M, &P);
    long long A;
    scanf("%lld", &A);
    int O, S_coeff, U;
    scanf("%d", &O);
    scanf("%d", &S_coeff);
    scanf("%d", &U);
    
    // Compute f[x] = O*x^2 + S*x + U mod P for x from 1 to M
    int *f = (int*)malloc((M+1) * sizeof(int));
    for(int x = 1; x <= M; x++){
        long long fx = ((long long)O * x * x + (long long)S_coeff * x + (long long)U) % P;
        f[x] = fx < 0 ? fx + P : fx;
    }
    
    // Determine maximum k
    int K = (A < M) ? (int)A : M;
    
    // Compute factorial[k] mod P for k from 0 to K
    int *fact = (int*)malloc((K+1) * sizeof(int));
    fact[0] = 1 % P;
    for(int k = 1; k <= K; k++){
        fact[k] = ((long long)fact[k-1] * k) % P;
    }
    
    // Compute A mod P
    int A_mod_P = A % P;
    
    // Initialize DP arrays
    int *prev = (int*)calloc(M+1, sizeof(int));
    int *current = (int*)calloc(M+1, sizeof(int));
    prev[0] = 1;
    
    int S_sum = 0;
    
    for(int k = 1; k <= K; k++){
        // Reset current
        memset(current, 0, (M+1) * sizeof(int));
        
        // Populate current based on prev and f[x]
        for(int m_prev = 0; m_prev <= M; m_prev++){
            if(prev[m_prev] == 0) continue;
            for(int x = 1; x <= M - m_prev; x++){
                current[m_prev + x] = (current[m_prev + x] + (int)((long long)f[x] * prev[m_prev] % P)) % P;
            }
        }
        
        // F(k, M) is current[M]
        int F_k_M = current[M];
        
        // Compute C(A, k) mod P
        int comb = 0;
        if(k <= A){
            if(fact[k] != 0){
                int inv_fact_k = invmod(fact[k], P);
                if(inv_fact_k != 0){
                    long long prod = 1;
                    for(int i = 0; i < k; i++){
                        int term = (A_mod_P - i) % P;
                        if(term < 0) term += P;
                        prod = (prod * term) % P;
                    }
                    comb = (int)((prod * (long long)inv_fact_k) % P);
                }
            }
        }
        
        // Add to S_sum
        S_sum = (S_sum + (int)((long long)comb * F_k_M % P)) % P;
        
        // Swap prev and current for next iteration
        int *temp = prev;
        prev = current;
        current = temp;
    }
    
    // Add the case where k = 0
    S_sum = (S_sum + 1) % P;
    
    printf("%d\n", S_sum);
    
    // Free allocated memory
    free(f);
    free(fact);
    free(prev);
    free(current);
    
    return 0;
}