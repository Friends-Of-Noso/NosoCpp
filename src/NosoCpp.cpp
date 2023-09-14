/*
 * This code is licensed under the terms of the MIT License.
 *
 * Author: pasichDev
 * Repository: https://github.com/pasichDev/NosoCpp
 *
 * See LICENSE file for details.
 */
#include "NosoCpp.h"
nCripto cripto;
WalletObject* NosoCpp::CreateNewAddress() {
	try {
		NosoC::KeyPair KeysPair = cripto.generateECKeysPair();

		WalletObject* walletObject = new WalletObject();

		walletObject->PublicKey = KeysPair.PublicKey;
		walletObject->PrivateKey = KeysPair.PrivateKey;
		walletObject->Hash = cripto.getAddressFromPublicKey(KeysPair.PublicKey);
		return walletObject;
	}

	catch (const std::exception& ex)
	{
		std::cerr << "Error: " << ex.what() << std::endl;
		return nullptr;
	}

}

std::string NosoCpp::signMessage(const std::string& message, const std::string& privateKey)
{
	try {
		return  cripto.signMessage(message, privateKey);
	}

	catch (const std::exception& ex)
	{
		std::cerr << "Error: " << ex.what() << std::endl;
		return nullptr;
	}
}

bool NosoCpp::verifySignatureMessage(const std::string& message, const std::string signatureBase64, const std::string publicKey)
{
	try {
		return cripto.verifySignedString(message, signatureBase64, publicKey);
	}

	catch (const std::exception& ex)
	{
		std::cerr << "Error: " << ex.what() << std::endl;
		return false;
	}
}


WalletObject* NosoCpp::ImportAddressForKeys(const std::string& keys) {

	NosoC::KeyPair keysPair = NosoCppUtils::StringTokenizer(keys);
	std::string signature = cripto.signMessage(NosoC::StringSignature, keysPair.PrivateKey);
	bool verification = cripto.verifySignedString(NosoC::StringSignature, signature, keysPair.PublicKey);



	if (!NosoCppUtils::checkSizesKeyPair(keysPair)) {
		std::cout << "  #Error -> Invalid input keys, " << std::endl;
		return nullptr;
	}



	if (verification) {
		WalletObject* walletObject = new WalletObject();
		walletObject->PublicKey = keysPair.PublicKey;
		walletObject->PrivateKey = keysPair.PrivateKey;
		walletObject->Hash = cripto.getAddressFromPublicKey(keysPair.PublicKey);

		std::cout << "  #Wallet Object:" << std::endl;
		std::cout << "  #Hash: " << walletObject->Hash << std::endl;
		std::cout << "  #Public Key: " << walletObject->PublicKey << std::endl;
		std::cout << "  #Private Key: " << walletObject->PrivateKey << std::endl;
		return walletObject;
	}
	else
	{
		std::cout << "  #Error -> Key verification error" << std::endl;
	}

	return nullptr;
}
