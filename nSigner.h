#ifndef NSIGNER_H
#define NSIGNER_H

#include <vector>
#include <string>
#include "Objects.h"
#include <cryptopp/eccrypto.h>
#include <cryptopp/asn.h>
#include <cryptopp/ecp.h>
#include <cryptopp/osrng.h>
#include <cryptopp/oids.h>
#include <cryptopp/secblock.h>
#include <cryptopp/hex.h>

using namespace CryptoPP;

class nSigner {
public:
	std::vector<unsigned char> signMessage(const std::vector<unsigned char>& message,
		const std::vector<unsigned char>& privateKey, NosoC::KeyType keyType);

	bool verifySignature(const std::vector<unsigned char>& signature, const std::vector<unsigned char>& message,
		const std::vector<unsigned char>& publicKey, NosoC::KeyType keyType);


	NosoC::KeyPair generateECKeyPair();
};


#endif // SIGNERUTILS_H
