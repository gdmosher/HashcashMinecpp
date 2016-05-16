/*
 **************************************************************************
 *                                                                        *
 *          General Purpose Hash Function Algorithms Library              *
 *                                                                        *
 * Author: Arash Partow - 2002                                            *
 * URL: http://www.partow.net                                             *
 * URL: http://www.partow.net/programming/hashfunctions/index.html        *
 *                                                                        *
 * Copyright notice:                                                      *
 * Free use of the General Purpose Hash Function Algorithms Library is    *
 * permitted under the guidelines and in accordance with the most current *
 * version of the Common Public License.                                  *
 * http://www.opensource.org/licenses/cpl1.0.php                          *
 *                                                                        *
 **************************************************************************
*/
// 2016-0430 added declaration of BloomFilter (at the end of this file)


#ifndef INCLUDE_GENERALHASHFUNCTION_CPP_H
#define INCLUDE_GENERALHASHFUNCTION_CPP_H


#include <string>
#include <vector>
#include <stdint.h>

typedef unsigned int (*HashFunction)(const std::string&);


unsigned int RSHash  (const std::string& str);
unsigned int JSHash  (const std::string& str);
unsigned int PJWHash (const std::string& str);
unsigned int ELFHash (const std::string& str);
unsigned int BKDRHash(const std::string& str);
unsigned int SDBMHash(const std::string& str);
unsigned int DJBHash (const std::string& str);
unsigned int DEKHash (const std::string& str);
unsigned int BPHash  (const std::string& str);
unsigned int FNVHash (const std::string& str);
unsigned int APHash  (const std::string& str);

// from blog.michaelschmatz.com ... how to write a bloom filter
class BloomFilter {
public:
//	BloomFilter(uint32_t size, uint8_t numHashes);
	BloomFilter::BloomFilter(uint32_t size, uint8_t numHashes=9) : m_bits(size), m_size(size), m_numHashes(numHashes) {}

	void add(const std::string& str);
	bool possiblyContains(const std::string& str) const;
private:
//	/*uint8_t */int m_numHashes = 500;		// ditch uint8_t for type conversion hassels and incompat w/ cout
//	uint8_t m_numHashes = (uint8_t)500;
	int m_numHashes;
	std::vector<bool> m_bits;				// This is a cool way to init a member object
	uint32_t m_size;
//	uint32_t m_elementsInSet = 0;
//	uint32_t my_numHashes = 9;
	int m = m_size;
	int n = 0;
	int k = m_numHashes;


};

#endif
