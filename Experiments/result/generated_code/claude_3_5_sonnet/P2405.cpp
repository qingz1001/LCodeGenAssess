#include <stdio.h>
#include <string.h>

#define MAX_LEN 10001

void subtract(char* m, char* weight) {
    int carry = 0;
    for (int i = strlen(m) - 1; i >= 0; i--) {
        int diff = (m[i] - '0') - (weight[i] - '0') - carry;
        if (diff < 0) {
            diff += 10;
            carry = 1;
        } else {
            carry = 0;
        }
        m[i] = diff + '0';
    }
}

int compare(char* m, char* weight) {
    int len_m = strlen(m);
    int len_w = strlen(weight);
    
    if (len_m > len_w) return 1;
    if (len_m < len_w) return -1;
    
    return strcmp(m, weight);
}

int main() {
    char m[MAX_LEN] = {0};
    int n;
    
    scanf("%s %d", m, &n);
    
    int count = 0;
    char weight[MAX_LEN] = {0};
    weight[MAX_LEN - 1] = '1';
    
    while (m[0] != '0' || strlen(m) > 1) {
        if (compare(m, weight) >= 0) {
            subtract(m, weight);
            count++;
        } else {
            int i;
            for (i = strlen(weight) - 1; i > 0; i--) {
                weight[i] = '0';
            }
            weight[i] = '1';
        }
        
        // Multiply weight by n
        int carry = 0;
        for (int i = strlen(weight) - 1; i >= 0; i--) {
            int product = (weight[i] - '0') * n + carry;
            weight[i] = (product % 10) + '0';
            carry = product / 10;
        }
        if (carry > 0) {
            memmove(weight + 1, weight, strlen(weight) + 1);
            weight[0] = carry + '0';
        }
    }
    
    printf("%d\n", count);
    
    return 0;
}