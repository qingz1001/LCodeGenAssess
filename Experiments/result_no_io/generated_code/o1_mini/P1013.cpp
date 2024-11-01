#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 10
#define MAX_M 9
#define MAX_B 10

int n;
char s[MAX_N][MAX_N][10];
char letters[MAX_M];
int m;
int mapping[26];
bool used_digits[MAX_B];
bool found = false;
int final_mapping[26];
int final_b;

bool verify(int b) {
    for(int i=1;i<n;i++) {
        for(int j=1;j<n;j++) {
            char row = s[i][0][0];
            char col = s[0][j][0];
            int sum_val = mapping[row - 'A'] + mapping[col - 'A'];
            if(sum_val < b) {
                if(strlen(s[i][j]) != 1) return false;
                char expected = 0;
                for(int k=0;k<m;k++) if(mapping[letters[k]-'A'] == sum_val) {expected = letters[k]; break;}
                if(s[i][j][0] != expected) return false;
            }
            else {
                if(strlen(s[i][j]) != 2) return false;
                int carry = sum_val / b;
                int digit = sum_val % b;
                char expected_carry = 0, expected_digit = 0;
                for(int k=0;k<m;k++) if(mapping[letters[k]-'A'] == carry) {expected_carry = letters[k]; break;}
                for(int k=0;k<m;k++) if(mapping[letters[k]-'A'] == digit) {expected_digit = letters[k]; break;}
                if(s[i][j][0] != expected_carry || s[i][j][1] != expected_digit) return false;
            }
        }
    }
    // Copy mapping to final_mapping
    for(int k=0;k<m;k++) final_mapping[letters[k]-'A'] = mapping[letters[k]-'A'];
    return true;
}

bool backtrack(int pos, int b) {
    if(found) return false;
    if(pos == m) {
        if(verify(b)) {
            final_b = b;
            found = true;
            return true;
        }
        return false;
    }
    for(int d=0;d<b;d++) {
        if(!used_digits[d]) {
            mapping[letters[pos]-'A'] = d;
            used_digits[d] = true;
            if(backtrack(pos+1, b)) return true;
            used_digits[d] = false;
        }
    }
    return false;
}

int main(){
    scanf("%d", &n);
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            scanf("%s", s[i][j]);
        }
    }
    // Collect letters from first row excluding s[0][0]
    m = 0;
    for(int j=1;j<n;j++) {
        letters[m++] = s[0][j][0];
    }
    // Iterate base from m to MAX_B
    for(int b = m; b <= MAX_B; b++) {
        if(b > MAX_B) break;
        memset(mapping, -1, sizeof(mapping));
        memset(used_digits, false, sizeof(used_digits));
        if(backtrack(0, b)) break;
    }
    if(found) {
        // Print letters and their mapping in order
        for(int k=0;k<m;k++) {
            printf("%c=%d", letters[k], final_mapping[letters[k]-'A']);
            if(k != m-1) printf(" ");
        }
        printf("\n%d\n", final_b);
    }
    else {
        printf("ERROR!\n");
    }
}