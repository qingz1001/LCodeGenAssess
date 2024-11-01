#include <stdio.h>
#include <string.h>

unsigned long long parse_binary(const char *s) {
    unsigned long long num = 0;
    for(int i = 0; i < 7; i++) {
        num = (num << 1) | (s[i] - '0');
    }
    return num;
}

int main(){
    // Define the state codes for digits 0-9
    unsigned long long digit_codes[10] = {
        parse_binary("1111110"), // 0
        parse_binary("0110000"), // 1
        parse_binary("1101101"), // 2
        parse_binary("1111001"), // 3
        parse_binary("0110011"), // 4
        parse_binary("1011011"), // 5
        parse_binary("1011111"), // 6
        parse_binary("1110000"), // 7
        parse_binary("1111111"), // 8
        parse_binary("1111011")  // 9
    };
    
    // Define the observed 18 state codes
    const char *observed_str[18] = {
        "0000011",
        "1001011",
        "0000001",
        "0100001",
        "0101011",
        "0110110",
        "1111111",
        "0010110",
        "0101001",
        "0010110",
        "1011100",
        "0100110",
        "1010000",
        "0010011",
        "0001111",
        "0101101",
        "0110101",
        "1101010"
    };
    
    unsigned long long observed_codes[18];
    for(int i = 0; i < 18; i++) {
        observed_codes[i] = parse_binary(observed_str[i]);
    }
    
    unsigned long long total = 1;
    for(int i = 0; i < 18; i++) {
        int count = 0;
        for(int d = 0; d < 10; d++) {
            if( (digit_codes[d] & observed_codes[i]) == observed_codes[i] ){
                count++;
            }
        }
        total *= count;
    }
    
    printf("%llu\n", total);
    return 0;
}