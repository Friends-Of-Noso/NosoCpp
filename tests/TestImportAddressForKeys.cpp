#include <iostream>
using namespace std;

#include "NosoAddress.h"
#include "WalletObject.h"


using namespace NosoCpp;


int TestImportAddressForKeys(int argc, char **argv){

    WalletObject* address = NosoCpp::restoreAddressFromKeysPair("BGBXhym1qvfZ7mYHR5Lp69YTqzmOnDf7uXFNTWk7yMr/OQJLawMGJO2XwTu3liEtY+4STrYnI1laRZ8kZSvkANE= GhUmXvEp2I3nBBoUgqRhU41LPy9CbNz8drshf3Du68E=");

    if(address) {
        return 0;
    } else {
        return 1;
    }
}
