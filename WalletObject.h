#pragma once

#include <string>

class WalletObject {
public:
    std::string Hash;
    std::string PublicKey;
    std::string PrivateKey;

    WalletObject Copy(
        const std::string& hash = "",
        const std::string& publicKey = "",
        const std::string& privateKey = ""
    ) const;
};
