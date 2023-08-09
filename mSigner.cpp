#include "mSigner.h"




std::vector<unsigned char>  mSigner::signMessage(const std::vector<unsigned char>& message,
    const std::vector<unsigned char>& privateKey, NosoC::KeyType keyType)
{
    AutoSeededRandomPool rng;
    ECDSA<ECP, SHA1>::PrivateKey ecPrivateKey;
    ecPrivateKey.Initialize(ASN1::secp256k1(), Integer(privateKey.data(), privateKey.size()));
    ECDSA<ECP, SHA1>::Signer signer(ecPrivateKey);
    size_t signatureLength = signer.MaxSignatureLength();
    SecByteBlock signature(signatureLength);
    signatureLength = signer.SignMessage(rng, message.data(), message.size(), signature);

    return std::vector<unsigned char>(signature.begin(), signature.begin() + signatureLength);



}

bool mSigner::verifySignature(const std::vector<unsigned char>& signature, const std::vector<unsigned char>& message, const std::vector<unsigned char>& publicKey, NosoC::KeyType keyType)
{
    
    return true;
}






