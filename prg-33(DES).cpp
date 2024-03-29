#include <stdio.h>
#include <string.h>
#include <openssl/des.h>


void des_encrypt(const unsigned char *plaintext, const unsigned char *key, unsigned char *ciphertext) {
    DES_key_schedule schedule;
    DES_set_key((const_DES_cblock *)key, &schedule);
    DES_ecb_encrypt((const_DES_cblock *)plaintext, (DES_cblock *)ciphertext, &schedule, DES_ENCRYPT);
}


void des_decrypt(const unsigned char *ciphertext, const unsigned char *key, unsigned char *plaintext) {
    DES_key_schedule schedule;
    DES_set_key((const_DES_cblock *)key, &schedule);
    DES_ecb_encrypt((const_DES_cblock *)ciphertext, (DES_cblock *)plaintext, &schedule, DES_DECRYPT);
}

int main() {
   
    unsigned char plaintext[] = "Hello, world!";
    unsigned char key[8] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1}; // 56-bit key

   
    unsigned char ciphertext[64];

    
    unsigned char decrypted_plaintext[64];

   
    des_encrypt(plaintext, key, ciphertext);

    
    printf("Ciphertext: ");
    for (int i = 0; i < 8; i++) {
        printf("%02X", ciphertext[i]);
    }
    printf("\n");

    
    des_decrypt(ciphertext, key, decrypted_plaintext);

   
    printf("Decrypted plaintext: %s\n", decrypted_plaintext);

    return 0;
}
