#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 26

char a_str[MAX_N + 1], b_str[MAX_N + 1], c_str_input[MAX_N + 1];
int mapping_digits[26];
bool used_digits_flag[MAX_N];
int n;
bool success = false;

// Function to reverse a string in place
void reverse_str(char *str, int len) {
    for(int i=0;i<len/2;i++) {
        char temp = str[i];
        str[i] = str[len-1-i];
        str[len-1-i] = temp;
    }
}

bool recurse(int pos, int carry, int len) {
    if(pos == len){
        return carry == 0;
    }
    
    char la = a_str[pos];
    char lb = b_str[pos];
    char lc = c_str_input[pos];
    
    int ma = mapping_digits[la - 'A'];
    int mb = mapping_digits[lb - 'A'];
    int mc = mapping_digits[lc - 'A'];
    
    // Determine which letters need to be assigned
    bool a_fixed = (ma != -1);
    bool b_fixed = (mb != -1);
    bool c_fixed = (mc != -1);
    
    if(a_fixed && b_fixed && c_fixed){
        int total = ma + mb + carry;
        if(total % n != mc){
            return false;
        }
        int new_carry = total / n;
        return recurse(pos+1, new_carry, len);
    }
    
    // If two are fixed, assign the third
    if(a_fixed && b_fixed && !c_fixed){
        int total = ma + mb + carry;
        int required_c = total % n;
        int new_carry = total / n;
        if(required_c >= n) return false;
        if(used_digits_flag[required_c]) return false;
        mapping_digits[lc - 'A'] = required_c;
        used_digits_flag[required_c] = true;
        if(recurse(pos+1, new_carry, len)){
            return true;
        }
        mapping_digits[lc - 'A'] = -1;
        used_digits_flag[required_c] = false;
        return false;
    }
    
    if(a_fixed && !b_fixed && c_fixed){
        int total = ma + carry;
        int required_b = mc - total;
        if(required_b < 0) required_b += n;
        int new_carry = (ma + 0 + carry) / n;
        if((ma + 0 + carry) >= n){
            new_carry = 1;
        }
        else{
            new_carry = 0;
        }
        required_b = (mc - ma - carry + n) % n;
        if(required_b >= n) return false;
        if(used_digits_flag[required_b]) return false;
        mapping_digits[lb - 'A'] = required_b;
        used_digits_flag[required_b] = true;
        int temp_total = ma + required_b + carry;
        int temp_mc = temp_total % n;
        int temp_new_carry = temp_total / n;
        if(temp_mc != mc){
            mapping_digits[lb - 'A'] = -1;
            used_digits_flag[required_b] = false;
            return false;
        }
        if(recurse(pos+1, temp_new_carry, len)){
            return true;
        }
        mapping_digits[lb - 'A'] = -1;
        used_digits_flag[required_b] = false;
        return false;
    }
    
    if(!a_fixed && b_fixed && c_fixed){
        int total = mb + carry;
        int required_a = (mc - total + n) % n;
        if(required_a >= n) return false;
        if(used_digits_flag[required_a]) return false;
        mapping_digits[la - 'A'] = required_a;
        used_digits_flag[required_a] = true;
        int temp_total = required_a + mb + carry;
        int temp_mc = temp_total % n;
        int temp_new_carry = temp_total / n;
        if(temp_mc != mc){
            mapping_digits[la - 'A'] = -1;
            used_digits_flag[required_a] = false;
            return false;
        }
        if(recurse(pos+1, temp_new_carry, len)){
            return true;
        }
        mapping_digits[la - 'A'] = -1;
        used_digits_flag[required_a] = false;
        return false;
    }
    
    // If one is fixed
    if(a_fixed && !b_fixed && !c_fixed){
        for(int db=0; db<n; db++){
            if(!used_digits_flag[db]){
                int total = ma + db + carry;
                int required_c = total % n;
                if(required_c >= n) continue;
                if(used_digits_flag[required_c]) continue;
                mapping_digits[lb - 'A'] = db;
                mapping_digits[lc - 'A'] = required_c;
                used_digits_flag[db] = true;
                used_digits_flag[required_c] = true;
                if(recurse(pos+1, total / n, len)){
                    return true;
                }
                mapping_digits[lb - 'A'] = -1;
                mapping_digits[lc - 'A'] = -1;
                used_digits_flag[db] = false;
                used_digits_flag[required_c] = false;
            }
        }
        return false;
    }
    
    if(!a_fixed && b_fixed && !c_fixed){
        for(int da=0; da<n; da++){
            if(!used_digits_flag[da]){
                int total = da + mb + carry;
                int required_c = total % n;
                if(required_c >= n) continue;
                if(used_digits_flag[required_c]) continue;
                mapping_digits[la - 'A'] = da;
                mapping_digits[lc - 'A'] = required_c;
                used_digits_flag[da] = true;
                used_digits_flag[required_c] = true;
                if(recurse(pos+1, total / n, len)){
                    return true;
                }
                mapping_digits[la - 'A'] = -1;
                mapping_digits[lc - 'A'] = -1;
                used_digits_flag[da] = false;
                used_digits_flag[required_c] = false;
            }
        }
        return false;
    }
    
    if(!a_fixed && !b_fixed && c_fixed){
        for(int da=0; da<n; da++){
            if(!used_digits_flag[da]){
                for(int db=0; db<n; db++){
                    if(!used_digits_flag[db]){
                        int total = da + db + carry;
                        int required_c = total % n;
                        if(required_c != mc){
                            continue;
                        }
                        int carry_out = total / n;
                        mapping_digits[la - 'A'] = da;
                        mapping_digits[lb - 'A'] = db;
                        used_digits_flag[da] = true;
                        used_digits_flag[db] = true;
                        if(recurse(pos+1, carry_out, len)){
                            return true;
                        }
                        mapping_digits[la - 'A'] = -1;
                        mapping_digits[lb - 'A'] = -1;
                        used_digits_flag[da] = false;
                        used_digits_flag[db] = false;
                    }
                }
            }
        }
        return false;
    }
    
    // If none are fixed, assign a and b and determine c
    if(!a_fixed && !b_fixed && !c_fixed){
        for(int da=0; da<n; da++){
            if(!used_digits_flag[da]){
                mapping_digits[la - 'A'] = da;
                used_digits_flag[da] = true;
                for(int db=0; db<n; db++){
                    if(!used_digits_flag[db]){
                        mapping_digits[lb - 'A'] = db;
                        used_digits_flag[db] = true;
                        int total = da + db + carry;
                        int required_c = total % n;
                        int carry_out = total / n;
                        if(required_c < n && !used_digits_flag[required_c]){
                            mapping_digits[lc - 'A'] = required_c;
                            used_digits_flag[required_c] = true;
                            if(recurse(pos+1, carry_out, len)){
                                return true;
                            }
                            mapping_digits[lc - 'A'] = -1;
                            used_digits_flag[required_c] = false;
                        }
                        mapping_digits[lb - 'A'] = -1;
                        used_digits_flag[db] = false;
                    }
                }
                mapping_digits[la - 'A'] = -1;
                used_digits_flag[da] = false;
            }
        }
        return false;
    }
    
    // If two are fixed and one is not
    if(a_fixed && b_fixed && !c_fixed){
        int total = ma + mb + carry;
        int required_c = total % n;
        int carry_out = total / n;
        if(required_c >= n || used_digits_flag[required_c]){
            return false;
        }
        mapping_digits[lc - 'A'] = required_c;
        used_digits_flag[required_c] = true;
        if(recurse(pos+1, carry_out, len)){
            return true;
        }
        mapping_digits[lc - 'A'] = -1;
        used_digits_flag[required_c] = false;
        return false;
    }
    
    return false;
}

int main(){
    scanf("%d", &n);
    scanf("%s", a_str);
    scanf("%s", b_str);
    scanf("%s", c_str_input);
    
    int len = n;
    
    // Reverse the strings to process from least to most significant
    reverse_str(a_str, len);
    reverse_str(b_str, len);
    reverse_str(c_str_input, len);
    
    // Initialize mapping and used_digits
    for(int i=0;i<26;i++) mapping_digits[i] = -1;
    for(int i=0;i<n;i++) used_digits_flag[i] = false;
    
    // Collect all unique letters
    bool letters_present[26] = {false};
    for(int i=0;i<len;i++){
        letters_present[a_str[i]-'A'] = true;
        letters_present[b_str[i]-'A'] = true;
        letters_present[c_str_input[i]-'A'] = true;
    }
    
    // Initialize mapping with any letters that can be determined immediately
    // Not implemented here, proceed with backtracking
    
    if(recurse(0, 0, len)){
        // Collect and print the mapping in 'A' to 'Z' order
        bool first = true;
        for(char ch='A'; ch<='Z'; ch++){
            if(letters_present[ch-'A']){
                if(!first){
                    printf(" ");
                }
                printf("%d", mapping_digits[ch-'A']);
                first = false;
            }
        }
        printf("\n");
    }
    return 0;
}