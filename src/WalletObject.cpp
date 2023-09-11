/*
 * This code is licensed under the terms of the MIT License.
 *
 * Author: pasichDev
 * Repository: https://github.com/pasichDev/NosoCpp
 *
 * See LICENSE file for details.
 */
#include "WalletObject.h"

WalletObject WalletObject::Copy(
    const std::string& hash,
    const std::string& publicKey,
    const std::string& privateKey
) const {
    WalletObject copiedObject;
    copiedObject.Hash = !hash.empty() ? hash : this->Hash;
    copiedObject.PublicKey = !publicKey.empty() ? publicKey : this->PublicKey;
    copiedObject.PrivateKey = !privateKey.empty() ? privateKey : this->PrivateKey;
    return copiedObject;
}
