#include "mSigner.h"



std::vector<unsigned char>  mSigner::signMessage(const std::vector<unsigned char>& message,
    const std::vector<unsigned char>& privateKey, NosoC::KeyType keyType)
{
  
    AutoSeededRandomPool rng;

    ECDSA<ECP, SHA1>::PrivateKey ecPrivateKey;
    ecPrivateKey.Initialize(rng, ASN1::secp256k1()); // тут можливо потрібно буде внести зміни в ключ

    // Set the private key
    ECDSA<ECP, SHA1>::Signer signer(ecPrivateKey);
    size_t signatureLength = signer.MaxSignatureLength();

    SecByteBlock signature(signatureLength);
    signatureLength = signer.SignMessage(rng, &message[0], message.size(), signature);

    return std::vector<byte>(signature.begin(), signature.begin() + signatureLength);

}

bool mSigner::verifySignature(const std::vector<unsigned char>& signature, const std::vector<unsigned char>& message, const std::vector<unsigned char>& privateKey, NosoC::KeyType keyType)
{
    CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::Verifier verifier;

    CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey ecPrivateKey;
    CryptoPP::StringSource publicKeySource(privateKey.data(), privateKey.size(), true);
    ecPrivateKey.Load(publicKeySource);

    CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::Verifier verifier(ecPrivateKey);

    bool result = false;
    CryptoPP::StringSource(signature.data(), signature.size(), true,
        new CryptoPP::SignatureVerificationFilter(
            verifier,
            new CryptoPP::ArraySink((byte*)&result, sizeof(result))
        )
    );

    return result;
}






