#pragma once

#include <vector>
#include <cmath>

// Генератор пары открытого и закрытого ключей
class GenerateKey
{
   // Два простых числа 
   // для генерации ключей
   struct PairPrime
   {
      uint64_t p, q;
   };

   // Результат расширенного алгоритма 
   // Евклида
   struct ResultGSDAdv
   {
      uint64_t a;
      int64_t adXi, adYi;
   };
   //------------------------------------------------------
public:
   struct Key
   {
      uint64_t exp, mod;
   };

   struct PairKeys
   {
      Key publicKey, primaryKey;
   };
   //------------------------------------------------------

   GenerateKey()
   {
      primes = sieveSundarama(500);
   }
   //------------------------------------------------------

   ~GenerateKey()
   {
      primes.clear();
   }
   //------------------------------------------------------

   /*Генерирует открытый и закрытый ключи
   *
   * Ничего не принимает
   *
   * Возвращает пару: открытый и закрытый ключи*/
   PairKeys Generate()
   {
      PairPrime pairPrime = generatePairPrime();
      uint64_t n = pairPrime.p * pairPrime.q;
      uint64_t funcEuler = (pairPrime.p - 1) *
         (pairPrime.q - 1);

      uint64_t publicExp = selectPublicExp(funcEuler);
      uint64_t primaryExp = calcInvNum(publicExp,
         funcEuler);
      PairKeys pair =
      {
         { publicExp, n },
         { primaryExp, n }
      };
      return pair;
   }
   //------------------------------------------------------

private:
   std::vector<uint64_t> primes;

   /*Вычисляет обратный элемент числа по модулю
   *
   * Принимает числа num и модуль mod
   *
   * Возвращает вычисленное значение обратного числа */
   uint64_t calcInvNum(uint64_t num, uint64_t mod)
   {
      ResultGSDAdv result;
      result = gsdAdvance(mod, num);
      while (result.adYi < 0)
         result.adYi += mod;
      return result.adYi;

      /*if (mod >= num)
      {
         result = gsdAdvance(mod, num);
      while (result.adYi < 0)
         result.adYi += mod;
      return result.adYi;
      }
      else
      {
         result = gsdAdvance(num, mod);
         while (result.adXi < 0)
            result.adXi += mod;
         return result.adXi;
      }*/
   }
   //------------------------------------------------------

   /*Выбор открытой экспоненты
   *
   * Принимает значение функции эйлера
   *
   * Возвращает открытую экспоненту*/
   uint64_t selectPublicExp(uint64_t funcEuler)
   {
      size_t bound = 30;
      uint64_t exp = 0;
      while (true)
      {
         exp = primes[rand() % bound];
         if (funcEuler > exp && checkMutuallyPrime(funcEuler, exp))
            break;
      }
      return exp;
   }
   //------------------------------------------------------

   //Вычисляет значения по расширенному алгоритму евклида
   ResultGSDAdv gsdAdvance(uint64_t a, uint64_t b,
      int64_t x1 = 0, int64_t x2 = 1, int64_t y1 = 1, 
      int64_t y2 = 0)
   {
      if (b == 0) {
         return { a, x2, y2 };
      }
      else {
         uint64_t tmp = a % b;
         uint64_t addiv = a / b;
         a = b;
         b = tmp;

         int64_t adXi = x2 - addiv * x1;
         int64_t adYi = y2 - addiv * y1;

         return gsdAdvance(a, b, adXi, x1, adYi, y1);
      }
   }
   //------------------------------------------------------

   /*Проверка на взаимную простоту чисел
   *
   * Принимает два числа a и b
   * 
   * Возвращает true если числа взаимно простые и 
   * false в противном случае*/
   bool checkMutuallyPrime(uint64_t a, uint64_t b)
   {
      uint64_t res = a > b ?
         gsdAdvance(a, b, 0, 1, 1, 0).a :
         gsdAdvance(b, a, 0, 1, 1, 0).a;
      return res == 1 ? true : false;
   }
   //------------------------------------------------------

   //Генерирует пару простых чисел
   PairPrime generatePairPrime()
   {
      size_t size = primes.size();
      size_t firstQuarter = size / 4;
      size_t indp = firstQuarter + (rand() % (size - firstQuarter)),
         indq = firstQuarter + (rand() % (size - firstQuarter));
      return { primes[indp], primes[indq] };
   }
   //------------------------------------------------------

   /*Высчитывает простые числа до maxNum*2 
   *
   * Принимает максимальное значение maxNum
   * 
   * Возвращает вектор простых чисел*/
   std::vector<uint64_t> sieveSundarama(uint64_t maxNum)
   {
      const uint64_t len = maxNum + 1;
      std::vector<uint64_t> primes(len + 1);

      // Записываем все числа в вектор
      for (uint64_t i = 0; i <= len; ++i)
      {
         primes[i] = i;
      }

      // Вычеркиваем те, что соответствуют критерию 
      uint64_t bound = ((uint64_t)sqrt(2 * maxNum + 1) - 1) / 2;
      for (uint64_t i = 1; i <= bound; i++)
      {
         for (uint64_t j = i; j <= (maxNum - i) / (2 * i + 1); j++)
         {
            if (i + j + 2 * i * j <= maxNum)
            {
               primes[i + j + 2 * i * j] = 0;
            }
         }
      }

      std::vector<uint64_t> result;
      result.push_back(2);

      // Оставшиеся числа умножаем на 2 и складываем с 1
      // и записываем в результат
      for (size_t i = 0; i < primes.size(); i++)
      {
         if (primes[i] != 0)
            result.push_back(primes[i] * 2 + 1);
      }

      return result;
   }
};