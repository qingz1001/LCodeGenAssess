#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int digits[1000];
    int len;
} bigint;

// Initialize bigint to zero
void init_bigint(bigint *a) {
    for(int i = 0; i < 1000; i++) a->digits[i] = 0;
    a->len = 0;
}

// Initialize bigint from unsigned long long
void bigint_from_uint64(bigint *a, unsigned long long b) {
    init_bigint(a);
    if(b == 0){
        a->digits[0] = 0;
        a->len = 1;
        return;
    }
    while(b > 0){
        a->digits[a->len++] = b % 10;
        b /= 10;
    }
}

// Multiply bigint by unsigned long long
void multiply_bigint_by_uint64(bigint *a, unsigned long long b){
    unsigned long long carry = 0;
    for(int i = 0; i < a->len; i++){
        unsigned long long temp = (unsigned long long)a->digits[i] * b + carry;
        a->digits[i] = temp % 10;
        carry = temp / 10;
    }
    while(carry > 0){
        a->digits[a->len++] = carry % 10;
        carry /= 10;
    }
}

// Multiply two bigints, store result in res
void multiply_bigints(const bigint *a, const bigint *b, bigint *res){
    init_bigint(res);
    for(int i = 0; i < a->len; i++){
        unsigned long long carry = 0;
        for(int j = 0; j < b->len; j++){
            if(i + j >= 1000) break;
            unsigned long long temp = a->digits[i] * b->digits[j] + res->digits[i+j] + carry;
            res->digits[i+j] = temp % 10;
            carry = temp / 10;
        }
        if(i + b->len < 1000){
            res->digits[i + b->len] += carry;
        }
    }
    // Determine the length
    res->len = a->len + b->len;
    while(res->len >1 && res->digits[res->len-1] ==0) res->len--;
}

// Add unsigned long long to bigint
void add_bigint_uint64(bigint *a, unsigned long long b){
    int i = 0;
    while(b > 0 && i < a->len){
        a->digits[i] += b % 10;
        if(a->digits[i] >= 10){
            a->digits[i] -=10;
            if(i+1 >= a->len){
                a->digits[a->len++] =1;
            }
            else{
                a->digits[i+1]++;
            }
        }
        b /=10;
        i++;
    }
    while(b >0){
        a->digits[a->len++] = b %10;
        b /=10;
    }
    // Handle carry
    while(a->len >0 && a->digits[a->len-1] >=10){
        int carry = a->digits[a->len-1] /10;
        a->digits[a->len-1] %=10;
        if(a->len < 1000){
            a->digits[a->len++] = carry;
        }
    }
}

// Print bigint
void print_bigint(const bigint *a){
    for(int i = a->len -1; i >=0; i--){
        putchar(a->digits[i] + '0');
    }
    putchar('\n');
}

unsigned long long factorials[21];

int main(){
    int n, k, h;
    scanf("%d %d %d", &n, &k, &h);
    int c[h];
    for(int i=0; i<h; i++) scanf("%d", &c[i]);

    // Compute factorials
    factorials[0] =1;
    for(int i=1; i<=20; i++) factorials[i] = factorials[i-1] * i;

    // Compute C(n,k)
    if(k > n){
        printf("0\n");
        return 0;
    }
    unsigned long long C = 1;
    for(int i=1; i<=k; i++) {
        C *= (n - i +1);
        C /= i;
    }

    // Compute C^2
    unsigned long long C_squared = C * C;

    // Compute k!
    unsigned long long k_fact = factorials[k];

    // Initialize placement bigint
    bigint placement;
    bigint_from_uint64(&placement, C_squared);
    multiply_bigint_by_uint64(&placement, k_fact);

    // Compute color assignments
    // Prepare factorials up to 20
    unsigned long long a_fact[21];
    a_fact[0] =1;
    for(int i=1; i<=20; i++) a_fact[i] = a_fact[i-1] * i;

    // Initialize A_sum
    bigint A_sum;
    init_bigint(&A_sum);
    A_sum.len =1;
    A_sum.digits[0] =0;

    // Recursive function to compute assignments
    // color_idx: current color
    // rem: remaining items to assign
    // current_num: k! / (a1!...ai!)
    // A_sum: accumulated sum
    // Using recursion
    // To avoid stack overflow, use iterative with indices
    // But since h and k are small, recursion is feasible

    // Define recursive function
    // Using nested function via helper
    // C does not support nested functions, use a helper function with additional parameters
    // Implemented via separate function
    // So define a helper using global variables

    // Global variables for simplicity
    unsigned long long global_k_fact;
    int global_h;
    int *global_c;
    unsigned long long global_a_fact[21];
    bigint *global_A_sum_ptr;

    void recurse_assign(int color_idx, int rem, unsigned long long current_num){
        if(color_idx == global_h){
            if(rem ==0){
                add_bigint_uint64(global_A_sum_ptr, current_num);
            }
            return;
        }
        for(int a_i=0; a_i <= rem && a_i <= global_c[color_idx]; a_i++){
            unsigned long long next_num = current_num;
            if(global_a_fact[a_i] !=0){
                next_num /= global_a_fact[a_i];
            }
            recurse_assign(color_idx +1, rem -a_i, next_num);
        }
    }

    // Assign global variables
    global_k_fact = k_fact;
    global_h = h;
    global_c = c;
    for(int i=0; i<=20; i++) global_a_fact[i] = a_fact[i];
    global_A_sum_ptr = &A_sum;

    // Call recursive function
    recurse_assign(0, k, global_k_fact);

    // Multiply placement and A_sum
    bigint total;
    multiply_bigints(&placement, &A_sum, &total);

    // Print the result
    print_bigint(&total);

    return 0;
}