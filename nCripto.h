#ifndef NCRIPTO_H
#define NCRIPTO_H
#include <string>
#include <vector>
#include <bitset>
#include "Objects.h"
#include "nSigner.h"
#include "Constants.h"
#include <cryptopp/ripemd.h>
#include <botan/bigint.h>
#include <botan/base58.h>
#include <botan/base64.h>
#include <botan/sha2_32.h>
#include <botan/hex.h>


class nCripto {
private:
	nSigner signer;
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

	NosoC::KeyPair generateECKeysPair();
};

#endif // MCRIPTO_H
