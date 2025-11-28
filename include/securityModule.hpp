#ifndef SECURITY_MODULE_HPP
#define SECURITY_MODULE_HPP

#include <memory>
#include <filesystem>

#include "IAeadEncryptor.hpp"
#include "IkeyDeriver.hpp"
#include "IrandomProvider.hpp"

class securityModule {
public:
    securityModule(std::unique_ptr<keyDeriverI> deriver, std::unique_ptr<randomProviderI> rng,
                   std::unique_ptr<aeadEncryptor> cipher) noexcept;
    ~securityModule() noexcept = default;

    void encryptFile(const std::filesystem::path& in,
                     const std::filesystem::path& out,
                     const std::string& pass) const;

    void decryptFile(const std::filesystem::path& in,
                     const std::filesystem::path& out,
                     const std::string& pass) const;

    bool verifyIntegrity(const std::filesystem::path& in,
                         const std::string& pass) const;
private:
    std::unique_ptr<keyDeriverI> deriver;
    std::unique_ptr<randomProviderI> rng;
    std::unique_ptr<aeadEncryptor> cipher;

    static std::vector<std::uint8_t> readAll(const std::filesystem::path& path);
    static void writeAll(const std::filesystem::path& path,
                         const std::vector<std::uint8_t>& data);

    static void save(const std::filesystem::path& path, const encryptedFile& f);
    static encryptedFile load(const std::filesystem::path& path);
};

#endif // !SECURITY_MODULE_HPP