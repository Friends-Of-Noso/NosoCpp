# NosoC++
NosoC++ is a C++ cryptographic library that provides various cryptographic functions to work with the Noso coin.

# Getting Started
#### Prerequisites
C++ Compiler (e.g., g++, Visual Studio)

# Usage
### Include the necessary headers in your C++ code:
```cpp
#include <NosoCpp.h>
NosoCpp noso;
```
Use the provided functions to perform cryptographic operations:
```cpp
// Example: Get the WalletObject from the ready keys
WalletObject* wallet = noso.ImportWalletForKeys(walletToken);

// Example: Generate a new WalletObject
WalletObject* wallet = noso.CreateNewAddress();
```



# Used Libraries

| Library   | URL                             |
| --------- | ------------------------------- |
| Botan     | [https://botan.randombit.net/](https://botan.randombit.net/) |


# Contribution

Your contributions are welcome! Please review the Contribution Guidelines for more details on contributing to the project.

# License

This project is licensed under the MIT License.

I hope this helps. If you're still having trouble, please let me know, and I'll do my best to assist you.
