#include "pch.h"
#include "../PRESENT/present.h"
#include "../PRESENT/files.h"


TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(PRESENT80, EncryptZero) {
    uint64_t plaintext = 0x0000000000000000ULL;
    std::bitset<80> key;
    key.reset();

    auto keys = generateRoundKeys80(key);
    uint64_t cipher = encrypt(plaintext, keys.data());

    EXPECT_EQ(cipher, 0x5579C1387B228445ULL);
}

TEST(PRESENT80, DecryptBack) {
    uint64_t plaintext = 0x0000000000000000ULL;
    std::bitset<80> key;
    key.reset();

    auto keys = generateRoundKeys80(key);
    uint64_t cipher = encrypt(plaintext, keys.data());
    uint64_t decrypted = decrypt(cipher, keys.data());

    EXPECT_EQ(decrypted, plaintext);
}
