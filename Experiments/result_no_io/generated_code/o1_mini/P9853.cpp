#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_N 200005

typedef long long ll;

ll solutions[MAX_N];
ll unique_solutions[MAX_N];
int unique_count = 0;

// Fast read
char buffer[1<<24];
size_t buf_pos = 0, buf_len = 0;

inline char get_char(){
    if(buf_pos >= buf_len){
        buf_len = fread(buffer, 1, sizeof(buffer), stdin);
        buf_pos = 0;
        if(buf_len == 0) return EOF;
    }
    return buffer[buf_pos++];
}

inline int read_int(){
    int x=0, sign=1;
    char c = get_char();
    while(c != '-' && !isdigit(c) && c != EOF) c = get_char();
    if(c == '-'){ sign=-1; c = get_char(); }
    while(isdigit(c)){
        x = x*10 + (c - '0');
        c = get_char();
    }
    return x * sign;
}

inline ll read_ll(){
    ll x=0;
    int sign=1;
    char c = get_char();
    while(c != '-' && !isdigit(c) && c != EOF) c = get_char();
    if(c == '-'){ sign=-1; c = get_char(); }
    while(isdigit(c)){
        x = x*10 + (c - '0');
        c = get_char();
    }
    return x * sign;
}

int cmp_ll(const void *a, const void *b){
    ll aa = *(ll*)a, bb = *(ll*)b;
    if(aa < bb) return -1;
    if(aa > bb) return 1;
    return 0;
}

int main(){
    int n, Q;
    n = read_int();
    Q = read_int();
    for(int i=0;i<n;i++){
        char eq[30];
        int idx=0;
        char c;
        while((c = get_char()) != '\n' && c != EOF){
            eq[idx++] = c;
        }
        eq[idx] = '\0';
        // Parse a, b, c
        int a=0, b=0, c_val=0;
        int pos = 0, len = idx;
        // Parse a
        int sign_a = 1;
        if(eq[pos] == '-'){ sign_a = -1; pos++; }
        while(isdigit(eq[pos])){
            a = a*10 + (eq[pos]-'0');
            pos++;
        }
        a *= sign_a;
        // Skip 'x'
        while(eq[pos] != 'x' && pos < len) pos++;
        pos++;
        // Parse operator
        int sign_b = 1;
        if(eq[pos] == '+'){ sign_b = 1; pos++; }
        else { sign_b = -1; pos++; }
        // Parse b
        while(isdigit(eq[pos])){
            b = b*10 + (eq[pos]-'0');
            pos++;
        }
        b *= sign_b;
        // Skip '='
        while(eq[pos] != '=' && pos < len) pos++;
        pos++;
        // Parse c
        int sign_c = 1;
        if(eq[pos] == '-'){ sign_c = -1; pos++; }
        while(isdigit(eq[pos])){
            c_val = c_val*10 + (eq[pos]-'0');
            pos++;
        }
        c_val *= sign_c;
        // Compute x
        if(a == 0){
            // No solution unless b == c
            if(b == c_val){
                // Infinitely many x, but x must be positive integer, up to 2e9
                // As per problem, each equation has exactly one positive integer solution
            }
        }
        else{
            ll x = (ll)(c_val - b) / a;
            if(a != 0 && (c_val - b) % a == 0 && x > 0){
                solutions[unique_count++] = x;
            }
        }
    }
    // Sort and remove duplicates
    qsort(solutions, unique_count, sizeof(ll), cmp_ll);
    unique_solutions[0] = solutions[0];
    int uc = 1;
    for(int i=1;i<unique_count;i++) {
        if(solutions[i] != unique_solutions[uc-1]){
            unique_solutions[uc++] = solutions[i];
        }
    }
    // Process queries
    for(int i=0;i<Q;i++){
        ll L = read_ll();
        ll R = read_ll();
        // Binary search for lower_bound and upper_bound
        // lower_bound: first >= L
        int left = 0, right = uc;
        while(left < right){
            int mid = left + (right - left)/2;
            if(unique_solutions[mid] >= L) right = mid;
            else left = mid + 1;
        }
        int lb = left;
        // upper_bound: first > R
        left = 0; right = uc;
        while(left < right){
            int mid = left + (right - left)/2;
            if(unique_solutions[mid] > R) right = mid;
            else left = mid + 1;
        }
        int ub = left;
        printf("%d\n", ub - lb);
    }
    return 0;
}