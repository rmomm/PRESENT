#include "pch.h"
#include "../PRESENT/present.h"
#include "../PRESENT/files.h"

using namespace std;

TEST(PRESENT80, EncryptZero80) {
    uint64_t plaintext = 0x0000000000000000ULL;
    bitset<80> key;
    key.reset();

    auto keys = generateRoundKeys80(key);
    uint64_t rk[32];
    for (int i = 0; i < 32; i++) { 
        rk[i] = keys[i]; 
    }

    uint64_t cipher = encrypt(plaintext, rk);

    EXPECT_EQ(cipher, 0x5579C1387B228445ULL);
}

TEST(PRESENT128, EncryptZero128) {
    uint64_t plaintext = 0x0000000000000000ULL;
    bitset<128> key;
    key.reset();

    auto keys = generateRoundKeys128(key);
    uint64_t rk[32];
    for (int i = 0; i < 32; i++) { 
        rk[i] = keys[i];
    }

    uint64_t cipher = encrypt(plaintext, rk);

    EXPECT_EQ(cipher, 0x96DB702A2E6900AFULL);
}

TEST(PRESENT80, DecryptBack) {
    uint64_t plaintext = 0x0000000000000000ULL;
    bitset<80> key;
    key.reset();

    auto keys = generateRoundKeys80(key);
    uint64_t cipher = encrypt(plaintext, keys.data());
    uint64_t decrypted = decrypt(cipher, keys.data());

    EXPECT_EQ(decrypted, plaintext);
}

TEST(PRESENT80, EncryptDecrypt) {
    uint64_t plain = 0x123456789ABCDEF0ULL;

    bitset<80> key;
    key.reset();

    auto keys = generateRoundKeys80(key);

    uint64_t rk[32];
    for (int i = 0; i < 32; i++) { 
        rk[i] = keys[i]; 
    }

    uint64_t cipher = encrypt(plain, rk);
    uint64_t decrypted = decrypt(cipher, rk);

    EXPECT_EQ(decrypted, plain);
}

TEST(PRESENT128, EncryptDecrypt) {
    uint64_t plain = 0xFEDCBA9876543210ULL;

    bitset<128> key;
    key.reset();

    auto keys = generateRoundKeys128(key);

    uint64_t rk[32];
    for (int i = 0; i < 32; i++) { 
        rk[i] = keys[i]; 
    }

    uint64_t cipher = encrypt(plain, rk);
    uint64_t decrypted = decrypt(cipher, rk);

    EXPECT_EQ(decrypted, plain);
}


TEST(PRESENT80, DifferentInputs) {
    bitset<80> key;
    key.reset();

    auto keys = generateRoundKeys80(key);

    uint64_t rk[32];
    for (int i = 0; i < 32; i++) {
        rk[i] = keys[i]; 
    }

    uint64_t p1 = 0x0000000000000000ULL;
    uint64_t p2 = 0xFFFFFFFFFFFFFFFFULL;

    uint64_t c1 = encrypt(p1, rk);
    uint64_t c2 = encrypt(p2, rk);

    EXPECT_NE(c1, c2);
}

