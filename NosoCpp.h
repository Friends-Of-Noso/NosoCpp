#ifndef NOSOC_H
#define NOSOC_H

#include "nCripto.h"
#include "nUtils.h"
#include <iostream>
#include <string>
#include <vector>
#include "WalletObject.h"

class NosoCpp {
private:
	nCripto cripto;
	 nUtils utils;


public:
	 WalletObject* ImportWalletForKeys(std::string& keys);
	 WalletObject* CreateNewAddress();


	NosoCpp() = default;
	bool operator==(const NosoCpp& other) const;
};
#endif // NOSOC_H
