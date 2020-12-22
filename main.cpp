#include <iostream>
#include "Algorithms.h"

using namespace std;

int main() {
    const string K = "F1A7C7F4B875D14B0D6F145CA4C4B53D";
    const string N = "54DA1F5AF3E882AFA6D32830D3";
    const string M = "AD5F724C5F67D0FA453F";

    cout << "Исходная строка\n " << M << '\n';
    string encrypted = ocb_encrypt(K, N, M);
    cout << "Зашифровання строка:\n " << encrypted << '\n';
    string decrypted = ocb_decrypt(K, N, encrypted);
    cout << "Дешифрованная строка\n " << decrypted << '\n';

}
