#include "pch.h"
#include "../PRESENT/present.h"
#include "../PRESENT/files.h"

using namespace std;

TEST(PRESENT80, OfficialVector) {
    uint64_t plain = 0x0123456789ABCDEFULL;

    bitset<80> key;
    string key_hex = "0123456789abcdef0123";

    for (int i = 0; i < 80; i++) {
        key[i] = (stoi(key_hex.substr(19 - i / 4, 1), nullptr, 16) >> (i % 4)) & 1;
    }

    auto keys = generateRoundKeys80(key);

    uint64_t rk[32];
    for (int i = 0; i < 32; i++) {
        rk[i] = keys[i]; 
    }

    uint64_t cipher = encrypt(plain, rk);

    EXPECT_EQ(cipher, 0xF8DD50531D973BDEULL);
}

TEST(PRESENT128, OfficialVector) {
    uint64_t plain = 0x0123456789ABCDEFULL;

    bitset<128> key;
    string key_hex = "00112233445566778899aabbccddeeff";

    for (int i = 0; i < 128; i++) {
        key[i] = (stoi(key_hex.substr(31 - i / 4, 1), nullptr, 16) >> (i % 4)) & 1;
    }

    auto keys = generateRoundKeys128(key);

    uint64_t rk[32];
    for (int i = 0; i < 32; i++) { 
        rk[i] = keys[i]; 
    }

    uint64_t cipher = encrypt(plain, rk);

    EXPECT_EQ(cipher, 0x88728500054418DEULL);
}


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

TEST(PRESENT80, DifferentKeys) {
    uint64_t plain = 0x123456789ABCDEF0ULL;

    bitset<80> key1;
    key1.reset();

    bitset<80> key2;
    key2.set();

    auto k1 = generateRoundKeys80(key1);
    auto k2 = generateRoundKeys80(key2);

    uint64_t rk1[32], rk2[32];
    for (int i = 0; i < 32; i++) {
        rk1[i] = k1[i];
        rk2[i] = k2[i];
    }

    uint64_t c1 = encrypt(plain, rk1);
    uint64_t c2 = encrypt(plain, rk2);

    EXPECT_NE(c1, c2);
}

TEST(PRESENT80, ECBMode) {
    vector<uint8_t> data = {
        1,2,3,4,5,6,7,8,
        9,10,11,12,13,14,15,16
    };

    bitset<80> key;
    key.reset();

    auto keys = generateRoundKeys80(key);

    uint64_t rk[32];
    for (int i = 0; i < 32; i++) {
        rk[i] = keys[i];
    }

    auto enc = encryptData(data, rk);
    auto dec = decryptData(enc, rk);

    EXPECT_EQ(dec, data);
}

TEST(PRESENT128, MultipleBlocks) {
    bitset<128> key;
    key.reset();

    auto keys = generateRoundKeys128(key);

    uint64_t rk[32];
    for (int i = 0; i < 32; i++) rk[i] = keys[i];

    uint64_t blocks[3] = {
        0x1111111111111111ULL,
        0x2222222222222222ULL,
        0x3333333333333333ULL
    };

    for (int i = 0; i < 3; i++) {
        uint64_t c = encrypt(blocks[i], rk);
        uint64_t d = decrypt(c, rk);

        EXPECT_EQ(d, blocks[i]);
    }
}
