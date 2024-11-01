#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INT 10000
#define MAX_FRAC 6000

typedef struct {
    char integer[MAX_INT];
    int integer_len;
    char frac[MAX_FRAC];
    int frac_len;
} BigDecimal;

// Initialize BigDecimal with integer value
void init_bd(BigDecimal *bd, long long val, int p) {
    bd->integer_len = 0;
    if(val == 0){
        bd->integer[bd->integer_len++] = '0';
    }
    else{
        while(val > 0){
            bd->integer[bd->integer_len++] = (val %10) + '0';
            val /=10;
        }
    }
    // Initialize fractional part with zeros
    bd->frac_len = 0;
    for(int i=0;i<2*p;i++) bd->frac[bd->frac_len++] = '0';
}

// Add integer s to BigDecimal
void add_integer_bd(BigDecimal *bd, long long s) {
    // Add s to integer part
    int carry = 0;
    int i =0;
    while(s >0 || carry) {
        int digit_s = s %10;
        s /=10;
        int digit_bd = (i < bd->integer_len) ? (bd->integer[i]-'0') : 0;
        int total = digit_bd + digit_s + carry;
        if(i < bd->integer_len){
            bd->integer[i] = (total %10) + '0';
        }
        else{
            bd->integer[bd->integer_len++] = (total %10) + '0';
        }
        carry = total /10;
        i++;
    }
}

// Divide BigDecimal by m, store result in res
void divide_bd(BigDecimal *bd, int m, BigDecimal *res, int p) {
    // Initialize res
    memset(res, 0, sizeof(BigDecimal));
    // Divide integer part
    long long dividend =0;
    for(int i = bd->integer_len-1;i>=0;i--){
        dividend = dividend *10 + (bd->integer[i]-'0');
        res->integer[res->integer_len++] = (dividend /m) + '0';
        dividend = dividend %m;
    }
    // If integer part is 0
    if(res->integer_len ==0){
        res->integer[res->integer_len++] = '0';
    }
    // Divide fractional part
    for(int i=0;i<2*p;i++){
        dividend = dividend *10;
        if(i < bd->frac_len){
            dividend += (bd->frac[i]-'0');
        }
        long long qt = dividend /m;
        res->frac[res->frac_len++] = qt + '0';
        dividend = dividend %m;
    }
    // Remove trailing zeros in integer part
    while(res->integer_len >1 && res->integer[res->integer_len-1] == '0'){
        res->integer_len--;
    }
}

// Compare h_j to h1, return 1 if h_j > h1, 0 otherwise
int compare(int hj, BigDecimal *h1) {
    // Compare hj with integer part of h1
    // First, compare number of digits
    int len_hj =0;
    int tmp = hj;
    if(tmp ==0) len_hj =1;
    else{
        while(tmp >0){
            len_hj++;
            tmp /=10;
        }
    }
    if(len_hj > h1->integer_len) return 1;
    if(len_hj < h1->integer_len) return 0;
    // Same length, compare digit by digit from high to low
    for(int i = len_hj-1;i>=0;i--){
        char ch_hj = '0' + (hj /1 %10);
        if(hj >=10){
            ch_hj = '0' + ((hj / (int)pow(10, i)) %10);
        }
        if(h1->integer[i] < ch_hj) return 1;
        if(h1->integer[i] > ch_hj) return 0;
    }
    // h_j == integer part of h1, check fractional
    for(int i=0;i<h1->frac_len;i++) {
        if(h1->frac[i] > '0') return 1;
        else break;
    }
    return 0;
}

// Check if h_j == integer part of h1 and h1 has fraction >0
int equal_and_frac(BigDecimal *h1, int hj){
    // Compare hj with integer part
    int len_hj =0;
    int tmp = hj;
    if(tmp ==0) len_hj =1;
    else{
        while(tmp >0){
            len_hj++;
            tmp /=10;
        }
    }
    if(len_hj != h1->integer_len) return 0;
    for(int i =0;i<h1->integer_len;i++){
        int digit_hj = (hj / (int)pow(10, h1->integer_len -1 -i)) %10;
        if(h1->integer[h1->integer_len -1 -i] - '0' != digit_hj) return 0;
    }
    // Check if fractional part >0
    for(int i=0;i<h1->frac_len;i++) {
        if(h1->frac[i] > '0') return 1;
    }
    return 0;
}

int main(){
    int n, k, p;
    scanf("%d %d %d", &n, &k, &p);
    int h[n];
    for(int i=0;i<n;i++) scanf("%d", &h[i]);
    // Sort h_j descendingly
    int hj_sorted[n-1];
    for(int i=1;i<n;i++) hj_sorted[i-1] = h[i];
    // Simple bubble sort for small n
    for(int i=0;i<n-1;i++) {
        for(int j=i+1;j<n-1;j++) {
            if(hj_sorted[i] < hj_sorted[j]){
                int temp = hj_sorted[i];
                hj_sorted[i] = hj_sorted[j];
                hj_sorted[j] = temp;
            }
        }
    }
    // Initialize h1
    BigDecimal h1, res;
    init_bd(&h1, h[0], p);
    long long sum_selected;
    for(int op=0; op<k; op++){
        // Find set S
        int count =0;
        sum_selected =0;
        for(int i=0;i<n-1;i++){
            int hj = hj_sorted[i];
            if(hj > h1.integer_len){
                count++;
                sum_selected += hj;
            }
            else{
                // Compare hj with h1
                // Reconstruct h1 integer
                long long h1_int =0;
                for(int d=0; d<h1.integer_len; d++) h1_int += (h1.integer[d]-'0') * (long long)pow(10, d);
                if(hj > h1_int){
                    count++;
                    sum_selected += hj;
                }
                else if(hj == h1_int){
                    // Check fraction
                    int has_frac =0;
                    for(int f=0; f<h1.frac_len; f++) {
                        if(h1.frac[f] > '0'){ has_frac =1; break;}
                    }
                    if(has_frac){
                        count++;
                        sum_selected += hj;
                    }
                }
                else{
                    break;
                }
            }
        }
        if(count ==0) break;
        // Add sum_selected to h1
        add_integer_bd(&h1, sum_selected);
        // Divide h1 by (count +1)
        divide_bd(&h1, count+1, &res, p);
        // Update h1
        memcpy(&h1, &res, sizeof(BigDecimal));
    }
    // Prepare output
    // Build integer part
    char integer_out[MAX_INT+1];
    for(int i=0;i<h1.integer_len;i++) integer_out[i] = h1.integer[h1.integer_len-1 -i];
    integer_out[h1.integer_len] = '\0';
    // Build fractional part
    char frac_out[2*p +1];
    for(int i=0;i<2*p;i++) {
        if(i < h1.frac_len) frac_out[i] = h1.frac[i];
        else frac_out[i] = '0';
    }
    frac_out[2*p] = '\0';
    // Truncate to p digits
    frac_out[p] = '\0';
    // Remove trailing zeros
    int last = p-1;
    while(last >0 && frac_out[last] == '0') last--;
    frac_out[last+1] = '\0';
    // Check if there are fractional digits
    int has_frac =0;
    for(int i=0;i<=last;i++) if(frac_out[i]!='0') {has_frac=1; break;}
    // Print
    if(p >0){
        printf("%s.", integer_out);
        for(int i=0;i<p;i++) {
            if(i <= last) printf("%c", frac_out[i]);
            else printf("0");
        }
    }
    else{
        printf("%s", integer_out);
    }
    return 0;
}