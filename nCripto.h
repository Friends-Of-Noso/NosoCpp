#ifndef NCRIPTO_H
#define NCRIPTO_H

#include <vector>
#include <bitset>
#include "Objects.h"
#include "Constants.h"
#include <botan/bigint.h>
#include <botan/base58.h>
#include <botan/base64.h>
#include <botan/sha2_32.h>
#include <botan/hex.h>
#include <botan/rmd160.h>

#include <botan/botan.h>
#include <botan/pubkey.h>
#include <botan/ec_group.h>
#include <botan/ecdsa.h>
#include <botan/auto_rng.h>
#include <botan/base64.h>

class nCripto {
private:
	std::vector<unsigned char> nosoBase64Decode(const std::string& input);
	std::string getHashSha256ToString(std::string publicKey);
	std::string getHashMD160ToString(std::string pubSHAHashed);


	int BMB58resumen(const std::string& numero58);
	std::string BMDecto58(const std::string& numero);
	Botan::BigInt BMHexToDec(std::string numerohex);
	NosoC::DivResult DivideBigInt(const Botan::BigInt& numerator, const Botan::BigInt& denominator);
	std::string BMHexto58(const std::string& numerohex, const Botan::BigInt& alphabetnumber);


public:
	bool verifySignedString(std::string stringSigned, std::string publicKey);
	std::string getAddressFromPublicKey(std::string publicKey);
	NosoC::KeyPair generateECKeysPair();
};

#endif // MCRIPTO_H
