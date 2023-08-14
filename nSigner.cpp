#include "nSigner.h"
#include <botan/hex.h>

#include <cryptopp/eccrypto.h>
#include <cryptopp/osrng.h>
#include <cryptopp/hex.h>






NosoC::KeyPair nSigner::generateECKeyPair() {
  CryptoPP::AutoSeededRandomPool rng;

    CryptoPP::DL_GroupParameters_EC<CryptoPP::ECP> curve;
    curve.Initialize(CryptoPP::ASN1::secp256k1());

    CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey privateKey;
    privateKey.Initialize(rng, curve);

    CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey publicKey;
    privateKey.MakePublicKey(publicKey);

    CryptoPP::Integer publicKeyX = publicKey.GetPublicElement().x;
    CryptoPP::Integer privateKeyValue = privateKey.GetPrivateExponent();

    std::string publicKeyBytes;
    publicKeyX.Encode(CryptoPP::StringSink(publicKeyBytes).Ref(), publicKeyX.ByteCount());

    std::string privateKeyBytes;
    privateKeyValue.Encode(CryptoPP::StringSink(privateKeyBytes).Ref(), privateKeyValue.ByteCount());

    std::string publicKeyBase64;
    CryptoPP::StringSource(publicKeyBytes, true,
        new CryptoPP::Base64Encoder(new CryptoPP::StringSink(publicKeyBase64), false));

    std::string privateKeyBase64;
    CryptoPP::StringSource(privateKeyBytes, true,
        new CryptoPP::Base64Encoder(new CryptoPP::StringSink(privateKeyBase64), false));


	NosoC::KeyPair result;
	result.PublicKey = publicKeyBase64;
	result.PrivateKey = privateKeyBase64;

	return result;


}


  
















std::string nSigner::signMessage(const std::string& message, const CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey& privateKey)
{
	/*AutoSeededRandomPool rng;
	ECDSA<ECP, SHA1>::PrivateKey ecPrivateKey;
	ecPrivateKey.Initialize(ASN1::secp256k1(), Integer(privateKey.data(), privateKey.size()));
	ECDSA<ECP, SHA1>::Signer signer(ecPrivateKey);
	size_t signatureLength = signer.MaxSignatureLength();
	SecByteBlock signature(signatureLength);
	signatureLength = signer.SignMessage(rng, message.data(), message.size(), signature);

	return std::vector<unsigned char>(signature.begin(), signature.begin() + signatureLength);
	*/
	CryptoPP::AutoSeededRandomPool rng;

	// ECDSA schema
	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::Signer signer(privateKey);

	// Sign the message
	std::string signature;
	CryptoPP::StringSource(message, true,
		new CryptoPP::SignerFilter(rng, signer,
			new CryptoPP::StringSink(signature)
		)
	);

	return signature;

}

bool nSigner::verifySignature(const std::string& signature, const std::string& message, const CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey& publicKey)
{
	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::Verifier verifier(publicKey);

	// Verify message firm
	bool result = false;
	CryptoPP::StringSource(signature + message, true,
		new CryptoPP::SignatureVerificationFilter(
			verifier,
			new CryptoPP::ArraySink(reinterpret_cast<CryptoPP::byte*>(&result), sizeof(result))
		)
	);

	return result;
}






