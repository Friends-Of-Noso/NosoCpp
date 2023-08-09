#include "mCripto.h"
#include <array>


const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

mSigner signer;


std::string mCripto::getStringSigned(std::string stringSigned, std::string privateKey)
{
	std::vector<unsigned char> signature = signer.signMessage(
		nosoBase64Decode(stringSigned),
		base64_decode(privateKey),
		NosoC::KeyType::SECP256K1
	);

	std::cout << "  # -> String Singer: " << base64_encode(signature) << std::endl;

	return base64_encode(signature);
}

bool mCripto::verifySignedString(std::string stringSigned, std::string signature, std::string publicKey)
{


	return true;

}


std::string mCripto::getAddressFromPublicKey(std::string publicKey)
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

std::string  mCripto::BMHexto58(const std::string& numerohex, const Botan::BigInt& alphabetnumber) {
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

Botan::BigInt mCripto::BMHexToDec(std::string numerohex) {
	std::vector<uint8_t> bytes;
	for (size_t i = 0; i < numerohex.size(); i += 2) {
		std::string byteString = numerohex.substr(i, 2);
		uint8_t byte = static_cast<uint8_t>(std::stoi(byteString, nullptr, 16));
		bytes.push_back(byte);
	}
	return Botan::BigInt(bytes.data(), bytes.size());
}

NosoC::DivResult mCripto::BMDividir(const Botan::BigInt& numerador, const Botan::BigInt& denominador)
{
	NosoC::DivResult result;
	result.Cociente = numerador / denominador;
	result.Residuo = numerador % denominador;
	return result;
}


std::string mCripto::BMDecto58(const std::string& numero) {
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


int mCripto::BMB58resumen(const std::string& numero58) {
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


/*
* Перенести цей метод в окремий класс
*/
std::string mCripto::base64_encode(const std::vector<unsigned char>& input) {
	std::string output;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	for (const auto& ch : input) {
		char_array_3[i++] = ch;
		if (i == 3) {
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; i < 4; i++) {
				output += base64_chars[char_array_4[i]];
			}

			i = 0;
		}
	}

	if (i) {
		for (j = i; j < 3; j++) {
			char_array_3[j] = '\0';
		}

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; j < i + 1; j++) {
			output += base64_chars[char_array_4[j]];
		}

		while (i++ < 3) {
			output += '=';
		}
	}

	return output;
}
/*
* Перенести цей метод в окремий класс
*/
std::vector<unsigned char> mCripto::base64_decode(const std::string& input) {
	std::vector<unsigned char> output;
	int i = 0;
	int j = 0;
	unsigned char char_array_4[4];
	unsigned char char_array_3[3];

	for (const auto& ch : input) {
		if (ch == '=') {
			break;
		}

		char_array_4[i++] = ch;
		if (i == 4) {
			for (i = 0; i < 4; i++) {
				char_array_4[i] = base64_chars.find(char_array_4[i]);
			}

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; i < 3; i++) {
				output.push_back(char_array_3[i]);
			}

			i = 0;
		}
	}

	if (i) {
		for (j = i; j < 4; j++) {
			char_array_4[j] = 0;
		}

		for (j = 0; j < 4; j++) {
			char_array_4[j] = base64_chars.find(char_array_4[j]);
		}

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; j < i - 1; j++) {
			output.push_back(char_array_3[j]);
		}
	}

	return output;
}

std::string mCripto::getHashSha256ToString(std::string publicKey)
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

std::string mCripto::getHashMD160ToString(std::string pubSHAHashed)
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


std::vector<unsigned char> mCripto::nosoBase64Decode(const std::string& input) {

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

