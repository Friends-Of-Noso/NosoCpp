/*
 * This code is licensed under the terms of the MIT License.
 *
 * Author: pasichDev
 * Repository: https://github.com/pasichDev/NosoCpp
 *
 * See LICENSE file for details.
 */
#ifndef NUTILS_H
#define NUTILS_H


#include <string>
#include "Objects.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace NosoCppUtils {
	NosoC::KeyPair StringTokenizer(string keys);

	bool checkSizesKeyPair(NosoC::KeyPair keys);
}

#endif
