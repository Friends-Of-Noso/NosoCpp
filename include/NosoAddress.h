/*
 * This code is licensed under the terms of the MIT License.
 *
 * Author: pasichDev
 * Repository: https://github.com/pasichDev/NosoCpp
 *
 * See LICENSE file for details.
 */
#ifndef NOSOADDRESS_H
#define NOSOADDRESS_H

#include <vector>
#include <bitset>
#include <iostream>

#include "Objects.h"
#include "Constants.h"
#include "NosoUtils.h"
#include "NosoCore.h"
#include "WalletObject.h"
#include "VerifySing.h"

#include <botan/bigint.h>
#include <botan/base58.h>
#include <botan/base64.h>
#include <botan/sha2_32.h>
#include <botan/hex.h>
#include <botan/rmd160.h>
#include <botan/pubkey.h>
#include <botan/ecdsa.h>
#include <botan/botan.h>

using namespace std;
using namespace Botan;

namespace NosoCpp
{

	string restoreHashFromPublicKey(const string &publicKey);
	NosoC::KeyPair generateNewKeysPair();

	WalletObject* restoreAddressFromKeysPair(const std::string &keys);
	WalletObject* generateNewAddress();

};

#endif // MCRIPTO_H
