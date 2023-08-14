#include "nCripto.h"
nSigner signer;


std::string nCripto::getStringSigned(std::string stringSigned, std::string privateKey)
{

/*	ECDSA<ECP, SHA1>::PrivateKey ecPrivateKey;
	Integer privateKeyInteger(reinterpret_cast<const byte*>(privateKey.data()), privateKey.size());
	ecPrivateKey.Initialize(ASN1::secp256k1(), privateKeyInteger);
	return signer.signMessage(
		stringSigned,
		ecPrivateKey
	);
	*/
	/*std::cout << "  # -> String Singer: " << Botan::base64_encode(reinterpret_cast<const uint8_t*>(signature.data()),
		signature.size()) << std::endl;

	return Botan::base64_encode(reinterpret_cast<const uint8_t*>(signature.data()), signature.size());*/
	return "";
}

bool nCripto::verifySignedString(std::string stringSigned, std::string signature, std::string publicKey)
{


/*ECDSA<ECP, SHA1>::PublicKey ecPublicKey;
	Integer privateKeyInteger(reinterpret_cast<const byte*>(publicKey.data()), publicKey.size());
	ecPublicKey.Initialize(ASN1::secp256k1(), privateKeyInteger);


	return signer.verifySignature(
		stringSigned,
		signature,
		ecPublicKey
	);*/	

	return true;

}


std::string nCripto::getAddressFromPublicKey(std::string publicKey)
{
	std::string pubSHAHashed = getHashSha256ToString(publicKey);
	std::string hash1w = getHashMD160ToString(pubSHAHashed);


	std::string hash1 = BMHexto58(hash1w, 58);


	int sumatoria = BMB58resumen(hash1);
	std::string clave = BMDecto58(std::to_string(sumatoria));
	std::string hash2 = hash1 + clave;


	std::cout << "  ### pubSHAHashed -->:" << pubSHAHashed << std::endl;
	std::cout << "  ### getHashMD160ToString -->:" << hash1w << std::endl;
	std::cout << "  ### encodeBase58 -->:" << hash1 << std::endl;
	std::cout << "  ### sumatoria -->:" << sumatoria << std::endl;
	std::cout << "  ### clave -->:" << clave << std::endl;
	std::cout << "  ### hash2 -->:" << hash2 << std::endl;


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
		NosoC::DivResult ResultadoDiv = BMDividir(decimalValue, alphabetnumber);
		decimalValue = ResultadoDiv.Cociente;
		int restante = ResultadoDiv.Residuo.to_u32bit();
		Resultado = AlphabetUsed[restante] + Resultado;
	}

	if (decimalValue >= alphabetnumber.to_u32bit()) {
		NosoC::DivResult ResultadoDiv = BMDividir(decimalValue, alphabetnumber);
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
	return signer.generateECKeyPair();
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

NosoC::DivResult nCripto::BMDividir(const Botan::BigInt& numerador, const Botan::BigInt& denominador)
{
	NosoC::DivResult result;
	result.Cociente = numerador / denominador;
	result.Residuo = numerador % denominador;
	return result;
}


std::string nCripto::BMDecto58(const std::string& numero) {
	Botan::BigInt decimalValue = Botan::BigInt(numero);

	NosoC::DivResult ResultadoDiv;
	std::string restante;
	std::string Resultado = "";

	while (decimalValue.bits() >= 2) {
		ResultadoDiv = BMDividir(decimalValue, 58);
		decimalValue = ResultadoDiv.Cociente;
		restante = std::to_string(ResultadoDiv.Residuo.to_u32bit());
		Resultado = NosoC::B58Alphabet[std::stoi(restante)] + Resultado;
	}

	if (decimalValue.cmp(58) >= 0) {
		ResultadoDiv = BMDividir(decimalValue, 58);
		decimalValue = ResultadoDiv.Cociente;
		restante = std::to_string(ResultadoDiv.Residuo.to_u32bit());
		Resultado = NosoC::B58Alphabet[std::stoi(restante)] + Resultado;
	}

	if (decimalValue.cmp(0) > 0) {
		Resultado = NosoC::B58Alphabet[decimalValue.to_u32bit()] + Resultado;
	}

	return Resultado;
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
	sha256.update(reinterpret_cast<const Botan::byte*>(publicKey.data()), publicKey.length());
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
	CryptoPP::RIPEMD160 ripemd;
	byte digest[CryptoPP::RIPEMD160::DIGESTSIZE];
	ripemd.CalculateDigest(digest, reinterpret_cast<const byte*>(pubSHAHashed.c_str()), pubSHAHashed.length());

	CryptoPP::HexEncoder encoder;
	std::string result;
	encoder.Attach(new CryptoPP::StringSink(result));
	encoder.Put(digest, sizeof(digest));
	encoder.MessageEnd();

	for (char& c : result) {
		c = std::toupper(c);
	}

	return result;
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

