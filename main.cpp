#include <ctime>
#include <iostream>
#include <cstdlib>

#include "Cipher.h"
#include "RusAlphabet.h"


int main()
{
   system("chcp 1251");
   srand(time(nullptr));

   RusAlphabet alphabet;
   Cipher cipher(&alphabet);

   std::cout << "Input text: ";
   std::string text;
   std::getline(std::cin, text);

   GenerateKey::Key key = cipher.GetPublicKey();
   std::vector<uint64_t> encTxt = cipher.Encrypt(text, key);
   
   std::cout << "Encrypted text: ";
   for (uint64_t value : encTxt)
      std::cout << value;
   std::cout << std::endl;

   std::string srcText = cipher.Decrypt(encTxt);
   std::cout << "Decrypted text: " << srcText;
}
