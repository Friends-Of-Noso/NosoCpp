/*
 * This code is licensed under the terms of the MIT License.
 *
 * Author: pasichDev
 * Repository: https://github.com/pasichDev/NosoCpp
 *
 * See LICENSE file for details.
 */
#include "VerifySing.h"

string NosoCpp::signMessage(const string &message, const string &privateKey)
{
	try
	{
		Botan::AutoSeeded_RNG rng;
		std::vector<unsigned char> messages = NosoCppCore::nosoBase64Decode("VERIFICATION");
		Botan::secure_vector<uint8_t> decodedPrivatKey = Botan::base64_decode(privateKey);
		Botan::AlgorithmIdentifier alg_id("ECDSA", Botan::AlgorithmIdentifier::USE_NULL_PARAM);

		Botan::BigInt private_key_value = Botan::BigInt::decode(decodedPrivatKey.data(), decodedPrivatKey.size());
		Botan::EC_Group secp256k1("secp256k1");
		Botan::ECDSA_PrivateKey private_key(rng, secp256k1, private_key_value);
		Botan::PK_Signer signer(private_key, rng, NosoC::emsa, Botan::DER_SEQUENCE);
		signer.update(messages);
		std::vector<uint8_t> signature = signer.signature(rng);

		std::string signature_base64 = Botan::base64_encode(signature.data(), signature.size());

		return signature_base64;
	}

	catch (const std::exception &ex)
	{
		std::cerr << "Error: " << ex.what() << std::endl;
		return nullptr;
	}
}

bool NosoCpp::verifySignedString(const string &message, const string &signatureBase64, const string &publicKey)
{

	try
	{
		Botan::AutoSeeded_RNG rng;
		Botan::secure_vector<uint8_t> decodedPublicKey = Botan::base64_decode(publicKey);
		Botan::secure_vector<uint8_t> signature = Botan::base64_decode(signatureBase64.data(), signatureBase64.size());
		std::vector<unsigned char> messages = NosoCppCore::nosoBase64Decode(message);

		if (decodedPublicKey.size() != 65)
		{
			std::cerr << "Invalid UNCOMPRESSED public key format" << std::endl;
			return false;
		}
		std::vector<uint8_t> xCoord(decodedPublicKey.begin() + 1, decodedPublicKey.begin() + 33);
		std::vector<uint8_t> yCoord(decodedPublicKey.begin() + 33, decodedPublicKey.end());

		Botan::BigInt x_bigint(xCoord.data(), xCoord.size());
		Botan::BigInt y_bigint(yCoord.data(), yCoord.size());

		Botan::EC_Group secp256k1("secp256k1");

		Botan::PointGFp point = secp256k1.point(x_bigint, y_bigint);

		Botan::ECDSA_PublicKey publicKeyEc(secp256k1, point);
		Botan::PK_Verifier verifier(publicKeyEc, NosoC::emsa, Botan::DER_SEQUENCE);
		verifier.update(messages);

		return verifier.check_signature(signature);
	}

	catch (const std::exception &ex)
	{
		std::cerr << "Error: " << ex.what() << std::endl;
		return false;
	}
}
