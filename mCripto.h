#ifndef MCRIPTO_H
#define MCRIPTO_H
#include <string>
#include <vector>
#include <bitset>
#include "Objects.h"
#include "mSigner.h"
#include <cryptopp/ripemd.h>
#include <botan/bigint.h>
#include <botan/base58.h>
#include <botan/base64.h>
#include <botan/sha2_32.h>
#include <botan/hex.h>


class mCripto {
private:
	mSigner signer;
	std::vector<unsigned char> nosoBase64Decode(const std::string& input);
	std::string getHashSha256ToString(std::string publicKey);
	std::string getHashMD160ToString(std::string pubSHAHashed);


	int BMB58resumen(const std::string& numero58);
	std::string BMDecto58(const std::string& numero);
	Botan::BigInt BMHexToDec(std::string numerohex);
	NosoC::DivResult BMDividir(const Botan::BigInt& numerador, const Botan::BigInt& denominador);
	std::string BMHexto58(const std::string& numerohex, const Botan::BigInt& alphabetnumber);

public:
	std::string getStringSigned(std::string stringSigned, std::string privateKey);
	bool verifySignedString(std::string stringSigned, std::string signature, std::string publicKey);
	std::string getAddressFromPublicKey(std::string publicKey);
};

#endif // MCRIPTO_H
