#include <stdio.h>
#include <string.h>

typedef long long ll;

int main(){
    // Define the standard seven-segment codes for digits 0-9
    int digit_codes[10] = {
        0b1111110, // 0
        0b0110000, // 1
        0b1101101, // 2
        0b1111001, // 3
        0b0110011, // 4
        0b1011011, // 5
        0b1011111, // 6
        0b1110000, // 7
        0b1111111, // 8
        0b1111011  // 9
    };
    
    // The 18 status codes as strings
    char status_str[18][8] = {
        "0000011", "1001011", "0000001", "0100001", "0101011", "0110110",
        "1111111", "0010110",
        "0101001", "0010110",
        "1011100", "0100110",
        "1010000", "0010011",
        "0001111", "0101101",
        "0110101", "1101010"
    };
    
    // Convert status codes to integer bitmask
    int status_codes[18];
    for(int i=0;i<18;i++){
        int code = 0;
        for(int j=0;j<7;j++) {
            if(status_str[i][j] == '1') code |= (1 << (6-j));
        }
        status_codes[i] = code;
    }
    
    // For each status code, count possible digits
    ll total = 1;
    for(int i=0;i<18;i++){
        int count = 0;
        for(int d=0; d<10; d++) {
            if( (digit_codes[d] & status_codes[i]) == status_codes[i]){
                count++;
            }
        }
        if(count == 0){
            total = 0;
            break;
        }
        total *= count;
    }
    
    printf("%lld\n", total);
    return 0;
}