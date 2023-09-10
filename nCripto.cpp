#include "nCripto.h"


std::string nCripto::getAddressFromPublicKey(std::string publicKey)
{
	std::string pubSHAHashed = getHashSha256ToString(publicKey);
	std::string hash1 = getHashMD160ToString(pubSHAHashed);
	hash1 = BMHexto58(hash1, 58);
	int sumatoria = BMB58resumen(hash1);
	std::string clave = BMDecto58(std::to_string(sumatoria));
	std::string hash2 = hash1 + clave;

	return NosoC::CoinChar + hash2;
}

std::string  nCripto::BMHexto58(const std::string& numerohex, const Botan::BigInt& alphabetnumber) {
	Botan::BigInt decimalValue = BMHexToDec(numerohex);
	std::string Resultado = "";
	std::string AlphabetUsed;

	if (alphabetnumber == 36) {
		AlphabetUsed = NosoC::B36Alphabet;
	}
	else {
		AlphabetUsed = NosoC::B58Alphabet;
	}

	while (decimalValue.bits() >= 2) {
		NosoC::DivResult ResultadoDiv = DivideBigInt(decimalValue, alphabetnumber);
		decimalValue = ResultadoDiv.Cociente;
		int restante = ResultadoDiv.Residuo.to_u32bit();
		Resultado = AlphabetUsed[restante] + Resultado;
	}

	if (decimalValue >= alphabetnumber.to_u32bit()) {
		NosoC::DivResult ResultadoDiv = DivideBigInt(decimalValue, alphabetnumber);
		decimalValue = ResultadoDiv.Cociente;
		int restante = ResultadoDiv.Residuo.to_u32bit();
		Resultado = AlphabetUsed[restante] + Resultado;
	}

	if (decimalValue > 0) {
		int value = decimalValue.to_u32bit();
		Resultado = AlphabetUsed[value] + Resultado;
	}

	return Resultado;
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
	std::vector<unsigned char> messages = nosoBase64Decode("VERIFICATION");
	Botan::secure_vector<uint8_t> decodedPrivatKey = Botan::base64_decode(privateKey);
	Botan::AlgorithmIdentifier alg_id("ECDSA", Botan::AlgorithmIdentifier::USE_NULL_PARAM);

	try {
		Botan::BigInt private_key_value = Botan::BigInt::decode(decodedPrivatKey.data(), decodedPrivatKey.size());
		Botan::EC_Group secp256k1("secp256k1");
		Botan::ECDSA_PrivateKey private_key(rng, secp256k1, private_key_value);
		Botan::PK_Signer signer(private_key, rng, NosoC::emsa, Botan::DER_SEQUENCE);
		signer.update(messages);
		std::vector<uint8_t> signature = signer.signature(rng);
		
		std::string signature_base64 = Botan::base64_encode(signature.data(), signature.size());

		return  signature_base64;
	}


	catch (const std::exception& ex)
	{
		std::cerr << "Error: " << ex.what() << std::endl;
		return ex.what();
	}
}

bool nCripto::verifySignedString(const std::string& message, const std::string signatureBase64, const std::string publicKey)
{
	Botan::AutoSeeded_RNG rng;
	Botan::secure_vector<uint8_t> decodedPublicKey = Botan::base64_decode(publicKey);
	Botan::secure_vector<uint8_t> signature = Botan::base64_decode(signatureBase64.data(), signatureBase64.size());
	std::vector<unsigned char> messages = nosoBase64Decode("VERIFICATION");

	if (decodedPublicKey.size() != 65) {
		std::cerr << "Invalid UNCOMPRESSED public key format" << std::endl;
		return false;
	}
	try {
		std::vector<uint8_t> xCoord(decodedPublicKey.begin() + 1, decodedPublicKey.begin() + 33);
		std::vector<uint8_t> yCoord(decodedPublicKey.begin() + 33, decodedPublicKey.end());

		Botan::BigInt x_bigint(xCoord.data(), xCoord.size());
		Botan::BigInt y_bigint(yCoord.data(), yCoord.size());

		Botan::EC_Group secp256k1("secp256k1");

		Botan::PointGFp point = secp256k1.point(x_bigint, y_bigint);

		Botan::ECDSA_PublicKey publicKey(secp256k1, point);
		Botan::PK_Verifier verifier(publicKey, NosoC::emsa, Botan::DER_SEQUENCE);
		verifier.update(messages);

		return verifier.check_signature(signature);
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Error: " << ex.what() << std::endl;
		return false; 
	}
}




Botan::BigInt nCripto::BMHexToDec(std::string numerohex) {
	std::vector<uint8_t> bytes;
	for (size_t i = 0; i < numerohex.size(); i += 2) {
		std::string byteString = numerohex.substr(i, 2);
		uint8_t byte = static_cast<uint8_t>(std::stoi(byteString, nullptr, 16));
		bytes.push_back(byte);
	}
	return Botan::BigInt(bytes.data(), bytes.size());
}

NosoC::DivResult nCripto::DivideBigInt(const Botan::BigInt& numerator, const Botan::BigInt& denominator)
{
	NosoC::DivResult result;
	result.Cociente = numerator / denominator;
	result.Residuo = numerator % denominator;
	return result;
}


std::string nCripto::BMDecto58(const std::string& numero) {
	Botan::BigInt decimalValue = Botan::BigInt(numero);
	NosoC::DivResult resultDiv;
	std::string restante;
	std::string result = "";

	while (decimalValue.bits() >= 2) {
		resultDiv = DivideBigInt(decimalValue, 58);
		decimalValue = resultDiv.Cociente;
		restante = std::to_string(resultDiv.Residuo.to_u32bit());
		result = NosoC::B58Alphabet[std::stoi(restante)] + result;
	}

	if (decimalValue.cmp(58) >= 0) {
		resultDiv = DivideBigInt(decimalValue, 58);
		decimalValue = resultDiv.Cociente;
		restante = std::to_string(resultDiv.Residuo.to_u32bit());
		result = NosoC::B58Alphabet[std::stoi(restante)] + result;
	}

	if (decimalValue.cmp(0) > 0) {
		result = NosoC::B58Alphabet[decimalValue.to_u32bit()] + result;
	}

	return result;
}


int nCripto::BMB58resumen(const std::string& numero58) {
	int total = 0;

	for (size_t i = 0; i < numero58.length(); i++) {
		char currentChar = numero58[i];
		size_t foundIndex = NosoC::B58Alphabet.find(currentChar);

		if (foundIndex != std::string::npos) {
			total += static_cast<int>(foundIndex);
		}
	}

	return total;
}

std::string nCripto::getHashSha256ToString(std::string publicKey)
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

std::string nCripto::getHashMD160ToString(std::string pubSHAHashed)
{
	Botan::RIPEMD_160 hash;
	Botan::secure_vector<uint8_t> hashResult = hash.process(reinterpret_cast<const uint8_t*>(pubSHAHashed.data()), pubSHAHashed.size());
	std::string hashHex = Botan::hex_encode(hashResult);

	for (char& c : hashHex) {
		c = std::toupper(c);
	}

	return hashHex;

}
std::vector<unsigned char> nCripto::nosoBase64Decode(const std::string& input) {

	std::vector<int> indexList;
	for (char c : input) {
		auto it = NosoC::B64Alphabet.find(c);
		if (it != std::string::npos) {
			indexList.push_back(static_cast<int>(it));
		}
	}

	std::string binaryString;
	for (int i : indexList) {
		std::string binary = std::bitset<6>(i).to_string();
		binaryString += binary;
	}

	std::string strAux = binaryString;
	std::vector<unsigned char> tempByteArray;

	while (strAux.length() >= 8) {
		std::string currentGroup = strAux.substr(0, 8);
		int intVal = std::stoi(currentGroup, nullptr, 2);
		tempByteArray.push_back(static_cast<unsigned char>(intVal));
		strAux = strAux.substr(8);
	}

	return tempByteArray;
}

