#include "present.h" 
#include "files.h"

int main() {
    try {
        int choice;

        cout << " PRESENT Cipher \n";
        cout << "1 - Encrypt file\n";
        cout << "2 - Decrypt file\n";
        cout << "Choice: ";
        cin >> choice;

        string inputFile, outputFile, keyFile;

        cout << "Input file: ";
        cin >> inputFile;

        cout << "Output file: ";
        cin >> outputFile;

        cout << "Key file: ";
        cin >> keyFile;

        if (choice == 1) {
            encryptFile(inputFile, outputFile, keyFile);
        }
        else if (choice == 2) {
            decryptFile(inputFile, outputFile, keyFile);
        }
        else {
           cout << "Invalid choice!\n";
        }

    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << "\n";
    }

    return 0;
}