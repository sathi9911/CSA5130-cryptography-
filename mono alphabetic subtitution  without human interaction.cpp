#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26


const float english_frequencies[ALPHABET_SIZE] = {
    0.0817, 0.0149, 0.0278, 0.0425, 0.1270, 0.0223, 0.0202, 0.0609,
    0.0697, 0.0015, 0.0077, 0.0403, 0.0241, 0.0675, 0.0751, 0.0193,
    0.0010, 0.0599, 0.0633, 0.0906, 0.0276, 0.0098, 0.0236, 0.0015,
    0.0197, 0.0007
};


void count_letter_frequencies(const char *text, int *frequencies) {
    for (int i = 0; text[i] != '\0'; i++) {
        char c = text[i];
        if (isalpha(c)) {
            frequencies[tolower(c) - 'a']++;
        }
    }
}


void decrypt(const char *ciphertext, const char *key) {
    printf("Plaintext with key '%s': ", key);
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char c = ciphertext[i];
        if (isalpha(c)) {
            char decrypted_char = islower(c) ? tolower(key[c - 'a']) : toupper(key[c - 'A']);
            printf("%c", decrypted_char);
        } else {
            printf("%c", c);
        }
    }
    printf("\n");
}


float score_text(const int *frequencies) {
    float score = 0.0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        score += english_frequencies[i] * frequencies[i];
    }
    return score;
}


void frequency_attack(const char *ciphertext) {
    int ciphertext_frequencies[ALPHABET_SIZE] = {0};
    count_letter_frequencies(ciphertext, ciphertext_frequencies);

    int sorted_indices[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        sorted_indices[i] = i;
    }

    
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (ciphertext_frequencies[sorted_indices[i]] < ciphertext_frequencies[sorted_indices[j]]) {
                int temp = sorted_indices[i];
                sorted_indices[i] = sorted_indices[j];
                sorted_indices[j] = temp;
            }
        }
    }

   
    char key[ALPHABET_SIZE + 1];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        key[sorted_indices[i]] = 'A' + i;
    }
    key[ALPHABET_SIZE] = '\0';

    decrypt(ciphertext, key);
}

int main() {
    char ciphertext[1000]; 
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; 
    printf("Possible plaintexts in rough order of likelihood:\n");
    frequency_attack(ciphertext);

    return 0;
}
