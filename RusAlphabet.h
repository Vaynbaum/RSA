#pragma once
#include <map>
#include <string>

#include "Alphabet.h"

class RusAlphabet : public Alphabet
{
public:
   /*Конструктор
   *
   * Инициализиурет алфавит русскими символами*/
   RusAlphabet() :Alphabet()
   {
      size_t i = (alphabet.rbegin())->second + 1;
      std::string alph = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя";

      for (char ch : alph)
         alphabet[ch] = i++;
   }

   /*Деструктор, очищающий алфавит
   * 
   * Ничего не принимает
   */
   ~RusAlphabet()
   {
      alphabet.clear();
   }

   /*Возвращает алфавит
   *
   * Ничего не принимает*/
   std::map<char, uint64_t> GetAlphabet() override
   {
      return alphabet;
   }
};