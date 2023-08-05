#include "NosoCpp.h"




mCripto cripto;

WalletObject* ImportWalletQR(std::string& keys) {
	std::vector<std::string> tokens;
	std::string delimiter = " ";
	size_t pos = 0;
	WalletObject* walletObject = NULL;

	std::cout << "### Start Test \n" << std::endl;
	while ((pos = keys.find(delimiter)) != std::string::npos) {
		std::string token = keys.substr(0, pos);
		tokens.push_back(token);
		keys.erase(0, pos + delimiter.length());
	}
	tokens.push_back(keys);

	if (tokens.size() == 2) {
		std::string publicKey = tokens[0];
		std::string privateKey = tokens[1];


		std::string signature = cripto.getStringSigned(NosoC::StringSignature, privateKey);
		bool verification = cripto.verifySignedString(NosoC::StringSignature, signature, publicKey);

		if (verification) {
			walletObject = new WalletObject();
			walletObject->PublicKey = publicKey;
			walletObject->PrivateKey = privateKey;
			//  walletObject->Hash = mCripto::GetAddressFromPublicKey(publicKey);
			return walletObject;
		}

		if (walletObject != nullptr) {
			std::cout << "  #Wallet Object:" << std::endl;
			std::cout << "  #Hash: " << walletObject->Hash << std::endl;
			std::cout << "  #Public Key: " << walletObject->PublicKey << std::endl;
			std::cout << "  #Private Key: " << walletObject->PrivateKey << std::endl;
		}
		else {
			std::cout << "  #Error -> Invalid input keys." << std::endl;
		}
	}

	return nullptr;
}

bool NosoCpp::operator==(const NosoCpp& other) const
{
	return false;
}



