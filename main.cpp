#include <iostream>
#include <cstdlib>

#include "osRandomProvider.hpp"
#include "pbkdf2.hpp"
#include "aes256GcmCipher.hpp"
#include "securityModule.hpp"

std::string getEnvPassword() {
    const char* p = std::getenv("DATASET_PASSPHRASE");
    if (!p) throw std::runtime_error("DATASET_PASSPHRASE not set");
    return std::string(p);
}

int main() {
    securityModule service(
        std::make_unique<pbkdf2>(16, 32, 200000),
        std::make_unique<osRandomProvider>(),
        std::make_unique<aes256GcmCipher>()
    );

    const std::string passwd = getEnvPassword();

    // 1) Encrypt
    // try {
    //     service.encryptFile("example/Dataset_2.zip", "example/Dataset_2.enc", passwd);
    // } catch (const std::exception& e) {
    //     std::cerr << "Encryption error: " << e.what() << "\n";
    //     return -1;
    // }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
    // 2) Integrity check
    if (!service.verifyIntegrity("example/Dataset_2.enc", passwd)) {
        std::cerr << "Integrity FAIL: wrong password or corrupted file.\n";
        return -1;
    }

    // 3) Decrypt
    try {
        service.decryptFile("example/Dataset_2.enc", "example/Dataset_2_dec.zip", passwd);
    } catch (const std::exception& e) {
        std::cerr << "Decryption error: " << e.what() << "\n";
        return -1;
    }

    std::cout << "Done\n";
    return 0;
}