#include <stdio.h>

int is_palindrome(int number, int base) {
    int digits[32];
    int count = 0;
    if (number == 0) {
        digits[count++] = 0;
    } else {
        while (number > 0) {
            digits[count++] = number % base;
            number /= base;
        }
    }
    if (count == 0) return 0;
    if (digits[0] == 0 || digits[count -1] == 0) return 0;
    for(int i=0;i<count/2;i++) {
        if(digits[i] != digits[count -1 -i]) return 0;
    }
    return 1;
}

int main(){
    int n, s;
    scanf("%d %d", &n, &s);
    int found = 0;
    int num = s +1;
    while(found < n){
        int count =0;
        for(int base=2;base<=10;base++){
            if(is_palindrome(num, base)){
                count++;
                if(count >=2){
                    break;
                }
            }
        }
        if(count >=2){
            printf("%d\n", num);
            found++;
        }
        num++;
    }
    return 0;
}