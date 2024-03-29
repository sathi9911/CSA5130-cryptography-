#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/dsa.h>
#include <openssl/sha.h>


DSA* generate_dsa_keypair() {
    DSA *dsa = DSA_new();
    if (!DSA_generate_parameters_ex(dsa, 1024, NULL, 0, NULL, NULL, NULL)) {
        printf("Error generating DSA parameters\n");
        return NULL;
    }
    if (!DSA_generate_key(dsa)) {
        printf("Error generating DSA key pair\n");
        return NULL;
    }
    return dsa;
}


unsigned char* dsa_sign(const unsigned char* msg, int msg_len, DSA* dsa) {
    DSA_SIG *sig = DSA_do_sign(msg, msg_len, dsa);
    if (sig == NULL) {
        printf("Error signing message\n");
        return NULL;
    }
    unsigned char* signature = (unsigned char*)malloc(DSA_size(dsa));
    unsigned int sig_len;
    if (!DSA_SIG_get0(sig, (const BIGNUM**)&signature, (const BIGNUM**)&signature)) {
        printf("Error extracting signature components\n");
        return NULL;
    }
    return signature;
}


int dsa_verify(const unsigned char* msg, int msg_len, unsigned char* signature, int sig_len, DSA* dsa) {
    DSA_SIG *sig = DSA_SIG_new();
    if (!DSA_SIG_set0(sig, (BIGNUM*)signature, (BIGNUM*)(signature + sig_len))) {
        printf("Error setting signature components\n");
        return 0;
    }
    int result = DSA_do_verify(msg, msg_len, sig, dsa);
    DSA_SIG_free(sig);
    return result;
}

int main() {
   
    DSA* dsa_keypair = generate_dsa_keypair();
    if (dsa_keypair == NULL) {
        printf("Error generating DSA key pair\n");
        return 1;
    }

   
    const char* msg1 = "Hello, world!";
    const char* msg2 = "Hello, world!";

    
    unsigned char* signature1 = dsa_sign((unsigned char*)msg1, strlen(msg1), dsa_keypair);
    if (signature1 == NULL) {
        printf("Error signing message\n");
        return 1;
    }

    
    unsigned char* signature2 = dsa_sign((unsigned char*)msg2, strlen(msg2), dsa_keypair);
    if (signature2 == NULL) {
        printf("Error signing message\n");
        return 1;
    }

    
    int verified1 = dsa_verify((unsigned char*)msg1, strlen(msg1), signature1, DSA_size(dsa_keypair), dsa_keypair);
    int verified2 = dsa_verify((unsigned char*)msg2, strlen(msg2), signature2, DSA_size(dsa_keypair), dsa_keypair);

    if (verified1 == 1 && verified2 == 1) {
        printf("DSA signatures verified successfully\n");
    } else {
        printf("DSA signatures verification failed\n");
    }

   
    DSA_free(dsa_keypair);
    free(signature1);
    free(signature2);

    return 0;
}
