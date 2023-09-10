#ifndef NOSOC_H
#define NOSOC_H
#include "nCripto.h"
#include "nUtils.h"
#include <iostream>
#include <vector>
#include "WalletObject.h"
	class NosoCpp {
	private:
		nCripto cripto;
		nUtils utils;


	public:
		WalletObject* ImportWalletForKeys(std::string& keys);
		WalletObject* CreateNewAddress();

		std::string signMessage(const std::string& message, const std::string& privateKey);
		bool verifySignatureMessage(const std::string& message, const std::string signatureBase64, const std::string publicKey);

	};
#endif // NOSOC_H
