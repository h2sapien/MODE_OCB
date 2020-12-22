#include "Algorithms.h"


bits E(const bytes &key, const bits &text) {
    std::unique_ptr<Botan::BlockCipher> aes(Botan::BlockCipher::create("AES-128"));
    bytes block = bittest(text);
    aes->set_key(key);
    aes->encrypt(block);
    return bytetest(block);
}

bits E_sub_one(const bytes &key, const bits &text) {
    std::unique_ptr<Botan::BlockCipher> aes(Botan::BlockCipher::create("AES-128"));
    bytes block = bittest(text);
    aes->set_key(key);
    aes->decrypt(block);
    return bytetest(block);
}

str ocb_encrypt(const str &key, const str &nonce, const str &text) {
    bytes K = Botan::hex_decode(key);
    bits N = hexinbit(nonce);
    bits MM = hexinbit(text);
    int n = N.size();
    int m = std::max(1, (int) std::ceil((double) MM.size() / n));
    std::vector<bits> Z(m);
    std::vector<bits> C(m);
    std::vector<bits> M = split(MM, m);
    bits L = E(K, bits(n));
    bits R = E(K, XOR(N, L));
    Z[0] = XOR(L, R);
    for (int i = 1; i < m; ++i)
        Z[i] = XOR(Z[i - 1], mulxn(L, ntz(numinbit(i + 1))));
    for (int i = 0; i < m - 1; ++i)
        C[i] = XOR(E(K, XOR(M[i], Z[i])), Z[i]);
    bits x = XOR(XOR(len(n, M.back()), divx(L)), Z.back());
    bits y = E(K, x);
    C.back() = XOR(y, M.back());
    bits CC = C[0];
    if (m > 1)
        for (int i = 1; i < m; ++i)
            CC = concat(CC, C[i]);
    bits checksum = M[0];
    if (m > 1)
        for (int i = 1; i < m - 1; ++i)
            checksum = XOR(checksum, M[i]);
    checksum = XOR(XOR(checksum, concat(C.back(), bits(n - C.back().size()))), y);
    bits T = nfirst(E(K, XOR(checksum, Z.back())), tau);
    bits result = concat(CC, T);
    return bittohex(result);
}

str ocb_decrypt(const str &key, const str &nonce, const str &c_text) {
    bytes K = Botan::hex_decode(key);
    bits N = hexinbit(nonce);
    int n = N.size();
    bits text = hexinbit(c_text);
    int size = text.size();
    if (size < tau) return "";
    bits CC = nfirst(text, size - tau);
    bits T = nlast(text, tau);
    int m = std::max(1, (int) std::ceil((double) CC.size() / n));
    std::vector<bits> C = split(CC, m);
    std::vector<bits> Z(m);
    std::vector<bits> M(m);
    bits L = E(K, bits(n));
    bits R = E(K, XOR(N, L));
    Z[0] = XOR(L, R);
    for (int i = 1; i < m; ++i) {
        Z[i] = XOR(Z[i - 1], mulxn(L, ntz(numinbit(i + 1))));
    }
    for (int i = 0; i < m - 1; ++i)
        M[i] = XOR(E_sub_one(K, XOR(C[i], Z[i])), Z[i]);
    bits x = XOR(XOR(len(n, C.back()), divx(L)), Z.back());
    bits y = E(K, x);
    M.back() = XOR(y, C.back());
    bits MM = M[0];
    if (m > 1)
        for (int i = 1; i < m; ++i)
            MM = concat(MM, M[i]);
    bits checksum = M[0];
    if (m > 1)
        for (int i = 1; i < m - 1; ++i)
            checksum = XOR(checksum, M[i]);
    checksum = XOR(XOR(checksum, concat(C.back(), bits(n - C.back().size()))), y);
    bits t = nfirst(E(K, XOR(checksum, Z.back())), tau);
    if (T == t)
        return bittohex(MM);
    else
        return "";
}