/*
 * This code is licensed under the terms of the MIT License.
 *
 * Author: pasichDev
 * Repository: https://github.com/pasichDev/NosoCpp
 *
 * See LICENSE file for details.
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace NosoC {

	const std::string B58Alphabet = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
	const std::string B36Alphabet = "0123456789abcdefghijklmnopqrstuvwxyz";
	const std::string B64Alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	const std::string CoinChar = "N";
	const std::string StringSignature = "VERIFICATION";
	const std::string emsa = "EMSA1(SHA-1)";

}

#endif