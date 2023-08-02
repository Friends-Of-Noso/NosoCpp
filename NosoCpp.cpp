#include "pch.h"
#include "NosoCpp.h"

mCripto cripto;


WalletObject* NosoCpp::ImportWalletQR(std::string& keys) {
    std::vector<std::string> tokens;
    std::string delimiter = " ";
    size_t pos = 0;

    // Split the keys string using the delimiter " " (space)
    while ((pos = keys.find(delimiter)) != std::string::npos) {
        std::string token = keys.substr(0, pos);
        tokens.push_back(token);
        keys.erase(0, pos + delimiter.length());
    }
    tokens.push_back(keys);

    if (tokens.size() == 2) {
        std::string publicKey = tokens[0];
        std::string privateKey = tokens[1];

      //  std::string testSignature = mCripto::GetStringSigned("VERIFICATION", privateKey);

      //  bool verification = mCripto::VerifySignedString("VERIFICATION", testSignature, publicKey);

       // std::cout << "testSignature => " << testSignature << "\n";
       // std::cout << "verification => " << verification << "\n";
        std::cout << "---------------------------------------------------------------------\n";

     /*  if (verification) {
            WalletObject* walletObject = new WalletObject();
            walletObject->PublicKey = publicKey;
            walletObject->PrivateKey = privateKey;
            walletObject->Hash = mCripto::GetAddressFromPublicKey(publicKey);
            return walletObject;
        }*/ 
    }

    return nullptr;
}




bool NosoCpp::operator==(const NosoCpp& other) const
{
    return false;
}
