#ifndef OBJECTS_H
#define OBJECTS_H
#include <string>
#include <botan/bigint.h>

namespace NosoC {

    const std::string B58Alphabet = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
    const std::string B36Alphabet = "0123456789abcdefghijklmnopqrstuvwxyz";
    const std::string B64Alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    const std::string CoinChar = "N";
    const std::string StringSignature = "VERIFICATION";

    class KeyPair {
    public:
        std::string PublicKey;
        std::string PrivateKey;
    };

    enum class KeyType {
        SECP256K1,
        SECP384R1,
        SECP521R1,
        SECT283K1
    };

    class DivResult {
    public:
        Botan::BigInt Cociente;
        Botan::BigInt Residuo;
    };

} // namespace NosoC_::models

#endif // OBJECTS_H
