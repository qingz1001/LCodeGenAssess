#include <stdio.h>
#include <string.h>

#define MAX 1002

int main(){
    char a[MAX], b[MAX], res[MAX];
    scanf("%s %s", a, b);
    int len_a = strlen(a);
    int len_b = strlen(b);
    int carry = 0, i = len_a -1, j = len_b -1, k =0;
    while(i >=0 || j >=0 || carry){
        int digit_a = (i >=0) ? a[i] - '0' : 0;
        int digit_b = (j >=0) ? b[j] - '0' : 0;
        int sum = digit_a + digit_b + carry;
        res[k++] = (sum %10) + '0';
        carry = sum /10;
        i--;
        j--;
    }
    // Reverse the result
    for(int l = k-1; l >=0; l--){
        printf("%c", res[l]);
    }
    return 0;
}