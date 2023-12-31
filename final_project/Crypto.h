#ifndef CRYPTO_H
#define CRYPTO_H

#include <openssl/aes.h>
#include <openssl/rand.h>
#include <iostream>

#include <vector>
#include <string>

using namespace std;

class Crypto {
public:
    string aesEncrypt(const std::string& plaintext);
    string aesDecrypt(const std::string& ciphertextWithKey);
};

#endif  