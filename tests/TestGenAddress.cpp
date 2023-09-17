#include <iostream>
using namespace std;

#include "NosoCpp.h"
#include "WalletObject.h"


using namespace NosoCpp;


int TestGenAddress(int argc, char **argv){

    WalletObject* address = NosoCpp::CreateNewAddress();

    if(address && address->PrivateKey.length() == 44 && address->PublicKey.length() == 88) {
        return 0;
    } else {
        return 1;
    }
}
