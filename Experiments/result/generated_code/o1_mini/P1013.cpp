#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 10
#define MAXM 9
#define MAXSTR 20

int n;
char tableData[MAXN][MAXN][MAXSTR];
char symbols[MAXM];
int m;
int digits[MAXM];
char digit_to_symbol_map[20];
int found = 0;

// Function to convert sum to symbol string based on digit_to_symbol_map
int convert_sum_to_symbols(int sum, int base, char* result) {
    char temp[20];
    int idx = 0;
    if(sum == 0){
        temp[idx++] = digit_to_symbol_map[0];
    }
    else{
        while(sum > 0){
            int rem = sum % base;
            if(rem >= base) return 0; // Invalid digit
            temp[idx++] = digit_to_symbol_map[rem];
            sum /= base;
        }
    }
    // Reverse to get the correct order
    for(int i=0;i<idx;i++) {
        result[i] = temp[idx-1-i];
    }
    result[idx] = '\0';
    return 1;
}

// Recursive backtracking function
int backtrack(int level, int base, int m, int used[]) {
    if(found) return 0;
    if(level == m){
        // Build digit_to_symbol_map
        for(int d=0; d<base; d++) {
            digit_to_symbol_map[d] = '?';
            for(int k=0; k<m; k++) {
                if(digits[k] == d){
                    digit_to_symbol_map[d] = symbols[k];
                    break;
                }
            }
            if(digit_to_symbol_map[d] == '?') return 0; // Unmapped digit
        }
        // Now verify the table
        for(int i=1; i<n; i++){
            for(int j=1; j<n; j++){
                int a = digits[i-1];
                int b = digits[j-1];
                int sum = a + b;
                char sum_str[MAXSTR];
                if(!convert_sum_to_symbols(sum, base, sum_str)) return 0;
                if(strcmp(sum_str, tableData[i][j]) != 0) return 0;
            }
        }
        // If all matched
        // Print the mapping
        for(int k=0; k<m; k++){
            printf("%c=%d", symbols[k], digits[k]);
            if(k != m-1) printf(" ");
        }
        printf("\n%d\n", base);
        found = 1;
        return 0;
    }
    for(int d=0; d<base; d++){
        if(!used[d]){
            digits[level] = d;
            used[d] = 1;
            backtrack(level+1, base, m, used);
            used[d] = 0;
            if(found) return 0;
        }
    }
    return 0;
}

int main(){
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        for(int j=0; j<n; j++) {
            scanf("%s", tableData[i][j]);
        }
    }
    // Extract symbols from first row, columns 1 to n-1
    m = n-1;
    for(int i=0;i<m;i++) symbols[i] = tableData[0][i+1][0];
    // Try base from m to m+5
    for(int base = m; base <= 16 && !found; base++){
        int used[20] = {0};
        backtrack(0, base, m, used);
    }
    if(!found) printf("ERROR!\n");
    return 0;
}