/*
 * This code is licensed under the terms of the MIT License.
 *
 * Author: pasichDev
 * Repository: https://github.com/pasichDev/NosoCpp
 *
 * See LICENSE file for details.
 */
#ifndef NCRIPTO_H
#define NCRIPTO_H

#include <vector>
#include <bitset>
#include <iostream>

#include "Objects.h"
#include "Constants.h"

#include <botan/bigint.h>
#include <botan/base58.h>
#include <botan/base64.h>
#include <botan/sha2_32.h>
#include <botan/hex.h>
#include <botan/rmd160.h>
#include <botan/pubkey.h>
#include <botan/ecdsa.h>
#include <botan/botan.h>
#include "nCore.h"



class nCripto {
private:
	nCore core;
	std::string getHashSha256ToString(const std::string& publicKey);
	std::string getHashMD160ToString(const std::string& pubSHAHashed);

public:
	bool verifySignedString(const std::string& message, const std::string& signatureBase64, const std::string& publicKey);
	std::string getAddressFromPublicKey(const  std::string& publicKey);
	NosoC::KeyPair generateECKeysPair();
	std::string signMessage(const std::string& message, const std::string& privateKey);

};

#endif // MCRIPTO_H
