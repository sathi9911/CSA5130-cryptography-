#include <stdio.h>
#include <string.h>
#include <ctype.h>


void encrypt(char message[], char key[]) {
    int i;
    char encrypted_message[100];

    for (i = 0; message[i] != '\0'; ++i) {
        if (isalpha(message[i])) {
            if (islower(message[i])) {
                encrypted_message[i] = key[message[i] - 'a'];
            } else {
                encrypted_message[i] = toupper(key[message[i] - 'A']);
            }
        } else {
            encrypted_message[i] = message[i];
        }
    }

    encrypted_message[i] = '\0';

    printf("Encrypted message: %s\n", encrypted_message);
}

int main() {
    char message[100];
    char key[26];

    printf("Enter a message to encrypt: ");
    fgets(message, sizeof(message), stdin);

    
    message[strcspn(message, "\n")] = '\0';

    printf("Enter the key (26 letters): ");
    fgets(key, sizeof(key), stdin);

  
    key[strcspn(key, "\n")] = '\0';

    if (strlen(key) != 26) {
        printf("Error: Key must be exactly 26 letters long.\n");
        return 1;
    }

   
    int used[26] = {0};
    for (int i = 0; i < 26; ++i) {
        if (!isalpha(key[i])) {
            printf("Error: Key must contain only alphabetic characters.\n");
            return 1;
        }
        int index = tolower(key[i]) - 'a';
        if (used[index]) {
            printf("Error: Key must contain each letter exactly once.\n");
            return 1;
        }
        used[index] = 1;
    }

    encrypt(message, key);

    return 0;
}
