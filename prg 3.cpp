#include <stdio.h>
#include <string.h>
#include <ctype.h>


void prepareKey(char key[], char matrix[5][5]) {
    int i, j, k;
    int keyLen = strlen(key);
    char keyAdjusted[26] = {0}; 
    int row = 0, col = 0;

   
    for (i = 0; i < keyLen; ++i) {
        if (key[i] == 'j')
            key[i] = 'i'; 
        if (!isalpha(key[i]))
            continue;
        if (keyAdjusted[key[i] - 'a'])
            continue; 
        matrix[row][col] = key[i];
        keyAdjusted[key[i] - 'a'] = 1;
        col++;
        if (col == 5) {
            col = 0;
            row++;
        }
    }

    
    for (k = 0; k < 26; ++k) {
        char ch = 'a' + k;
        if (ch == 'j') 
            continue;
        if (keyAdjusted[k])
            continue; 
        matrix[row][col] = ch;
        col++;
        if (col == 5) {
            col = 0;
            row++;
        }
    }
}


void findPosition(char matrix[5][5], char ch, int *row, int *col) {
    int i, j;
    for (i = 0; i < 5; ++i) {
        for (j = 0; j < 5; ++j) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}


void encryptPair(char matrix[5][5], char ch1, char ch2, char encryptedPair[2]) {
    int row1, col1, row2, col2;k

    findPosition(matrix, ch1, &row1, &col1);
    findPosition(matrix, ch2, &row2, &col2);

    if (row1 == row2) { 
        encryptedPair[0] = matrix[row1][(col1 + 1) % 5];
        encryptedPair[1] = matrix[row2][(col2 + 1) % 5];
    } else if (col1 == col2) { 
        encryptedPair[0] = matrix[(row1 + 1) % 5][col1];
        encryptedPair[1] = matrix[(row2 + 1) % 5][col2];
    } else { 
        encryptedPair[0] = matrix[row1][col2];
        encryptedPair[1] = matrix[row2][col1];
    }
}


void encryptPlayfair(char matrix[5][5], char plaintext[]) {
    int i, j;
    int len = strlen(plaintext);
    char encryptedText[100] = {0};
    int index = 0;

    for (i = 0; i < len; i += 2) {
        char ch1 = plaintext[i];
        char ch2 = (i + 1 < len) ? plaintext[i + 1] : 'x';
        char encryptedPair[2];

       
        encryptPair(matrix, ch1, ch2, encryptedPair);

       
        encryptedText[index++] = encryptedPair[0];
        encryptedText[index++] = encryptedPair[1];
    }

    printf("Encrypted text: %s\n", encryptedText);
}

int main() {
    char key[100];
    char plaintext[100];
    char matrix[5][5] = {{0}}; 
    printf("Enter the key: ");
    scanf("%s", key);

    printf("Enter the plaintext: ");
    scanf("%s", plaintext);

    prepareKey(key, matrix);

    encryptPlayfair(matrix, plaintext);

    return 0;
}
