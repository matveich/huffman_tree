//
// Created by matveich on 16.06.18.
//


#include <cmath>
#include "gtest/gtest.h"
#include "tree.h"


void check_eq(const std::string& data) {
    tree t;
    t.update_dict(data.data(), data.size());
    t.build();
    bit_sequence offset(1), offset1(1);
    bit_sequence* compressed = t.compress(data.data(), data.size(), offset);
    if (offset.size() > 0)
        compressed->append(offset);
    EXPECT_TRUE(compressed->size() <= data.size());

    tree t1;
    std::vector<char> dict = t.get_dict();
    t1.build_by_freq_dict(dict.data() + 1, dict.size() - 1);
    bit_sequence* decompressed = t1.decompress((char*)compressed->get_data(), compressed->size(), offset1, true);
    EXPECT_EQ(data, std::string((char*)(decompressed->get_data()), decompressed->size()));
    delete compressed;
    delete decompressed;
}


TEST(correctness, basic) {
    check_eq("abc");
}


TEST(correctness, empty) {
    check_eq("");
}


TEST(correctness, one) {
    check_eq("1");
}

TEST(correctness, back_slash_n) {
    check_eq("\n");
}

TEST(correctness, back_slash_n_plus_char) {
    check_eq("\na");
}

TEST(correctness, chars_back_slash_n_plus_chars) {
    check_eq("ajtjglt\nnln");
}

TEST(correctness, chars_tabs) {
    check_eq("a\tjtj\tglt\tnln\t");
}

TEST(correctness, spaces) {
    check_eq("       ");
}

TEST(correctness, one_hundred_a) {
    std::string input(100, 'a');
    check_eq(input);
}

TEST(correctness, small_fuzzing_a_z) {
    srand(0);
    for (int i = 0; i < 100; ++i) {
        std::string input;
        for (int j = 0; j < 100; ++j) {
            input += ('a' + static_cast<unsigned char>(rand() % 26));
        }
        check_eq(input);
    }
}

TEST(correctness, small_fuzzing_0_128) {
    srand(0);
    for (int i = 0; i < 100; ++i) {
        std::string input;
        for (int j = 0; j < 100; ++j) {
            input += static_cast<char>(rand() % 128);
        }
        check_eq(input);
    }
}

TEST(correctness, critical_size) {
    size_t CZ = 8 * 1024 * 1024;
    check_eq(std::string(CZ, 'a'));
}

TEST(correctness, critical_size_random) {
    size_t CZ = 8 * 1024 * 1024;
    std::string s;
    s.resize(CZ);
    for (auto &c : s) {
        c = static_cast<char>(rand() % 128);
    }
    check_eq(s);
}