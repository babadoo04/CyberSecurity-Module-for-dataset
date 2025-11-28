#include "pch.hpp"
#include "securityModule.hpp"

#include <fstream>


securityModule::securityModule(std::unique_ptr<keyDeriverI> deriver, std::unique_ptr<randomProviderI> rng,
                               std::unique_ptr<aeadEncryptor> cipher) noexcept : 
    deriver{std::move(deriver)},
    rng{std::move(rng)},
    cipher{(std::move(cipher))} {
}

std::vector<std::uint8_t> securityModule::readAll(const std::filesystem::path& path) {
    std::ifstream is(path, std::ios::binary);
    if (!is) {
        throw std::runtime_error("Cannot open input file: " + path.string());
    }

    std::vector<std::uint8_t> data;
    int c = 0;
    
    while ((c = is.get()) != std::char_traits<char>::eof()) {
        data.push_back(static_cast<std::uint8_t>(c));
    }

    return data;
}

void securityModule::writeAll(const std::filesystem::path& path, const std::vector<std::uint8_t>& data) {
    std::ofstream os(path, std::ios::binary);
    
    if (!os) {
        throw std::runtime_error("Cannot open output file: " + path.string());
    }

    for (const std::uint8_t b : data) {
        os.put(static_cast<char>(b));
    }
}

void securityModule::save(const std::filesystem::path& path, const encryptedFile& f) {
    std::ofstream os(path, std::ios::binary);
    
    if (!os) {
        throw std::runtime_error("Cannot open encrypted file: " + path.string());
    }

    const auto writeVec = [&](const std::vector<std::uint8_t>& v) {
        for (const std::uint8_t b : v) {
            os.put(static_cast<char>(b));
        }
    };

    writeVec(f.salt);
    writeVec(f.iv);
    writeVec(f.tag);
    writeVec(f.ciphertext);
}

encryptedFile securityModule::load(const std::filesystem::path& path) {
    const auto bytes = readAll(path);

    constexpr std::size_t saltLen = 16;
    constexpr std::size_t ivLen   = 12;
    constexpr std::size_t tagLen  = 16;

    if (bytes.size() < saltLen + ivLen + tagLen) {
        throw std::runtime_error("Encrypted file too small: " + path.string());
    }

    encryptedFile f;
    auto it = bytes.begin();

    f.salt.assign(it, it + static_cast<std::ptrdiff_t>(saltLen));
    it += static_cast<std::ptrdiff_t>(saltLen);

    f.iv.assign(it, it + static_cast<std::ptrdiff_t>(ivLen));
    it += static_cast<std::ptrdiff_t>(ivLen);

    f.tag.assign(it, it + static_cast<std::ptrdiff_t>(tagLen));
    it += static_cast<std::ptrdiff_t>(tagLen);

    f.ciphertext.assign(it, bytes.end());

    return f;
}

void securityModule::encryptFile(const std::filesystem::path& in, const std::filesystem::path& out,
                                 const std::string& pass) const {
    const auto pt = readAll(in);

    encryptedFile f;
    f.salt = rng->getBytes(deriver->saltSize());
    f.iv = rng->getBytes(cipher->ivSize());

    const auto key = deriver->deriveKey(pass, f.salt);

    const auto enc = cipher->encrypt(pt, key, f.iv);
    f.tag = enc.tag;
    f.ciphertext = enc.ciphertext;

    save(out, f);
}

void securityModule::decryptFile(const std::filesystem::path& in, const std::filesystem::path& out, const std::string& pass) const {
    const encryptedFile f   = load(in);
    const std::vector<std::uint8_t> key = deriver->deriveKey(pass, f.salt);

    const std::vector<std::uint8_t> pt = cipher->decrypt(f, key);
    writeAll(out, pt);
}

bool securityModule::verifyIntegrity(const std::filesystem::path& in, const std::string& pass) const {
    try {
        const encryptedFile f   = load(in);
        const std::vector<std::uint8_t> key = deriver->deriveKey(pass, f.salt);
        (void)cipher->decrypt(f, key);
        return true;
    } catch (...) {
        return false;
    }
}


