#pragma once
#include <string>
#include <map>
#include <algorithm>

#include "GenerateKey.h"
#include "Alphabet.h"

class Cipher
{
public:
   /*Конструктор
   *
   * Принимает ссылку на алфавит
   */
   Cipher(Alphabet* alphabet)
   {
      _alphabet = alphabet;
      GenerateKey::PairKeys pair = generate.Generate();
      publicKey = pair.publicKey;
      primaryKey = pair.primaryKey;
   }

   /*Зашифровывает сообщение
   *
   * Принимает строку сообщения
   *
   * Возвращает вектор чисел, соответствующий
   * зашифрованному сообщению*/
   std::vector<uint64_t> Encrypt(std::string srcTxt, GenerateKey::Key publicKey)
   {
      std::vector<uint64_t> sequence =
         convertStrToVec(srcTxt, publicKey.mod);

      for (size_t i = 0; i < sequence.size(); i++)
      {
         sequence[i] = modexp(sequence[i], publicKey.exp,
            publicKey.mod);
      }
      return sequence;
   }

   /*Получить открытый ключ
   *
   * Ничего не принимает
   *
   * Возвращает открытый ключ*/
   GenerateKey::Key GetPublicKey()
   {
      return publicKey;
   }

   /*Расшифровывает сообщение
   *
   * Принимает вектор чисел, соответствующий
   * зашифрованному сообщению
   *
   * Возвращает расшифрованно сообщение*/
   std::string Decrypt(std::vector<uint64_t> sequence)
   {
      for (size_t i = 0; i < sequence.size(); i++)
      {
         sequence[i] = modexp(sequence[i], primaryKey.exp, primaryKey.mod);
      }
      std::string txt = convertVecToStr(sequence, primaryKey.mod);
      return txt;
   }

private:
   GenerateKey generate;
   GenerateKey::Key primaryKey;
   GenerateKey::Key publicKey;
   Alphabet* _alphabet;

   /*Высчитывает чисел в степени по модулю
   *
   * Принимает основание, степень и модуль
   *
   * Возвращает вычисленное значение */
   uint64_t modexp(uint64_t base, uint64_t extent, uint64_t mod)
   {
      if (extent == 0) return 1;
      uint64_t tmp = modexp(base, extent / 2, mod);
      if (extent % 2 == 0)
         return (tmp * tmp) % mod;
      else
         return (base * tmp * tmp) % mod;
   }

   /*Преобразует строку в вектор чисел
   *
   * Принимает строку и модуль
   *
   * Возвращает вектор чисел*/
   std::vector<uint64_t> convertStrToVec(std::string srcTxt, uint64_t mod)
   {
      std::map<char, uint64_t> alphabet = _alphabet->GetAlphabet();
      //Добавление в начало случайного символа
      std::vector<uint64_t> sequence;
      sequence.push_back(rand() % 255);
      for (size_t i = 0; i < srcTxt.size(); i++)
      {
         //Смешивание предыдущего числа в последовательности с текущем
         sequence.push_back((sequence[i] + alphabet[srcTxt[i]]) % mod);
      }
      return sequence;
   }

   /*Преобразует вектор чисел в строку
   *
   * Принимает  вектор чисел и модуль
   *
   * Возвращает строку*/
   std::string convertVecToStr(std::vector<uint64_t> sequence, uint64_t mod)
   {
      std::map<char, uint64_t> alphabet = _alphabet->GetAlphabet();
      std::string txt;
      for (int i = sequence.size() - 1; i > 0; i--)
      {
         //"Распутывает" текущий символ от предыдущего
         sequence[i] = (sequence[i] - sequence[i - 1]) % mod;

         //Поиск символа в алфавите
         auto begin = alphabet.begin();
         while (begin != alphabet.end())
         {
            if ((*begin).second == sequence[i])
            {
               auto beginStr = txt.begin();
               txt.insert(beginStr, begin->first);
               break;
            }
            ++begin;
         }
      }
      return txt;
   }
};