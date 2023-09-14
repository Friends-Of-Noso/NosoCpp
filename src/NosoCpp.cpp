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

		Wallet<std::string> walletString;

		std::string hash = cripto.getAddressFromPublicKey(KeysPair.PublicKey);

		return walletString.CreateNewWalletObject(hash, KeysPair.PublicKey, KeysPair.PrivateKey);
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
		Wallet<std::string> walletString;
		std::string hash = cripto.getAddressFromPublicKey(keysPair.PublicKey);
		return walletString.CreateNewWalletObject(hash, keysPair.PublicKey, keysPair.PrivateKey);

	}
	else
	{
		std::cout << "  #Error -> Key verification error" << std::endl;
	}

	return nullptr;
}
