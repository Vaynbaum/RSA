#pragma once
#include <map>
#include <string>

#include "Alphabet.h"

class RusAlphabet : public Alphabet
{
public:
   /*�����������
   *
   * �������������� ������� �������� ���������*/
   RusAlphabet() :Alphabet()
   {
      size_t i = (alphabet.rbegin())->second + 1;
      std::string alph = "�����Ũ����������������������������������������������������������";

      for (char ch : alph)
         alphabet[ch] = i++;
   }

   /*����������, ��������� �������
   * 
   * ������ �� ���������
   */
   ~RusAlphabet()
   {
      alphabet.clear();
   }

   /*���������� �������
   *
   * ������ �� ���������*/
   std::map<char, uint64_t> GetAlphabet() override
   {
      return alphabet;
   }
};