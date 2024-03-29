#include <stdio.h>
#include <string.h>
#include <ctype.h>


void decryptPlayfair(const char *cipherText, const char keyMatrix[5][5]) {
    char decryptedText[strlen(cipherText)];

    int row1, col1, row2, col2;

    for (int i = 0; i < strlen(cipherText); i += 2) {
        char c1 = toupper(cipherText[i]);
        char c2 = toupper(cipherText[i + 1]);

       
        for (int row = 0; row < 5; row++) {
            for (int col = 0; col < 5; col++) {
                if (keyMatrix[row][col] == c1) {
                    row1 = row;
                    col1 = col;
                }
                if (keyMatrix[row][col] == c2) {
                    row2 = row;
                    col2 = col;
                }
            }
        }

        
        if (row1 == row2) {
            decryptedText[i] = keyMatrix[row1][(col1 + 4) % 5];
            decryptedText[i + 1] = keyMatrix[row2][(col2 + 4) % 5];
        }
        
        else if (col1 == col2) {
            decryptedText[i] = keyMatrix[(row1 + 4) % 5][col1];
            decryptedText[i + 1] = keyMatrix[(row2 + 4) % 5][col2];
        }
        
        else {
            decryptedText[i] = keyMatrix[row1][col2];
            decryptedText[i + 1] = keyMatrix[row2][col1];
        }
    }

    decryptedText[strlen(cipherText)] = '\0';
    printf("Decrypted message: %s\n", decryptedText);
}

int main() {
    const char keyMatrix[5][5] = {
        {'K', 'X', 'J', 'E', 'Y'},
        {'U', 'R', 'E', 'B', 'Z'},
        {'W', 'H', 'F', 'S', 'G'},
        {'O', 'I', 'T', 'L', 'C'},
        {'A', 'P', 'D', 'N', 'Q'}
    };

    const char cipherText[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONEYCUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";

    decryptPlayfair(cipherText, keyMatrix);

    return 0;
}
