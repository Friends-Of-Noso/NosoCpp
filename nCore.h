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


class nCore {

public:
	std::vector<unsigned char> nosoBase64Decode(const std::string& input);
	int B58Sum(const std::string& number58);
	std::string DecTo58(const std::string& number);
	Botan::BigInt HexToDec(std::string numerohex);
	NosoC::DivResult DivideBigInt(const Botan::BigInt& numerator, const Botan::BigInt& denominator);
	std::string BMHexto58(const std::string& numerohex, const Botan::BigInt& alphabetnumber);

};

#endif // NCORE_H
