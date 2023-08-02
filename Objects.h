#ifndef OBJECTS_H
#define OBJECTS_H
#include <string>

namespace NosoC {

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
        std::string Cociente;
        std::string Residuo;
    };

} // namespace NosoC_::models

#endif // OBJECTS_H
