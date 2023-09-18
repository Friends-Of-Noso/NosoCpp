/*
 * This code is licensed under the terms of the MIT License.
 *
 * Author: pasichDev
 * Repository: https://github.com/pasichDev/NosoCpp
 *
 * See LICENSE file for details.
 */
#ifndef VERIFYSING_H
#define VERIFYSING_H

#include <vector>
#include <bitset>
#include <iostream>

#include "Objects.h"
#include "Constants.h"
#include "NosoCore.h"

#include <botan/bigint.h>
#include <botan/base64.h>
#include <botan/hex.h>
#include <botan/pubkey.h>
#include <botan/ecdsa.h>
#include <botan/botan.h>
using namespace std;

namespace NosoCpp {
	bool verifySignedString(const string& message, const string& signatureBase64, const string& publicKey);
	string signMessage(const string& message, const string& privateKey);

};

#endif // MCRIPTO_H