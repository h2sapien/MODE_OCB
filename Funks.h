#ifndef UNTITLED1_FUNKS_H
#define UNTITLED1_FUNKS_H
#include <bitset>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <botan/hex.h>

#define bits std::vector<bool>
#define bytes std::vector<uint8_t>
#define str std::string

bits concat(const bits &bi1, const bits &bi2);

bits bytetest(const bytes &by);

bits mulx(const bits &bi);

bits hexinbit(const str &hex);

str bittohex(const bits &bi);

std::vector<bits> split(bits bi, int m);

bits XOR(const bits &bi1, const bits &bi2);

bits nfirst(const bits &bi, int n);

int ntz(const bits &bi);

bits len(int n, const bits &bi);

bits shr(const bits &bi);

bits mulxn(const bits &bi, int n);

bits divx(const bits &bi);

bytes bittest(const bits &bi);

bits shl(const bits &bi);

bits numinbit(unsigned long num);

bits nlast(const bits &bi, int n);

#endif //UNTITLED1_FUNKS_H
