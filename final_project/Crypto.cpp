#include "Crypto.h"

// Function to perform AES encryption with key generation
string Crypto::aesEncrypt(const std::string& plaintext) {
    // Generate a random 256-bit key
    unsigned char key[AES_BLOCK_SIZE];
    RAND_bytes(key, AES_BLOCK_SIZE);

    // Perform AES encryption
    size_t plaintextSize = plaintext.size();
    std::vector<unsigned char> ciphertext(plaintextSize + AES_BLOCK_SIZE);

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, key, NULL);
    EVP_EncryptUpdate(ctx, ciphertext.data(), (int*)&plaintextSize, (const unsigned char*)plaintext.c_str(), plaintextSize);
    int ciphertextSizeFinal;
    EVP_EncryptFinal_ex(ctx, ciphertext.data() + plaintextSize, &ciphertextSizeFinal);

    // Return the key and encrypted text
    return std::string(key, key + AES_BLOCK_SIZE) + std::string(ciphertext.begin(), ciphertext.begin() + plaintextSize + ciphertextSizeFinal);
}

// Function to perform AES decryption with the provided key
string Crypto::aesDecrypt(const std::string& ciphertextWithKey) {
    // Extract the key from the input
    unsigned char key[AES_BLOCK_SIZE];
    std::copy(ciphertextWithKey.begin(), ciphertextWithKey.begin() + AES_BLOCK_SIZE, key);

    // Extract the ciphertext from the input
    std::string ciphertext(ciphertextWithKey.begin() + AES_BLOCK_SIZE, ciphertextWithKey.end());

    // Perform AES decryption
    size_t ciphertextSize = ciphertext.size();
    std::vector<unsigned char> decryptedText(ciphertextSize);

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, key, NULL);
    EVP_DecryptUpdate(ctx, decryptedText.data(), (int*)&ciphertextSize, (const unsigned char*)ciphertext.c_str(), ciphertextSize);
    int decryptedTextSizeFinal;
    EVP_DecryptFinal_ex(ctx, decryptedText.data() + ciphertextSize, &decryptedTextSizeFinal);

    // Return the decrypted text
    return std::string(decryptedText.begin(), decryptedText.begin() + ciphertextSize + decryptedTextSizeFinal);
}