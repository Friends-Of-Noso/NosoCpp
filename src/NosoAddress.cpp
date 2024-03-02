/*
 * This code is licensed under the terms of the MIT License.
 *
 * Author: pasichDev
 * Repository: https://github.com/pasichDev/NosoCpp
 *
 * See LICENSE file for details.
 */
#include "NosoAddress.h"
#include <print>

/*
 */
string NosoCpp::restoreHashFromPublicKey(const string &publicKey)
{
	string pubSHAHashed = NosoCppCore::getHashSha256ToString(publicKey);
	string hash1 = NosoCppCore::getHashMD160ToString(pubSHAHashed);
	hash1 = NosoCppCore::BMHexto58(hash1, 58);
	int sumatoria = NosoCppCore::B58Sum(hash1);
	string clave = NosoCppCore::DecTo58(std::to_string(sumatoria));
	return NosoC::CoinChar + hash1 + clave;
}

/*
 */
NosoC::KeyPair NosoCpp::generateNewKeysPair()
{
	AutoSeeded_RNG rng;
	EC_Group secp256k1("secp256k1");
	ECDSA_PrivateKey privateKey(rng, secp256k1);
	vector<uint8_t> publicKeyPointBytes = privateKey.public_point().encode(Botan::PointGFp::UNCOMPRESSED);
	vector<uint8_t> privateKeyBytes = Botan::BigInt::encode(privateKey.private_value());
	string privateKeyBase64 = Botan::base64_encode(privateKeyBytes.data(), privateKeyBytes.size());
	string publicKeyPointBase64 = Botan::base64_encode(publicKeyPointBytes.data(), publicKeyPointBytes.size());

	NosoC::KeyPair result;
	result.PublicKey = publicKeyPointBase64;
	result.PrivateKey = privateKeyBase64;

	std::string signature = NosoCpp::signMessage(NosoC::StringSignature, privateKeyBase64);

	std::cout << signature << endl;

	return result;
}

/*
 */
WalletObject* NosoCpp::restoreAddressFromKeysPair(const string &keys)
{
	NosoC::KeyPair keysPair = NosoCppUtils::StringTokenizer(keys);
	std::string signature = NosoCpp::signMessage(NosoC::StringSignature, keysPair.PrivateKey);

	std::cout << signature << endl;
	std::cerr << "Signature: "  << std::endl;

	bool verification = NosoCpp::verifySignedString(NosoC::StringSignature, signature, keysPair.PublicKey);

	if (!NosoCppUtils::checkSizesKeyPair(keysPair))
	{
		std::cout << "  #Error -> Invalid input keys, " << endl;

		return nullptr;
	}

	if (verification)
	{
		Wallet<std::string> walletString;
		return walletString.CreateNewWalletObject(NosoCpp::restoreHashFromPublicKey(keysPair.PublicKey), keysPair.PublicKey, keysPair.PrivateKey);
	}
	else
	{
		std::cout << "  #Error -> Key verification error" << endl;
	}

	return nullptr;
}
WalletObject* NosoCpp::generateNewAddress()
{
	try
	{
		NosoC::KeyPair keysPair = NosoCpp::generateNewKeysPair();
		Wallet<string> walletString;
		
		return walletString.CreateNewWalletObject(NosoCpp::restoreHashFromPublicKey(keysPair.PublicKey), keysPair.PublicKey, keysPair.PrivateKey);
	}

	catch (const std::exception &ex)
	{
		std::cerr << "Error: " << ex.what() << std::endl;
		return nullptr;
	}
}
