#include <stdio.h>


int find_multiplicative_inverse(int n) {
    for (int i = 1; i < 26; i++) {
        if ((n * i) % 26 == 1) {
            return i;
        }
    }
    return -1; 
}


void decrypt_affine_cipher(const char *ciphertext, int a, int b) {
    printf("Decrypted plaintext:\n");
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char c = ciphertext[i];
        if (c >= 'A' && c <= 'Z') {
            int x = c - 'A';
            int x_inv = find_multiplicative_inverse(a);
            int decrypted_char = (x_inv * (x - b + 26)) % 26;
            printf("%c", 'A' + decrypted_char);
        } else if (c >= 'a' && c <= 'z') {
            int x = c - 'a';
            int x_inv = find_multiplicative_inverse(a);
            int decrypted_char = (x_inv * (x - b + 26)) % 26;
            printf("%c", 'a' + decrypted_char);
        } else {
            printf("%c", c);
        }
    }
    printf("\n");
}

int main() {
    char ciphertext[1000]; 
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    
    
    int freq[26] = {0};
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char c = ciphertext[i];
        if (c >= 'A' && c <= 'Z') {
            freq[c - 'A']++;
        } else if (c >= 'a' && c <= 'z') {
            freq[c - 'a']++;
        }
    }
    
    
    int max_freq = 0, second_max_freq = 0;
    char max_char = '\0', second_max_char = '\0';
    for (int i = 0; i < 26; i++) {
        if (freq[i] > max_freq) {
            second_max_freq = max_freq;
            second_max_char = max_char;
            max_freq = freq[i];
            max_char = 'A' + i;
        } else if (freq[i] > second_max_freq) {
            second_max_freq = freq[i];
            second_max_char = 'A' + i;
        }
    }
    
    
    int a, b;
    
    a = ((4 - (max_char - 'A')) * find_multiplicative_inverse(max_char - 'A')) % 26;
    if (a < 0) {
        a += 26;
    }
    b = (21 - ('E' - 'A') * a) % 26;
    if (b < 0) {
        b += 26;
    }
    
    
    decrypt_affine_cipher(ciphertext, a, b);
    
    return 0;
}
