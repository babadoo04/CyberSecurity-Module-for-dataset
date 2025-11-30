# Security module for dataset

This repository contains a small C++ security module for protecting an anonymized dataset stored as a file and used inside a bachelor’s software project. 
The module provides **encryption** and **integrity/authenticity verification** so that the dataset can be safely stored and shared without risking silent tampering or unauthorized reading.

## Why this module is needed

Even after anonymization, datasets remain sensitive and valuable. They may contain important statistical patterns and research value. In addition, dataset files can be **silently replaced or partially modified** while preserving a valid file format.
Files can also be damaged during storage or copying, resulting in distorted results without obvious errors.

## Security approach

The module uses an **AEAD (Authenticated Encryption with Associated Data)** scheme:

- A cryptographic key is derived from a user password using **PBKDF2-HMAC-SHA256** with a random salt.
- The dataset is encrypted using **AES-256-GCM**, which provides confidentiality and built-in integrity checking via an authentication tag.

During decryption, AES-GCM verifies the authentication tag automatically. If the encrypted file was changed by even a single byte or the password is incorrect, integrity verification fails and decryption is rejected. 
This prevents the system from running analyses on altered or corrupted datasets.

## Dependencies

The repository does **not** ship with a built-in crypto library. A cryptographic backend **Crypto++** must be available on the system and is linked via CMake.
The exact dependency and linking logic are defined in `CMakeLists.txt`.

## Build and run

Build the project with CMake:

```bash
cmake -S . -B build
cmake --build build -j
```

## Expected behavior

- Any modification of the encrypted dataset file causes integrity verification to fail. Decryption is blocked if the file was altered or the wrong password is provided.

- The module does not restore deleted files. Availability must be ensured through backups and storage policies.

- The module guarantees that only authentic, unchanged datasets are accepted by the software product.

## Contacts

For questions or suggestions, contact the author:

- **Email:** nikitaayn@gmail.com  
