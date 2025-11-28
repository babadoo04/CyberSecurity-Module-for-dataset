#include <iostream>

#include "osRandomProvider.hpp"
#include "pbkdf2.hpp"
#include "aes256GcmCipher.hpp"
#include "securityModule.hpp"
#include "commandLinePanser.hpp"

int main(int argc, char** argv) {
    try {
        const ClArgs args = parseArgs(argc, argv);

        securityModule service(
            std::make_unique<pbkdf2>(16, 32, 200000),
            std::make_unique<osRandomProvider>(),
            std::make_unique<aes256GcmCipher>()
        );

        switch (args.op) {
            case operation::Encrypt:
                service.encryptFile(args.in, args.out, args.password);
                std::cout << "Encrypted file\n";
                break;

            case operation::Decrypt:
                service.decryptFile(args.in, args.out, args.password);
                std::cout << "Decrypted file\n";
                break;

            case operation::Verify: {
                const bool res = service.verifyIntegrity(args.in, args.password);
                std::cout << (res ? "Integrity OK\n" : "Integrity FAIL\n");
                return res ? 0 : 2;
            }
            default:
                return 1;
        }
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << "\n";
        return 1;
    }
}