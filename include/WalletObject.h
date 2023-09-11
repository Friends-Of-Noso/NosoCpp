/*
 * This code is licensed under the terms of the MIT License.
 *
 * Author: pasichDev
 * Repository: https://github.com/pasichDev/NosoCpp
 *
 * See LICENSE file for details.
 */
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
