#ifndef NOSOC_H
#define NOSOC_H

#include "mCripto.h"
#include <iostream>
#include <string>
#include <vector>
#include "WalletObject.h"

class NosoCpp {
private:
	 mCripto cripto;


public:
	 WalletObject* ImportWalletQR(std::string& keys);


	NosoCpp() = default;
	bool operator==(const NosoCpp& other) const;
};
#endif // NOSOC_H
