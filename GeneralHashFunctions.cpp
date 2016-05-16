#include "GeneralHashFunctions.h"
#include <iostream>

// 2016-0430 added definition/implementation of BloomFilter (at the end of this file)
unsigned int RSHash(const std::string& str)
{
   unsigned int b    = 378551;
   unsigned int a    = 63689;
   unsigned int hash = 0;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = hash * a + str[i];
      a    = a * b;
   }

   return hash;
}
/* End Of RS Hash Function */


unsigned int JSHash(const std::string& str)
{
   unsigned int hash = 1315423911;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash ^= ((hash << 5) + str[i] + (hash >> 2));
   }

   return hash;
}
/* End Of JS Hash Function */


unsigned int PJWHash(const std::string& str)
{
   unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
   unsigned int ThreeQuarters     = (unsigned int)((BitsInUnsignedInt  * 3) / 4);
   unsigned int OneEighth         = (unsigned int)(BitsInUnsignedInt / 8);
   unsigned int HighBits          = (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
   unsigned int hash              = 0;
   unsigned int test              = 0;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = (hash << OneEighth) + str[i];

      if((test = hash & HighBits)  != 0)
      {
         hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
      }
   }

   return hash;
}
/* End Of  P. J. Weinberger Hash Function */


unsigned int ELFHash(const std::string& str)
{
   unsigned int hash = 0;
   unsigned int x    = 0;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = (hash << 4) + str[i];
      if((x = hash & 0xF0000000L) != 0)
      {
         hash ^= (x >> 24);
      }
      hash &= ~x;
   }

   return hash;
}
/* End Of ELF Hash Function */


unsigned int BKDRHash(const std::string& str)
{
   unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
   unsigned int hash = 0;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = (hash * seed) + str[i];
   }

   return hash;
}
/* End Of BKDR Hash Function */


unsigned int SDBMHash(const std::string& str)
{
   unsigned int hash = 0;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = str[i] + (hash << 6) + (hash << 16) - hash;
   }

   return hash;
}
/* End Of SDBM Hash Function */


unsigned int DJBHash(const std::string& str)
{
   unsigned int hash = 5381;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = ((hash << 5) + hash) + str[i];
   }

   return hash;
}
/* End Of DJB Hash Function */


unsigned int DEKHash(const std::string& str)
{
   unsigned int hash = static_cast<unsigned int>(str.length());

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = ((hash << 5) ^ (hash >> 27)) ^ str[i];
   }

   return hash;
}
/* End Of DEK Hash Function */


unsigned int BPHash(const std::string& str)
{
   unsigned int hash = 0;
   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = hash << 7 ^ str[i];
   }

   return hash;
}
/* End Of BP Hash Function */


unsigned int FNVHash(const std::string& str)
{
   const unsigned int fnv_prime = 0x811C9DC5;
   unsigned int hash = 0;
   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash *= fnv_prime;
      hash ^= str[i];
   }
//   hash %= 100;
//   std::cout << "FNV Hash: " << hash << std::endl;
   return hash;
}
/* End Of FNV Hash Function */


unsigned int APHash(const std::string& str)
{
   unsigned int hash = 0xAAAAAAAA;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ str[i] * (hash >> 3)) :
                               (~((hash << 11) + (str[i] ^ (hash >> 5))));
   }
//   hash %= 100;
   std::cout << " AP Hash: " << hash << std::endl;
   return hash;
}
/* End Of AP Hash Function */


void BloomFilter::add(const std::string& str) {
/*	unsigned int hash1 = FNVHash(str);
	unsigned int hash2 = APHash(str);
	m_bits[hash1] = true;
	m_bits[hash2] = true;
*/
	m_bits[BKDRHash(str) % m] = true;
	m_bits[ BPHash(str) % m] = true;
	m_bits[DEKHash(str) % m] = true;
	m_bits[DJBHash(str) % m] = true;
	m_bits[ELFHash(str) % m] = true;
	m_bits[ JSHash(str) % m] = true;
	m_bits[PJWHash(str) % m] = true;
	m_bits[FNVHash(str) % m] = true;
	m_bits[APHash(str) % m] = true;
	n++;								//	m_elementsInSet++;
	if (m <= 100 && n <= 50) {
		std::cout << "My bits ";
		for (int i = 0; i < m; i++) {
			std::cout << m_bits[i];
		}
		std::cout << std::endl;
	}
}
bool BloomFilter::possiblyContains(const std::string& str) const {
	bool notInSet = false;
	if (m_bits[BKDRHash(str) % m] == false) { notInSet = true; }
	else if (m_bits[BPHash(str) % m] == false) { notInSet = true; }
	else if (m_bits[DEKHash(str) % m] == false) { notInSet = true; }
	else if (m_bits[DJBHash(str) % m] == false) { notInSet = true; }
	else if (m_bits[ELFHash(str) % m] == false) { notInSet = true; }
	else if (m_bits[JSHash(str) % m] == false) { notInSet = true; }
	else if (m_bits[PJWHash(str) % m] == false) { notInSet = true; }
	else if (m_bits[FNVHash(str) % m] == false) { notInSet = true; }
	else if (m_bits[APHash(str) % m] == false) { notInSet = true; }


	if (notInSet) {
		std::cout << str << " is definately not in the set." << std::endl;
		return false;
	}

	double falsePosPercent = pow(1 - exp(-k*n / (double)m), k);			//force floating point divide
	std::cout << "Number of bits:" << m << std::endl;
	std::cout << "Number of elements in set:" << n << std::endl;
	std::cout << "Number of hashes:" << k << std::endl;
//	std::cout << "Number of hashes:" << (int)m_numHashes << std::endl;
	std::cout << str << " may be in the set." << std::endl;
	std::cout << "Probability of a false positive: " << 100*pow(1 - exp(-k*(n+0.0) / m), k) << "% " << falsePosPercent << std::endl;
	return true;
}
