#include "mCripto.h"


const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

mSigner signer;


std::string  mCripto::getStringSigned(std::string stringSigned, std::string privateKey)
{
	std::vector<unsigned char> signature = signer.signMessage(
		nosoBase64Decode(stringSigned),
		base64_decode(privateKey),
		NosoC::KeyType::SECP256K1
	);

	return base64_encode(signature);
}

bool  mCripto::verifySignedString(std::string stringSigned, std::string signature, std::string publicKey)
{


	return signer.verifySignature(
		base64_decode(signature),
		nosoBase64Decode(stringSigned),
		base64_decode(publicKey),
		NosoC::KeyType::SECP256K1
	);

}



/*
* Перенести цей метод в окремий класс
*/
std::string base64_encode(const std::vector<unsigned char>& input) {
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
std::vector<unsigned char> base64_decode(const std::string& input) {
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


std::vector<unsigned char> nosoBase64Decode(const std::string& input) {

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

