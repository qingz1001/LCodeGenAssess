#include <stdio.h>
#include <string.h>

int main() {
    char isbn[14];
    scanf("%s", isbn);
    
    int sum = 0;
    int j = 1;
    
    for (int i = 0; i < 12; i++) {
        if (isbn[i] != '-') {
            sum += (isbn[i] - '0') * j;
            j++;
        }
    }
    
    int check = sum % 11;
    char correct_check = (check == 10) ? 'X' : (check + '0');
    
    if (correct_check == isbn[12]) {
        printf("Right\n");
    } else {
        isbn[12] = correct_check;
        printf("%s\n", isbn);
    }
    
    return 0;
}