#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10000
#define MAXLEN 256
#define MAXDIGITS 2100

char names_array[10000][256];
int n, m;

int cmp(const void *a, const void *b){
    return strcmp((char*)a, (char*)b);
}

int has_prefix(char sorted_names[][256], int n, char *s){
    int left = 0, right = n - 1, mid, res = 0;
    int len = strlen(s);
    while(left <= right){
        mid = left + (right - left) / 2;
        int cmp_res = strncmp(sorted_names[mid], s, len);
        if(cmp_res == 0){
            return 1;
        }
        if(cmp_res < 0){
            left = mid + 1;
        }
        else{
            right = mid -1;
        }
    }
    return 0;
}

typedef struct {
    char digits[MAXDIGITS];
    int len;
} BigInt;

void init_bigint(BigInt *num, int initial){
    num->len = 0;
    if(initial == 0){
        num->digits[num->len++] = '0';
    }
    else{
        while(initial > 0){
            num->digits[num->len++] = (initial % 10) + '0';
            initial /=10;
        }
    }
}

void add_bigint(BigInt *a, BigInt *b, BigInt *res){
    int carry = 0, i;
    res->len = 0;
    for(i = 0; i < a->len || i < b->len; i++){
        int digit_a = (i < a->len) ? (a->digits[i]-'0') : 0;
        int digit_b = (i < b->len) ? (b->digits[i]-'0') : 0;
        int total = digit_a + digit_b + carry;
        res->digits[res->len++] = (total % 10) + '0';
        carry = total /10;
    }
    if(carry){
        res->digits[res->len++] = carry + '0';
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i =0;i<n;i++){
        scanf("%s", names_array[i]);
    }
    qsort(names_array, n, sizeof(names_array[0]), cmp);
    int count =0;
    char s[256];
    for(int i =0;i<m;i++){
        scanf("%s", s);
        if(has_prefix(names_array, n, s)){
            count++;
        }
    }
    // Compute F(n+1)
    BigInt F_prev, F_curr, F_next;
    init_bigint(&F_prev,1); // F(1)=1
    if(n ==0){
        // Not possible as n >=1
    }
    if(n >=1){
        init_bigint(&F_curr,2); // F(2)=2
    }
    for(int i=3;i<=n+1;i++){
        add_bigint(&F_prev, &F_curr, &F_next);
        F_prev = F_curr;
        F_curr = F_next;
    }
    // Handle n=0 and n=1
    if(n ==0){
        init_bigint(&F_curr,1);
    }
    else if(n ==1){
        // F(2) already
    }
    // Output
    printf("%d\n", count);
    // Print F(n+1)
    for(int i = F_curr.len-1;i>=0;i--){
        putchar(F_curr.digits[i]);
    }
    putchar('\n');
    return 0;
}