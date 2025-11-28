#include <iostream>

#include "osRandomProvider.hpp"
#include "pbkdf2.hpp"
#include "aes256GcmCipher.hpp"
#include "securityModule.hpp"

int main() {
    securityModule service(
        std::make_unique<pbkdf2>(16, 32, 200000),
        std::make_unique<osRandomProvider>(),
        std::make_unique<aes256GcmCipher>()
    );

    const std::string passwd = "strong-passphrase1";

    // 1) Encrypt
    try {
        service.encryptFile("netflix_titles.csv", "netflix_titles.enc", passwd);
    } catch (const std::exception& e) {
        std::cerr << "Encryption error: " << e.what() << "\n";
        return 1;
    }

    // 2) Integrity check
    if (!service.verifyIntegrity("netflix_titles.enc", passwd)) {
        std::cerr << "Integrity FAIL: wrong password or corrupted file.\n";
        return 2;
    }

    // 3) Decrypt
    try {
        service.decryptFile("netflix_titles.enc", "netflix_titles_dec.csv", passwd);
    } catch (const std::exception& e) {
        std::cerr << "Decryption error: " << e.what() << "\n";
        return 3;
    }

    std::cout << "Done\n";
    return 0;
}