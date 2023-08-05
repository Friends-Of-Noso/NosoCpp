#ifndef MCRIPTO_H
#define MCRIPTO_H
#include <string>
#include <vector>
#include "Objects.h"
#include "mSigner.h"
#include <bitset>

class mCripto {
private:
	mSigner signer;
	std::vector<unsigned char> nosoBase64Decode(const std::string& input);
	std::string base64_encode(const std::vector<unsigned char>& input);
	std::vector<unsigned char> base64_decode(const std::string& input);
public:

	std::string getStringSigned(std::string stringSigned, std::string privateKey);
	bool verifySignedString(std::string stringSigned, std::string signature, std::string publicKey);
};

#endif // MCRIPTO_H
