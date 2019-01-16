#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VALUE 255
using namespace std;

const char* alphabet = "abcdefghijklmnopqrstuvwxyz";

struct position {
	int x;
	int y;
	int z;
};

void ShowMatrix(char matrix[100][100])
{
	int i, j;
	for (i = 0; i < 100; ++i)
	{
		for (j = 0; j < 100; ++j)
		{
			if (matrix[i][j] != '9') {
				cout << matrix[i][j];
			}
			else {
				break;
			}
		}
		cout << "\n";
		if (matrix[i + 1][0] == '9') {
			break;
		}
	}
	cout << "\n";
}


void AddMatrixPassword(char matrix[100][100], char key[])
{
	int i;
	for (i = 0; i < 100; ++i)
	{
		if (i < strlen(key)) {
			matrix[0][i] = key[i];
		}
		else {
			break;
		}
	}
}

struct position CheckPosition(char letter, char matrixAlphabet[100][100])
{
	int i, j;
	struct position letterposition;

	for (i = 0; i < 9; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			if (matrixAlphabet[i][j] == letter)
			{
				letterposition.x = i % 3 + 1;
				letterposition.y = j + 1;
				if (i < 3)
				{
					letterposition.z = 1;
				}
				else if (i < 6)
				{
					letterposition.z = 2;
				}
				else letterposition.z = 3;

				return letterposition;

			}
		}
	}
	struct position letterposition1;
	letterposition1.x = 10;
	letterposition1.y = 10;
	letterposition1.z = 10;
	return letterposition1;
}

void DeleteDuplicateLetters(char text[])
{
	int i, j, k;
	int lungimeText = strlen(text);
	for (i = 0; i < lungimeText; ++i)
	{
		for (j = i + 1; text[j] != '\0'; ++j)
		{
			if (text[j] == text[i])
			{
				for (k = j; text[k] != '\0'; ++k)
				{
					if (text[k] == text[k + 1])
					{
						j -= 1;
					}
					text[k] = text[k + 1];
				}
			}
		}
	}
}

void AddMatrixAlphabet(char matrix[100][100], char key[])
{
	int i, j, k = 0;
	for (i = 0; i < 100; ++i)
	{
		for (j = 0; j < 3; j++) {
			matrix[i][j] = key[k];
			k++;
			if (k > strlen(key))
			{
				i = j = 100;
			}
		}
	}
}

void InitiateMatrix(char matrix[100][100])
{
	int i, j;
	for (i = 0; i < 100; ++i)
	{
		for (j = 0; j < 100; ++j)
		{
			matrix[i][j] = '9';
		}
	}
}

void AddMatrixLettersPosition(char matrixCipher[100][100], char matrixAlphabet[100][100], int textLenght)
{
	int i;
	for (i = 0; i < textLenght; ++i)
	{
		struct position pos = CheckPosition(matrixCipher[0][i], matrixAlphabet);

		matrixCipher[1][i] = pos.z + '0';
		matrixCipher[2][i] = pos.x + '0';
		matrixCipher[3][i] = pos.y + '0';
	}

	int table;
	int line;
	int column;
	int k = -5;
	char var;
	for (i = 0; i < textLenght; ++i)
	{
		if (i % 5 == 0)
		{
			k += 5;
		}
		switch (i % 5)
		{
		case 0:
			table = matrixCipher[1][k + 0] - '0';
			line = matrixCipher[1][k + 1] - '0';
			column = matrixCipher[1][k + 2] - '0';
			var = matrixAlphabet[line - 1 + ((table - 1) * 3)][column - 1];
			matrixCipher[4][i] = var;
			break;
		case 1:
			table = matrixCipher[1][k + 3] - '0';
			line = matrixCipher[1][k + 4] - '0';
			column = matrixCipher[2][k + 0] - '0';
			var = matrixAlphabet[line - 1 + ((table - 1) * 3)][column - 1];
			matrixCipher[4][i] = var;
			break;
		case 2:
			table = matrixCipher[2][k + 1] - '0';
			line = matrixCipher[2][k + 2] - '0';
			column = matrixCipher[2][k + 3] - '0';
			var = matrixAlphabet[line - 1 + ((table - 1) * 3)][column - 1];
			matrixCipher[4][i] = var;
			break;
		case 3:
			table = matrixCipher[2][k + 4] - '0';
			line = matrixCipher[3][k + 0] - '0';
			column = matrixCipher[3][k + 1] - '0';
			var = matrixAlphabet[line - 1 + ((table - 1) * 3)][column - 1];
			matrixCipher[4][i] = var;
			break;
		case 4:
			table = matrixCipher[3][k + 2] - '0';
			line = matrixCipher[3][k + 3] - '0';
			column = matrixCipher[3][k + 4] - '0';
			var = matrixAlphabet[line - 1 + ((table - 1) * 3)][column - 1];
			matrixCipher[4][i] = var;
			break;
		default:
			cout << "Error";
			break;
		}
	}
}


void Criptare(char text[], char key[])
{
	char matrixAlphabet[100][100];
	char newKey[100] = "";

	strcat(newKey, key);

	InitiateMatrix(matrixAlphabet);
	strcat(newKey, alphabet);
	DeleteDuplicateLetters(newKey);

	AddMatrixAlphabet(matrixAlphabet, newKey);
	ShowMatrix(matrixAlphabet);

	char matrixCipher[100][100];
	InitiateMatrix(matrixCipher);

	AddMatrixPassword(matrixCipher, text);
	AddMatrixLettersPosition(matrixCipher, matrixAlphabet, strlen(key));

	ShowMatrix(matrixCipher);

}

void DecryptionMatrixLetterPosition(char matrixCipher[100][100], char matrixAlphabet[100][100], int textLenght)
{
	int i;
	int k = -5;
	for (i = 0; i < textLenght; ++i)
	{
		struct position pos = CheckPosition(matrixCipher[0][i], matrixAlphabet);

		if (i % 5 == 0)
		{
			k += 5;
		}
		switch (i % 5)
		{
		case 0:
			matrixCipher[1][k + 0] = pos.z + '0';
			matrixCipher[1][k + 1] = pos.x + '0';
			matrixCipher[1][k + 2] = pos.y + '0';
			break;
		case 1:
			matrixCipher[1][k + 3] = pos.z + '0';
			matrixCipher[1][k + 4] = pos.x + '0';
			matrixCipher[2][k + 0] = pos.y + '0';
			break;
		case 2:
			matrixCipher[2][k + 1] = pos.z + '0';
			matrixCipher[2][k + 2] = pos.x + '0';
			matrixCipher[2][k + 3] = pos.y + '0';
			break;
		case 3:
			matrixCipher[2][k + 4] = pos.z + '0';
			matrixCipher[3][k + 0] = pos.x + '0';
			matrixCipher[3][k + 1] = pos.y + '0';
			break;
		case 4:
			matrixCipher[3][k + 2] = pos.z + '0';
			matrixCipher[3][k + 3] = pos.x + '0';
			matrixCipher[3][k + 4] = pos.y + '0';
			break;
		default:
			cout << "Error";
			break;
		}
	}
	int currentTable;
	int currentLine;
	int currentColumn;


	for (i = 0; i < textLenght; ++i)
	{
		currentTable = matrixCipher[1][i] - '0';
		currentLine = matrixCipher[2][i] - '0';
		currentColumn = matrixCipher[3][i] - '0';
		char letter = matrixAlphabet[currentLine - 1 + ((currentTable - 1) * 3)][currentColumn - 1];
		matrixCipher[4][i] = letter;
	}
}

void Decriptare(char text[], char key[])
{
	char matrixAlphabet[100][100];
	char newKey[100] = "";

	strcat(newKey, key);

	InitiateMatrix(matrixAlphabet);
	strcat(newKey, alphabet);
	DeleteDuplicateLetters(newKey);

	AddMatrixAlphabet(matrixAlphabet, newKey);
	ShowMatrix(matrixAlphabet);

	char matrixCipher[100][100];
	InitiateMatrix(matrixCipher);

	AddMatrixPassword(matrixCipher, text);
	DecryptionMatrixLetterPosition(matrixCipher, matrixAlphabet, strlen(key));

	ShowMatrix(matrixCipher);

}



int main()
{
	int option;
	char key[100];
	char text[100];
	while (1)
	{
		cout << "\nTrifid Cipher \n";
		cout << "\nChoose an option: \n";
		cout << "1. Encrypt \n";
		cout << "2. Decrypt \n";
		cin >> option;
		switch (option)
		{
		case 1:
			cout << "Plaintext: ";
			cin >> text, sizeof(text);
			cout << "Key: ";
			cin >> key, sizeof(key);
			Criptare(text, key);
			break;
		case 2:
			cout << "Ciphertext: ";
			cin >> text, sizeof(text);
			cout << "Key: ";
			cin >> key, sizeof(key);
			Decriptare(text, key);
			break;
		default:
			cout << "Please, choose 1 or 2";
			break;
		}
	}
	return 0;
}