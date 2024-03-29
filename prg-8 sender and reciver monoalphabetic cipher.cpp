#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26


void generate_cipher_sequence(const char *keyword, char *cipher_sequence) {
    int keyword_length = strlen(keyword);
    int index = 0;

   
    strcpy(cipher_sequence, keyword);
    index += keyword_length;

    
    for (char c = 'A'; c <= 'Z'; c++) {
        if (!strchr(keyword, toupper(c))) {
            cipher_sequence[index++] = c;
        }
    }
    cipher_sequence[index] = '\0';
}


void encrypt(const char *plaintext, const char *cipher_sequence, char *ciphertext) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char c = plaintext[i];
        if (isalpha(c)) {
            if (islower(c)) {
                ciphertext[i] = tolower(cipher_sequence[c - 'a']);
            } else {
                ciphertext[i] = toupper(cipher_sequence[c - 'A']);
            }
        } else {
            ciphertext[i] = c;
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}


void decrypt(const char *ciphertext, const char *cipher_sequence, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char c = ciphertext[i];
        if (isalpha(c)) {
            if (islower(c)) {
                plaintext[i] = 'a' + (strchr(cipher_sequence, c) - cipher_sequence);
            } else {
                plaintext[i] = 'A' + (strchr(cipher_sequence, tolower(c)) - cipher_sequence);
            }
        } else {
            plaintext[i] = c;
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    char keyword[] = "CIPHER";
    char plaintext[] = "HELLO";
    char cipher_sequence[ALPHABET_SIZE + 1];
    char ciphertext[strlen(plaintext) + 1];
    char decrypted_plaintext[strlen(plaintext) + 1];

    
    generate_cipher_sequence(keyword, cipher_sequence);

   
    encrypt(plaintext, cipher_sequence, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);

   
    decrypt(ciphertext, cipher_sequence, decrypted_plaintext);
    printf("Decrypted text: %s\n", decrypted_plaintext);

    return 0;
}
