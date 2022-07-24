# RSA

The algorithm allows you to encrypt and decrypt the message.

***
# How to use

You need to create an instance of a class that implements an abstract `Alphabet class` (e.g. the `RusAlphabet` class).
Create an instance of the `Cipher` class, when creating, pass a reference to an instance of the `Alphabet` class.

**File: main.cpp**
```c++
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
```

<img width="453" alt="image" src="https://user-images.githubusercontent.com/78900834/180651933-79be4949-b8c2-4529-98af-413cf3d91c20.png">
