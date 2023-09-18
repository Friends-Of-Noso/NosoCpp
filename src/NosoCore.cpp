/*
 * This code is licensed under the terms of the MIT License.
 *
 * Author: pasichDev
 * Repository: https://github.com/pasichDev/NosoCpp
 *
 * See LICENSE file for details.
 */
#include "NosoCore.h"
std::string NosoCppCore::BMHexto58(const std::string& numerohex, const BigInt& alphabetnumber) {

    BigInt decimalValue = HexToDec(numerohex);
    std::string Result = "";
    std::string AlphabetUsed;

    if (alphabetnumber == 36) {
        AlphabetUsed = NosoC::B36Alphabet;
    }
    else {
        AlphabetUsed = NosoC::B58Alphabet;
    }

    while (decimalValue.bits() >= 2) {
        NosoC::DivResult ResultDiv = DivideBigInt(decimalValue, alphabetnumber);
        decimalValue = ResultDiv.Quotient;
        int remainder = ResultDiv.Remainder.to_u32bit();
        Result = AlphabetUsed[remainder] + Result;
    }

    if (decimalValue >= alphabetnumber.to_u32bit()) {
        NosoC::DivResult ResultDiv = DivideBigInt(decimalValue, alphabetnumber);
        decimalValue = ResultDiv.Quotient;
        int remainder = ResultDiv.Remainder.to_u32bit();
        Result = AlphabetUsed[remainder] + Result;
    }

    if (decimalValue > 0) {
        int value = decimalValue.to_u32bit();
        Result = AlphabetUsed[value] + Result;
    }

    return Result;
}

BigInt NosoCppCore::HexToDec(std::string numerohex) {
    std::vector<uint8_t> bytes;
    for (size_t i = 0; i < numerohex.size(); i += 2) {
        std::string byteString = numerohex.substr(i, 2);
        uint8_t byte = static_cast<uint8_t>(std::stoi(byteString, nullptr, 16));
        bytes.push_back(byte);
    }
    return BigInt(bytes.data(), bytes.size());
}

NosoC::DivResult NosoCppCore::DivideBigInt(const BigInt& numerator, const BigInt& denominator)
{
    NosoC::DivResult result;
    result.Quotient = numerator / denominator;
    result.Remainder = numerator % denominator;
    return result;
}


std::string NosoCppCore::DecTo58(const std::string& number) {
    BigInt decimalValue = BigInt(number);
    NosoC::DivResult resultDiv;
    std::string remainder;
    std::string result = "";

    while (decimalValue.bits() >= 2) {
        resultDiv = DivideBigInt(decimalValue, 58);
        decimalValue = resultDiv.Quotient;
        remainder = std::to_string(resultDiv.Remainder.to_u32bit());
        result = NosoC::B58Alphabet[std::stoi(remainder)] + result;
    }

    if (decimalValue.cmp(58) >= 0) {
        resultDiv = DivideBigInt(decimalValue, 58);
        decimalValue = resultDiv.Quotient;
        remainder = std::to_string(resultDiv.Remainder.to_u32bit());
        result = NosoC::B58Alphabet[std::stoi(remainder)] + result;
    }

    if (decimalValue.cmp(0) > 0) {
        result = NosoC::B58Alphabet[decimalValue.to_u32bit()] + result;
    }

    return result;
}


int NosoCppCore::B58Sum(const std::string& number58) {
    int total = 0;

    for (size_t i = 0; i < number58.length(); i++) {
        char currentChar = number58[i];
        size_t foundIndex = NosoC::B58Alphabet.find(currentChar);

        if (foundIndex != std::string::npos) {
            total += static_cast<int>(foundIndex);
        }
    }

    return total;
}



std::vector<unsigned char> NosoCppCore::nosoBase64Decode(const std::string& input) {

    std::vector<int> indexList;
    for (char c : input) {
        auto it = NosoC::B64Alphabet.find(c);
        if (it != std::string::npos) {
            indexList.push_back(static_cast<int>(it));
        }
    }

    std::string binaryString;
    for (int i : indexList) {
        std::string binary = std::bitset<6>(i).to_string();
        binaryString += binary;
    }

    std::string strAux = binaryString;
    std::vector<unsigned char> tempByteArray;

    while (strAux.length() >= 8) {
        std::string currentGroup = strAux.substr(0, 8);
        int intVal = std::stoi(currentGroup, nullptr, 2);
        tempByteArray.push_back(static_cast<unsigned char>(intVal));
        strAux = strAux.substr(8);
    }

    return tempByteArray;
}

string NosoCppCore::getHashSha256ToString(const string &publicKey)
{
	SHA_256 sha256;
	sha256.update(reinterpret_cast<const Botan::byte *>(publicKey.c_str()), publicKey.length());
	secure_vector<Botan::byte> digest = sha256.final();

	string result = hex_encode(digest);

	for (char &c : result)
	{
		if (c == '-')
			c = ' ';
		c = std::toupper(c);
	}

	return result;
}

string NosoCppCore::getHashMD160ToString(const string &pubSHAHashed)
{
	RIPEMD_160 hash;
	secure_vector<uint8_t> hashResult = hash.process(reinterpret_cast<const uint8_t *>(pubSHAHashed.data()), pubSHAHashed.size());
	string hashHex = hex_encode(hashResult);

	for (char &c : hashHex)
	{
		c = std::toupper(c);
	}

	return hashHex;
}
