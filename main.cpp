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

    service.encryptFile("netflix_titles.csv", "netflix_titles.enc", passwd);

    if (!service.verifyIntegrity("netflix_titles.enc", passwd)) {
         std::cout << "Integrity FAIL\n";
         return 1;
    }

    service.decryptFile("netflix_titles.enc", "netflix_titles_dec.csv", passwd);
    std::cout << "Done\n";
}