#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 400005
#define MOD 998244353

typedef struct {
    long long count1;
    int variables;
    int valid;
} ExprResult;

char expr[MAX_LEN];
int m;

// Precompute powers of 2 modulo MOD
long long power2[MAX_LEN];

// Function to initialize power2
void init_power2(int max_v){
    power2[0] = 1;
    for(int i=1;i<=max_v;i++) {
        power2[i] = (power2[i-1] * 2) % MOD;
    }
}

// Recursive parser
ExprResult parse_expr(int start, int end){
    ExprResult res;
    res.valid = 0;
    res.count1 = 0;
    res.variables = 0;
    
    if(start > end){
        return res;
    }
    
    // If single character
    if(start == end){
        res.valid = 1;
        if(expr[start] == '0'){
            res.count1 = 0;
            res.variables = 0;
        }
        else if(expr[start] == '1'){
            res.count1 = 1;
            res.variables = 0;
        }
        else if(islower(expr[start])){
            res.count1 = power2[1]; // 2^1 / 2 =1
            res.variables = 1;
        }
        return res;
    }
    
    // If starts with '(' and ends with ')', try to parse inside
    if(expr[start] == '(' && expr[end] == ')'){
        ExprResult inner = parse_expr(start+1, end-1);
        if(inner.valid){
            res = inner;
            return res;
        }
    }
    
    // Try to find operator at top level
    int depth = 0;
    for(int i=start;i<=end;i++){
        if(expr[i] == '('){
            depth++;
        }
        else if(expr[i] == ')'){
            depth--;
        }
        else if((expr[i] == '&' || expr[i] == '|' || expr[i] == '^') && depth == 0){
            // Split into left and right
            ExprResult left = parse_expr(start, i-1);
            ExprResult right = parse_expr(i+1, end);
            if(left.valid && right.valid){
                res.valid = 1;
                res.variables = left.variables + right.variables;
                long long total = (power2[left.variables + right.variables]) % MOD;
                long long total_left = power2[left.variables];
                long long total_right = power2[right.variables];
                long long total_assign = (total_left * total_right) % MOD;
                
                if(expr[i] == '&'){
                    res.count1 = (left.count1 * right.count1) % MOD;
                }
                else if(expr[i] == '|'){
                    res.count1 = (left.count1 * total_right + right.count1 * total_left - left.count1 * right.count1) % MOD;
                    if(res.count1 <0) res.count1 += MOD;
                }
                else if(expr[i] == '^'){
                    res.count1 = (left.count1 * (total_right - right.count1) + (total_left - left.count1) * right.count1) % MOD;
                    if(res.count1 <0) res.count1 += MOD;
                }
                // Ensure res.count1 is within [0, MOD)
                res.count1 %= MOD;
            }
            return res;
        }
    }
    
    // If no operator found, invalid
    return res;
}

int main(){
    // Read m
    scanf("%d", &m);
    // Read initial expression
    scanf("%s", expr);
    int len = strlen(expr);
    // Initialize power2 up to len
    init_power2(len);
    
    // Process m modifications
    for(int q=0; q<m; q++){
        int a;
        char b;
        scanf("%d %c", &a, &b);
        if(a >=1 && a <= len){
            expr[a-1] = b;
        }
        else{
            // Invalid position, ignore
        }
        // Now compute harmony
        long long harmony = 0;
        // Enumerate all substrings
        for(int i=0;i<len;i++){
            for(int j=i; j<len; j++){
                ExprResult tmp = parse_expr(i, j);
                if(tmp.valid){
                    harmony = (harmony + tmp.count1) % MOD;
                }
            }
        }
        printf("%lld\n", harmony);
    }
    return 0;
}