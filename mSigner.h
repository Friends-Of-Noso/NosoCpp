#ifndef MSIGNER_H
#define MSIGNER_H

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



#include <botan/botan.h>
#include <botan/ecdsa.h>
#include <botan/auto_rng.h>
#include <botan/pkcs8.h>
#include <botan/data_src.h>
#include <botan/oids.h>
#include <botan/base64.h>


using namespace CryptoPP;

class mSigner {
public:
	std::vector<unsigned char> signMessage(const std::vector<unsigned char>& message,
		const std::vector<unsigned char>& privateKey, NosoC::KeyType keyType);

	bool verifySignature(const std::vector<unsigned char>& signature, const std::vector<unsigned char>& message,
		const std::vector<unsigned char>& publicKey, NosoC::KeyType keyType);


	
};


#endif // SIGNERUTILS_H
