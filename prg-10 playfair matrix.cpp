#include <stdio.h>
#include <string.h>
#include <ctype.h>


void preprocessPlaintext(const char *plaintext, char *processedText) {
    int j = 0;
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            processedText[j++] = toupper(plaintext[i]);
        }
    }
    processedText[j] = '\0';
}


void findPosition(char keyMatrix[5][5], char ch, int *row, int *col) {
    if (ch == 'J') 
        ch = 'I';

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (keyMatrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}


void encryptPlayfair(const char *plaintext, char keyMatrix[5][5]) {
    char processedText[100]; 
    char encryptedText[100];

    preprocessPlaintext(plaintext, processedText);

    int len = strlen(processedText);
    int pos1_row, pos1_col, pos2_row, pos2_col;

    for (int i = 0; i < len; i += 2) {
        char c1 = processedText[i];
        char c2 = (i + 1 < len) ? processedText[i + 1] : 'X'; 

        findPosition(keyMatrix, c1, &pos1_row, &pos1_col);
        findPosition(keyMatrix, c2, &pos2_row, &pos2_col);

        if (pos1_row == pos2_row) {
            encryptedText[i] = keyMatrix[pos1_row][(pos1_col + 1) % 5];
            encryptedText[i + 1] = keyMatrix[pos2_row][(pos2_col + 1) % 5];
        } else if (pos1_col == pos2_col) {
            encryptedText[i] = keyMatrix[(pos1_row + 1) % 5][pos1_col];
            encryptedText[i + 1] = keyMatrix[(pos2_row + 1) % 5][pos2_col];
        } else {
            encryptedText[i] = keyMatrix[pos1_row][pos2_col];
            encryptedText[i + 1] = keyMatrix[pos2_row][pos1_col];
        }
    }

    encryptedText[len] = '\0';
    printf("Encrypted message: %s\n", encryptedText);
}

int main() {
    char keyMatrix[5][5] = {
        {'M', 'F', 'H', 'I', 'K'},
        {'U', 'N', 'O', 'P', 'Q'},
        {'Z', 'V', 'W', 'X', 'Y'},
        {'E', 'L', 'A', 'R', 'G'},
        {'D', 'S', 'T', 'B', 'C'}
    };

    char plaintext[] = "Must see you over Cadogan West. Coming at once.";

    encryptPlayfair(plaintext, keyMatrix);

    return 0;
}
