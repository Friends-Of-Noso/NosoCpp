#include <iostream>
#include <NosoAddress.h>

int main() {
    std::cout << "Hello, World!" << std::endl;
    string add = "BGBXhym1qvfZ7mYHR5Lp69YTqzmOnDf7uXFNTWk7yMr/OQJLawMGJO2XwTu3liEtY+4STrYnI1laRZ8kZSvkANE= GhUmXvEp2I3nBBoUgqRhU41LPy9CbNz8drshf3Du68E=";
    NosoCpp::restoreAddressFromKeysPair(add);
    return 0;
}
