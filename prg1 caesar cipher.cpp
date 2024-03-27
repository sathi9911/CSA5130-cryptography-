#include <stdio.h>
#include <string.h>


void encrypt(char message[], int key) {
    int i;
    char encrypted_message[100];

    for (i = 0; message[i] != '\0'; ++i) {
        if (message[i] >= 'a' && message[i] <= 'z') {
            encrypted_message[i] = 'a' + (message[i] - 'a' + key) % 26;
        } else if (message[i] >= 'A' && message[i] <= 'Z') {
            encrypted_message[i] = 'A' + (message[i] - 'A' + key) % 26;
        } else {
            encrypted_message[i] = message[i];
        }
    }

    encrypted_message[i] = '\0';

    printf("Encrypted message with key %d: %s\n", key, encrypted_message);
}


void decrypt(char message[], int key) {
    int i;
    char decrypted_message[100];

    for (i = 0; message[i] != '\0'; ++i) {
        if (message[i] >= 'a' && message[i] <= 'z') {
            decrypted_message[i] = 'a' + (message[i] - 'a' - key + 26) % 26;
        } else if (message[i] >= 'A' && message[i] <= 'Z') {
            decrypted_message[i] = 'A' + (message[i] - 'A' - key + 26) % 26;
        } else {
            decrypted_message[i] = message[i];
        }
    }

    decrypted_message[i] = '\0';

    printf("Decrypted message with key %d: %s\n", key, decrypted_message);
}

int main() {
    char message[100];
    int key;

    printf("Enter a message to encrypt: ");
    fgets(message, sizeof(message), stdin);

    
    message[strcspn(message, "\n")] = 0;

    printf("Enter a key value (1-25): ");
    scanf("%d", &key);

    encrypt(message, key);
    decrypt(message, key);

    return 0;
}
