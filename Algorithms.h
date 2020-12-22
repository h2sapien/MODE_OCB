
#ifndef UNTITLED1_ALGORITHMS_H
#define UNTITLED1_ALGORITHMS_H
#include <botan/aes.h>
#include <botan/hex.h>
#include "Funks.h"

#define tau 64

bits E(const bytes &key, const bits &text);
bits E_sub_one(const bytes &key, const bits &text);
str ocb_encrypt(const str &key, const str &nonce, const str &text);
str ocb_decrypt(const str &key, const str &nonce, const str &text);



#endif //UNTITLED1_ALGORITHMS_H
