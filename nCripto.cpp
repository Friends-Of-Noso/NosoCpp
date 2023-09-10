/*
 * This code is licensed under the terms of the MIT License.
 *
 * Author: pasichDev
 * Repository: https://github.com/pasichDev/NosoCpp
 *
 * See LICENSE file for details.
 */
#include "nCripto.h"

nCore core;

std::string nCripto::getAddressFromPublicKey(const std::string& publicKey)
{
	std::string pubSHAHashed = getHashSha256ToString(publicKey);
	std::string hash1 = getHashMD160ToString(pubSHAHashed);
	hash1 = core.BMHexto58(hash1, 58);
	int sumatoria = core.B58Sum(hash1);
	std::string clave = core.DecTo58(std::to_string(sumatoria));
	return NosoC::CoinChar + hash1 + clave;
}

NosoC::KeyPair nCripto::generateECKeysPair()
{
	Botan::AutoSeeded_RNG rng;
	Botan::EC_Group secp256k1("secp256k1");
	Botan::ECDSA_PrivateKey privateKey(rng, secp256k1);
	std::vector<uint8_t> publicKeyPointBytes = privateKey.public_point().encode(Botan::PointGFp::UNCOMPRESSED);
	std::vector<uint8_t> privateKeyBytes = Botan::BigInt::encode(privateKey.private_value());
	std::string privateKeyBase64 = Botan::base64_encode(privateKeyBytes.data(), privateKeyBytes.size());
	std::string publicKeyPointBase64 = Botan::base64_encode(publicKeyPointBytes.data(), publicKeyPointBytes.size());

	NosoC::KeyPair result;
	result.PublicKey = publicKeyPointBase64;
	result.PrivateKey = privateKeyBase64;

	return result;

}

std::string nCripto::signMessage(const std::string& message, const std::string& privateKey)
{
	Botan::AutoSeeded_RNG rng;
	std::vector<unsigned char> messages = core.nosoBase64Decode("VERIFICATION");
	Botan::secure_vector<uint8_t> decodedPrivatKey = Botan::base64_decode(privateKey);
	Botan::AlgorithmIdentifier alg_id("ECDSA", Botan::AlgorithmIdentifier::USE_NULL_PARAM);

	Botan::BigInt private_key_value = Botan::BigInt::decode(decodedPrivatKey.data(), decodedPrivatKey.size());
	Botan::EC_Group secp256k1("secp256k1");
	Botan::ECDSA_PrivateKey private_key(rng, secp256k1, private_key_value);
	Botan::PK_Signer signer(private_key, rng, NosoC::emsa, Botan::DER_SEQUENCE);
	signer.update(messages);
	std::vector<uint8_t> signature = signer.signature(rng);

	std::string signature_base64 = Botan::base64_encode(signature.data(), signature.size());

	return  signature_base64;
}

bool nCripto::verifySignedString(const std::string& message, const std::string& signatureBase64, const std::string& publicKey)
{
	Botan::AutoSeeded_RNG rng;
	Botan::secure_vector<uint8_t> decodedPublicKey = Botan::base64_decode(publicKey);
	Botan::secure_vector<uint8_t> signature = Botan::base64_decode(signatureBase64.data(), signatureBase64.size());
	std::vector<unsigned char> messages = core.nosoBase64Decode("VERIFICATION");

	if (decodedPublicKey.size() != 65) {
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

std::string nCripto::getHashSha256ToString(const std::string& publicKey)
{
	Botan::SHA_256 sha256;
	sha256.update(reinterpret_cast<const Botan::byte*>(publicKey.c_str()), publicKey.length());
	Botan::secure_vector<Botan::byte> digest = sha256.final();

	std::string result = Botan::hex_encode(digest);

	for (char& c : result) {
		if (c == '-') c = ' ';
		c = std::toupper(c);
	}

	return result;
}

std::string nCripto::getHashMD160ToString(const std::string& pubSHAHashed)
{
	Botan::RIPEMD_160 hash;
	Botan::secure_vector<uint8_t> hashResult = hash.process(reinterpret_cast<const uint8_t*>(pubSHAHashed.data()), pubSHAHashed.size());
	std::string hashHex = Botan::hex_encode(hashResult);

	for (char& c : hashHex) {
		c = std::toupper(c);
	}

	return hashHex;

}

