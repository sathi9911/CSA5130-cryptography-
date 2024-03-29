#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26


void calculate_letter_frequency(const char *text, int frequency[]) {
    int i;
    for (i = 0; i < strlen(text); i++) {
        char c = text[i];
        if (c >= 'a' && c <= 'z') {
            frequency[c - 'a']++;
        } else if (c >= 'A' && c <= 'Z') {
            frequency[c - 'A']++;
        }
    }
}


void decrypt_text(const char *text, int key, char *decrypted_text) {
    int i;
    for (i = 0; i < strlen(text); i++) {
        char c = text[i];
        if (c >= 'a' && c <= 'z') {
            decrypted_text[i] = ((c - 'a' - key + ALPHABET_SIZE) % ALPHABET_SIZE) + 'a';
        } else if (c >= 'A' && c <= 'Z') {
            decrypted_text[i] = ((c - 'A' - key + ALPHABET_SIZE) % ALPHABET_SIZE) + 'A';
        } else {
            decrypted_text[i] = c; 
        }
    }
    decrypted_text[i] = '\0';
}


void find_top_plaintexts(const char *ciphertext, int top_count) {
    int frequency[ALPHABET_SIZE] = {0};
    int i, j;

    
    calculate_letter_frequency(ciphertext, frequency);

    
    int max_frequency = frequency[0];
    int max_index = 0;
    for (i = 1; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > max_frequency) {
            max_frequency = frequency[i];
            max_index = i;
        }
    }

    
    int key = (max_index - ('e' - 'a') + ALPHABET_SIZE) % ALPHABET_SIZE;

    
    char decrypted_text[strlen(ciphertext) + 1];
    decrypt_text(ciphertext, key, decrypted_text);

   
    printf("Top %d possible plaintexts:\n", top_count);
    for (i = 0; i < top_count; i++) {
        printf("%d. %s\n", i + 1, decrypted_text);
        
        key = (key + 1) % ALPHABET_SIZE;
        decrypt_text(ciphertext, key, decrypted_text);
    }
}

int main() {
    char ciphertext[1000]; 
    int top_count;

   
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; 

   
    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &top_count);

   
    find_top_plaintexts(ciphertext, top_count);

    return 0;
}
