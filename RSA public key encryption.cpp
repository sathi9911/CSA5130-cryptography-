#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}


int generate_e(int phi) {
    int e = 2;
    while (e < phi) {
        if (gcd(e, phi) == 1)
            break;
        e++;
    }
    return e;
}


int generate_d(int e, int phi) {
    int k = 1;
    while (1) {
        if ((k * phi + 1) % e == 0)
            return (k * phi + 1) / e;
        k++;
    }
}


long long mod_exp(long long base, int exponent, int modulus) {
    long long result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent & 1)
            result = (result * base) % modulus;
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}


long long encrypt(long long msg, int e, int n) {
    return mod_exp(msg, e, n);
}


long long decrypt(long long cipher, int d, int n) {
    return mod_exp(cipher, d, n);
}

int main() {
   
    int p = 61; 
    int q = 53; 
    int n = p * q; 
    int phi = (p - 1) * (q - 1); 
    int e = generate_e(phi); 
    int d = generate_d(e, phi); 

    
    long long msg = 123456789;

    
    long long encrypted_msg = encrypt(msg, e, n);
    printf("Encrypted message: %lld\n", encrypted_msg);

    
    long long decrypted_msg = decrypt(encrypted_msg, d, n);
    printf("Decrypted message: %lld\n", decrypted_msg);

    return 0;
}
