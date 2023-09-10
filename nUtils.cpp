/*
 * This code is licensed under the terms of the MIT License.
 *
 * Author: pasichDev
 * Repository: https://github.com/pasichDev/NosoCpp
 *
 * See LICENSE file for details.
 */
#include "nUtils.h"

NosoC::KeyPair NosoCppUtils::StringTokenizer(std::string keys)
{
	std::vector<std::string> tokens;
	std::string delimiter = " ";
	size_t pos = 0;

	while ((pos = keys.find(delimiter)) != std::string::npos) {
		std::string token = keys.substr(0, pos);
		tokens.push_back(token);
		keys.erase(0, pos + delimiter.length());
	}
	tokens.push_back(keys);

	if (tokens.size() == 2) {
		return { tokens[0],tokens[1] };
	}
	else {
		return NosoC::KeyPair();
	}

}


/*
* Checks the key sizes in a pair
* Returns true if the dimensions match the expected values
* Otherwise, it returns false
*/
bool NosoCppUtils::checkSizesKeyPair(NosoC::KeyPair keys)
{

	if (keys.PrivateKey.length() == 44 && keys.PublicKey.length() == 88) {
		return true;
	}

	return false;
}
