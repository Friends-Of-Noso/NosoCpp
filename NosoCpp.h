/*
 * This code is licensed under the terms of the MIT License.
 *
 * Author: pasichDev
 * Repository: https://github.com/pasichDev/NosoCpp
 *
 * See LICENSE file for details.
 */
#ifndef NOSOC_H
#define NOSOC_H

#include <iostream>
#include <vector>

#include "nCripto.h"
#include "nUtils.h"
#include "WalletObject.h"


namespace NosoCpp {
	WalletObject* ImportAddressForKeys(const std::string& keys);
	WalletObject* CreateNewAddress();

	std::string signMessage(const std::string& message, const std::string& privateKey);
	bool verifySignatureMessage(const std::string& message, const std::string signatureBase64, const std::string publicKey);

};
#endif // NOSOC_H
