/*
 * This code is licensed under the terms of the MIT License.
 *
 * Author: pasichDev
 * Repository: https://github.com/pasichDev/NosoCpp
 *
 * See LICENSE file for details.
 */

#ifndef WALLET_HPP
#define WALLET_HPP

#include <map>
#include <string>

class WalletObject {
public:
    std::string Hash;
    std::string PublicKey;
    std::string PrivateKey;

    WalletObject(const std::string& hash, const std::string& publicKey, const std::string& privateKey)
        : Hash(hash), PublicKey(publicKey), PrivateKey(privateKey) {}

    WalletObject Copy(
        const std::string& hash = "",
        const std::string& publicKey = "",
        const std::string& privateKey = ""
    ) const {
        return WalletObject(hash.empty() ? Hash : hash,
            publicKey.empty() ? PublicKey : publicKey,
            privateKey.empty() ? PrivateKey : privateKey);
    }
};

template <typename KeyType>
class Wallet {
public:
    Wallet() {}

    WalletObject* CreateNewWalletObject(
        const std::string& hash = "",
        const std::string& publicKey = "",
        const std::string& privateKey = ""
    ) {
        WalletObject* walletObject = new WalletObject(hash, publicKey, privateKey);
        objects[hash] = walletObject;
        return walletObject;
    }

    WalletObject* GetWalletObject(const KeyType& key) {
        if (objects.find(key) != objects.end()) {
            return objects[key];
        }
        else {
            return nullptr;
        }
    }

    typename std::map<KeyType, WalletObject*>::iterator begin() {
        return objects.begin();
    }

    typename std::map<KeyType, WalletObject*>::iterator end() {
        return objects.end();
    }

private:
    std::map<KeyType, WalletObject*> objects;
};

#endif // WALLET_HPP
