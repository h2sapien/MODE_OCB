#include "Funks.h"

bits mulx(const bits &bi) {
    bits result = shl(bi);
    if (bi.front()) {
        bits xor_by = bits(120);
        xor_by.push_back(true);
        xor_by.push_back(false);
        xor_by.push_back(false);
        xor_by.push_back(false);
        xor_by.push_back(false);
        xor_by.push_back(true);
        xor_by.push_back(true);
        xor_by.push_back(true);
        result = XOR(result, xor_by);
    }
    return result;
}

bits divx(const bits &bi) {
    bits result = shr(bi);
    if (bi.front()) {
        bits xor_by = bits(120);
        xor_by.insert(xor_by.begin(), true);
        xor_by.push_back(true);
        xor_by.push_back(false);
        xor_by.push_back(false);
        xor_by.push_back(false);
        xor_by.push_back(false);
        xor_by.push_back(true);
        xor_by.push_back(true);
        result = XOR(result, xor_by);
    }
    return result;
}

bits len(const int n, const bits &bi) {
    bits binary = numinbit(bi.size());
    bits bb(n - binary.size());
    bb.insert(bb.end(), binary.begin(), binary.end());
    return bb;
}

bits nfirst(const bits &bi, int n) {
    if (n > bi.size()) {
        std::cerr << "Слишком короткое сообщение\n";
        exit(1);
    }
    bits result(bi.begin(), bi.begin() + n);
    return result;
}

bits nlast(const bits &bi, int n) {
    if (n > bi.size()) {
        std::cerr << "Слишком короткое сообщение\n";
        exit(1);
    }
    bits result(bi.end() - n, bi.end());
    return result;
}

bytes bittest(const bits &bi) {
    bytes by;
    for (int i = 0; i < bi.size(); i += 8) {
        uint8_t byte = 0;
        for (int j = 0; j < 8; ++j)
            byte += (1 << j) * bi[i + j];
        by.push_back(byte);
    }
    return by;
}

bits bytetest(const bytes &by) {
    bits bitstring;
    for (uint8_t byte : by) {
        for (int j = 0; j < 8; ++j) {
            bitstring.push_back(std::bitset<8>(byte)[j]);
        }
    }
    return bitstring;
}

bits numinbit(const unsigned long num) {
    bits bi;
    for (unsigned long i = num; i != 0; i /= 2) {
        if (i % 2)
            bi.insert(bi.begin(), true);
        else
            bi.insert(bi.begin(), false);
    }
    return bi;
}

std::vector<bits> split(bits bi, int m) {
    int size = bi.size();
    int n = std::ceil(size / m);
    std::vector<bits> result(m);
    for (int i = 0; i < m; ++i) {
        bits temp(n);
        for (int j = i; j < n; ++j)
            temp[j] = bi[i * n + j];
        result[i] = temp;
    }
    return result;
}

bits XOR(const bits &bi1, const bits &bi2) {
    int l = std::min(bi1.size(), bi2.size());
    bits result(l);
    for (int i = 0; i < l; ++i) {
        result[i] = bi1[i] ^ bi2[i];
    }
    return result;
}

bits shl(const bits &bi) {
    bits result = bi;
    std::rotate(result.begin(), result.begin() + 1, result.end());
    return result;
}

bits shr(const bits &bi) {
    bits result = bi;
    std::rotate(result.rbegin(), result.rbegin() + 1, result.rend());
    return result;
}

bits mulxn(const bits &bi, int n) {
    if (n == 0)
        return bi;
    else if (n == 1)
        return mulx(bi);
    else
        return mulxn(mulx(bi), n - 1);
}

bits concat(const bits &bi1, const bits &bi2) {
    bits result = bi1;
    if (!bi2.empty())
        result.insert(result.end(), bi2.begin(), bi2.end());
    return result;
}

int ntz(const bits &bi) {
    int count_zeros = 0;
    for (unsigned long i = bi.size() - 1; i >= 0; --i) {
        if (bi[i] == 0)
            count_zeros++;
        else
            break;
    }
    return count_zeros;
}

bits hexinbit(const str &hex) {
    return bytetest(Botan::hex_decode(hex));
}

str bittohex(const bits &bi) {
    return Botan::hex_encode(bittest(bi));
}
