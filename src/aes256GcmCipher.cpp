#include "pch.hpp"
#include "aes256GcmCipher.hpp"

encryptedFile aes256GcmCipher::encrypt(const std::vector<std::uint8_t> &plaintext, const std::vector<std::uint8_t> &key,
                                       const std::vector<std::uint8_t> &iv) const {
    if (key.size() != 32) {
        throw std::runtime_error("GCM: key must be 32 bytes");
    }

    if (iv.size()  != ivSize()) {
        throw std::runtime_error("GCM: iv must be 12 bytes");
    }

    CryptoPP::GCM<CryptoPP::AES>::Encryption enc;
    
    enc.SetKeyWithIV(key.data(), key.size(), iv.data(), iv.size());

    encryptedFile out;
    out.iv = iv;

    CryptoPP::AuthenticatedEncryptionFilter filter(
        enc,
        new CryptoPP::VectorSink(out.ciphertext),
        false,
        static_cast<int>(tagSize())
    );

    filter.ChannelPut(CryptoPP::DEFAULT_CHANNEL, plaintext.data(), plaintext.size());
    filter.ChannelMessageEnd(CryptoPP::DEFAULT_CHANNEL);
    
    if (out.ciphertext.size() < tagSize()) {
        throw std::runtime_error("GCM: ciphertext too small");
    }

    out.tag.assign(out.ciphertext.end() - tagSize(), out.ciphertext.end());
    out.ciphertext.resize(out.ciphertext.size() - tagSize());
    
    return out;
}

std::vector<std::uint8_t> aes256GcmCipher::decrypt(const encryptedFile &file, const std::vector<std::uint8_t> &key) const {
    if (key.size() != 32) {
        throw std::runtime_error("GCM: key must be 32 bytes");
    }
    
    if (file.iv.size()  != ivSize()) {
        throw std::runtime_error("GCM: bad iv");
    }

    if (file.tag.size() != tagSize()) {
        throw std::runtime_error("GCM: bad tag");
    }
    
    CryptoPP::GCM<CryptoPP::AES>::Decryption dec;
    dec.SetKeyWithIV(key.data(), key.size(), file.iv.data(), file.iv.size());

    std::vector<std::uint8_t> combined = file.ciphertext;
    combined.insert(combined.end(), file.tag.begin(), file.tag.end());

    std::vector<std::uint8_t> plaintext;
    CryptoPP::AuthenticatedDecryptionFilter filter(
        dec,
        new CryptoPP::VectorSink(plaintext)
    );

    filter.ChannelPut(CryptoPP::DEFAULT_CHANNEL, combined.data(), combined.size());
    filter.ChannelMessageEnd(CryptoPP::DEFAULT_CHANNEL);

    if (!filter.GetLastResult())
        throw std::runtime_error("Integrity check failed (file modified)");

    return plaintext;
}

constexpr std::size_t aes256GcmCipher::ivSize() const {
    return 12;
}

constexpr std::size_t aes256GcmCipher::tagSize() const {
    return 16;
}
