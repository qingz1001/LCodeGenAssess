#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 500

// Convert a character to its numerical value
int char_to_val(char c){
    if(c >= '0' && c <= '9') return c - '0';
    else return toupper(c) - 'A' + 10;
}

// Convert a numerical value to its character representation
char val_to_char(int val){
    if(val >=0 && val <=9) return '0' + val;
    else return 'A' + (val -10);
}

// Reverse a string
void reverse_str(char *src, char *dest){
    int len = strlen(src);
    for(int i=0;i<len;i++) dest[i]=src[len-1-i];
    dest[len] = '\0';
}

// Add two numbers in base N. a and b are input strings, result is stored in res
void add_baseN(char *a, char *b, int N, char *res){
    int len_a = strlen(a);
    int len_b = strlen(b);
    int max_len = len_a > len_b ? len_a : len_b;
    int carry = 0;
    res[max_len +1] = '\0';
    int idx = 0;
    for(int i=1;i<=max_len;i++){
        int digit_a = (len_a -i >=0) ? char_to_val(a[len_a -i]) : 0;
        int digit_b = (len_b -i >=0) ? char_to_val(b[len_b -i]) : 0;
        int sum = digit_a + digit_b + carry;
        carry = sum / N;
        sum = sum % N;
        res[idx++] = val_to_char(sum);
    }
    if(carry) res[idx++] = val_to_char(carry);
    // Now reverse the result
    for(int i=0;i<idx;i++) res[idx-i-1] = res[i];
    res[idx] = '\0';
}

// Check if the string is a palindrome
int is_palindrome(char *s){
    int len = strlen(s);
    for(int i=0;i<len/2;i++) if(toupper(s[i]) != toupper(s[len-1-i])) return 0;
    return 1;
}

int main(){
    int N;
    char M[MAX_LEN];
    scanf("%d", &N);
    scanf("%s", M);
    char current[MAX_LEN];
    strcpy(current, M);
    int step =0;
    while(step <=30){
        if(is_palindrome(current)){
            printf("STEP=%d\n", step);
            return 0;
        }
        if(step ==30){
            break;
        }
        char reversed[MAX_LEN];
        reverse_str(current, reversed);
        char sum[MAX_LEN*2];
        add_baseN(current, reversed, N, sum);
        strcpy(current, sum);
        step++;
    }
    printf("Impossible!\n");
    return 0;
}