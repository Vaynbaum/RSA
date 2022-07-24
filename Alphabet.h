#pragma once
#include <map>

class Alphabet
{
public:
   
   /*Конструктор
   *
   * Инициализиурет алфавит общими символами*/
   Alphabet()
   {
      size_t i = 2;
      alphabet[' '] = i++;
      for (char ch = '0'; ch <= '9'; ch++)
         alphabet[ch] = i++;
   }
   /*Возвращает алфавит
   * 
   * Ничего не принимает*/
   virtual std::map<char, uint64_t> GetAlphabet()=0;
protected:
   std::map<char, uint64_t> alphabet;
};