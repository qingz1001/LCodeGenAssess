#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct {
    int len;
    char digits[205]; // digits[0] is least significant digit
} BigInt;

// Function to add two BigInts
void add_bigint(BigInt a, BigInt b, BigInt *res){
    res->len = 0;
    int carry = 0, i = 0;
    while(i < a.len || i < b.len || carry){
        int digit_a = (i < a.len) ? (a.digits[i] - '0') : 0;
        int digit_b = (i < b.len) ? (b.digits[i] - '0') : 0;
        int s = digit_a + digit_b + carry;
        carry = s / 10;
        res->digits[res->len++] = (s % 10) + '0';
        i++;
    }
}

// Function to copy BigInt src to dst
void copy_bigint(BigInt *src, BigInt *dst){
    dst->len = src->len;
    for(int i = 0; i < src->len; i++) {
        dst->digits[i] = src->digits[i];
    }
}

// Function to compute floor of log2(x)
int floor_log2_func(int x){
    if(x ==0) return 0;
    int res = 0;
    while(x >= 2){
        x = x >>1;
        res++;
    }
    return res;
}

// Function to print BigInt
void print_bigint(BigInt n){
    int i = n.len -1;
    while(i >0 && n.digits[i] == '0') i--;
    for(; i >=0; i--){
        printf("%c", n.digits[i]);
    }
}

int main(){
    int k, w;
    scanf("%d %d", &k, &w);
    int B = 1;
    for(int i=0;i<k;i++) B *=2;
    // Initialize C[n][m]
    // Maximum B is 512, so n and m up to 512
    BigInt C[512][512];
    for(int n=0; n<B; n++){
        for(int m=0; m<=n; m++){
            if(m ==0 || m ==n){
                C[n][m].len =1;
                C[n][m].digits[0] = '1';
            }
            else{
                BigInt temp;
                add_bigint(C[n-1][m-1], C[n-1][m], &temp);
                C[n][m].len = temp.len;
                for(int d=0; d<temp.len; d++) C[n][m].digits[d] = temp.digits[d];
            }
        }
    }
    // Initialize total_sum to zero
    BigInt total_sum;
    total_sum.len =1;
    total_sum.digits[0] = '0';
    // Iterate over d1 from1 to B-2
    for(int d1=1; d1 <= B-2; d1++){
        int bits_first = floor_log2_func(d1) +1;
        if(bits_first + k > w) continue;
        int l_max_prime = (w - bits_first)/k +1;
        int l_max = l_max_prime < (B - d1) ? l_max_prime : (B - d1);
        if(l_max <2) continue;
        int m_real_max = (l_max -1) < (B-1 -d1) ? (l_max -1) : (B-1 -d1);
        for(int m=1; m<=m_real_max; m++){
            BigInt temp;
            add_bigint(total_sum, C[B-1 -d1][m], &temp);
            copy_bigint(&temp, &total_sum);
        }
    }
    // Print the total_sum
    print_bigint(total_sum);
    return 0;
}