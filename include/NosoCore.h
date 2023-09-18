/*
 * This code is licensed under the terms of the MIT License.
 *
 * Author: pasichDev
 * Repository: https://github.com/pasichDev/NosoCpp
 *
 * See LICENSE file for details.
 */
#ifndef NCORE_H
#define NCORE_H

#include <bitset>
#include <vector>

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

using namespace std;
using namespace Botan;

namespace NosoCppCore {
	vector<unsigned char> nosoBase64Decode(const string& input);
	int B58Sum(const string& number58);
	string DecTo58(const string& number);
	Botan::BigInt HexToDec(string numerohex);
	NosoC::DivResult DivideBigInt(const Botan::BigInt& numerator, const Botan::BigInt& denominator);
	string BMHexto58(const string& numerohex, const Botan::BigInt& alphabetnumber);
	string getHashSha256ToString(const string &publicKey);
	string getHashMD160ToString(const string &pubSHAHashed);

};

#endif // NCORE_H
