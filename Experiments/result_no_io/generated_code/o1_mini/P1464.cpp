#include <stdio.h>
#include <stdint.h>

long long w_table[21][21][21];

// Initialize w_table with -1
void initialize_w_table() {
    for(int a=0; a<=20; a++)
        for(int b=0; b<=20; b++)
            for(int c=0; c<=20; c++)
                w_table[a][b][c] = -1;
}

// Compute w(a, b, c) with memoization
long long compute_w(int a, int b, int c) {
    if(a <= 0 || b <= 0 || c <= 0)
        return 1;
    if(a > 20 || b > 20 || c > 20)
        return w_table[20][20][20];
    if(w_table[a][b][c] != -1)
        return w_table[a][b][c];
    if(a < b && b < c)
        w_table[a][b][c] = compute_w(a, b, c-1) + compute_w(a, b-1, c-1) - compute_w(a, b-1, c);
    else
        w_table[a][b][c] = compute_w(a-1, b, c) + compute_w(a-1, b-1, c) + compute_w(a-1, b, c-1) - compute_w(a-1, b-1, c-1);
    return w_table[a][b][c];
}

int main(){
    initialize_w_table();
    // Precompute all w(a,b,c)
    for(int a=0; a<=20; a++)
        for(int b=0; b<=20; b++)
            for(int c=0; c<=20; c++)
                if(w_table[a][b][c] == -1)
                    compute_w(a, b, c);
    
    long long a, b, c;
    while(scanf("%lld %lld %lld", &a, &b, &c) == 3){
        if(a == -1 && b == -1 && c == -1)
            break;
        long long ans;
        if(a <= 0 || b <= 0 || c <= 0)
            ans = 1;
        else if(a > 20 || b > 20 || c > 20)
            ans = w_table[20][20][20];
        else
            ans = w_table[a][b][c];
        printf("w(%lld, %lld, %lld) = %lld\n", a, b, c, ans);
    }
    return 0;
}