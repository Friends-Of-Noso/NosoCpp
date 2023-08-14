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
#include <cryptopp/base64.h>

#include <botan/auto_rng.h>
#include <botan/ecdsa.h>
#include <botan/pkcs8.h>
#include <botan/x509_key.h>
#include <botan/base64.h>
#include <botan/botan.h>
#include <botan/ecdsa.h>
#include <botan/pubkey.h>
#include <botan/secmem.h>
#include <botan/base64.h>

#include <botan/asn1_oid.h>
#include <iostream>
using namespace CryptoPP;

class nSigner {
public:
	std::string signMessage(const std::string& message, const CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey& privateKey);

	bool verifySignature(const std::string& signature, const std::string& message, const CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey& publicKey);


	NosoC::KeyPair generateECKeyPair();

};


#endif // SIGNERUTILS_H
