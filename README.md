# NosoC++
NosoC++ is a cryptographic library in C++ that provides various cryptographic functionalities such as encryption, decryption, hashing, and digital signatures.

# Getting Started

#### Prerequisites

C++ Compiler (e.g., g++, Visual Studio)


# Usage

### Include the necessary headers in your C++ code:
```
#include <NosoCpp.h>
NosoCpp noso;
```
Use the provided functions to perform cryptographic operations:
```
// Example: Get the WalletObject from the ready keys
WalletObject* wallet = noso.ImportWalletForKeys(walletToken);

// Example: Generate a new WalletObject
WalletObject* wallet = noso.CreateNewAddress();
```



# Used Libraries

| Library   | URL                             |
| --------- | ------------------------------- |
| Crypto++  | [https://www.cryptopp.com/](https://www.cryptopp.com/) |
| Botan     | [https://botan.randombit.net/](https://botan.randombit.net/) |


# Contribution

Your contributions are welcome! Please review the Contribution Guidelines for more details on contributing to the project.

# License

This project is licensed under the MIT License.

I hope this helps. If you're still having trouble, please let me know, and I'll do my best to assist you.
