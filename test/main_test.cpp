#include "gtest/gtest.h"
#include "automaton.h"

TEST(Case1, LibTest1){
    Automaton a("ab+c.aba.*.bac.+.+*");
    // (((a+b)c+a(ba)*(b+ac)))*
    EXPECT_EQ(true, a.CheckIfContained("ab"));
    EXPECT_EQ(true, a.CheckIfContained("acbcabababaacac"));
    EXPECT_EQ(true, a.CheckIfContained("abab"));
    EXPECT_EQ(false, a.CheckIfContained("a"));
    EXPECT_EQ(false, a.CheckIfContained("acbcabababaacaa"));
    EXPECT_EQ(false, a.CheckIfContained("$"));
}

TEST(Case1, LibTest2){
    Automaton a("ab+c*.ab..ca.+aba+*.c.ab+.+*");
    // ((((a+b)(c)*ab+ca)+a((b+a))*c(a+b)))*
    EXPECT_EQ(true, a.CheckIfContained("aab"));
    EXPECT_EQ(false, a.CheckIfContained("cababac"));
    EXPECT_EQ(false, a.CheckIfContained("c"));
    EXPECT_EQ(false, a.CheckIfContained("caaaab"));
    EXPECT_EQ(true, a.CheckIfContained("cacaacccababbabca"));
    EXPECT_EQ(true, a.CheckIfContained("cacaacccab"));
    EXPECT_EQ(true, a.CheckIfContained("aababbbbacb"));
}

TEST(Case1, LibTest3){
    Automaton a("ab+*c*.ab+*.c*.abc++*.");
    // ((a+b))*(c)*((a+b))*(c)*((a+(b+c)))*
    EXPECT_EQ(true, a.CheckIfContained("aab"));
    EXPECT_EQ(true, a.CheckIfContained("cababac"));
    EXPECT_EQ(true, a.CheckIfContained("c"));
    EXPECT_EQ(true, a.CheckIfContained("caaaab"));
    EXPECT_EQ(true, a.CheckIfContained("cacaacccababbabca"));
    EXPECT_EQ(true, a.CheckIfContained("cacaacccab"));
    EXPECT_EQ(true, a.CheckIfContained("aababbbbacb"));
    EXPECT_EQ(true, a.CheckIfContained("1"));
}


TEST(Case1, LibTest4){
    Automaton a("abc..*");
    // (abc)*
    EXPECT_EQ(false, a.CheckIfContained("cba"));
    EXPECT_EQ(false, a.CheckIfContained("babcab"));
    EXPECT_EQ(false, a.CheckIfContained("aaaa"));
    EXPECT_EQ(false, a.CheckIfContained("aaab"));
    EXPECT_EQ(false, a.CheckIfContained("cababac"));
    EXPECT_EQ(false, a.CheckIfContained("c"));
    EXPECT_EQ(false, a.CheckIfContained("bbb"));
    EXPECT_EQ(true, a.CheckIfContained("abcabc"));
    EXPECT_EQ(true, a.CheckIfContained("abc"));
    EXPECT_EQ(false, a.CheckIfContained("cab"));
    EXPECT_EQ(false, a.CheckIfContained("b"));
    EXPECT_EQ(false, a.CheckIfContained("a"));
    EXPECT_EQ(false, a.CheckIfContained("1"));
}

TEST(Case1, LibTest5){
    Automaton a("abc..");
    // abc
    EXPECT_EQ(false, a.CheckIfContained("cba"));
    EXPECT_EQ(false, a.CheckIfContained("babcab"));
    EXPECT_EQ(false, a.CheckIfContained("aaaa"));
    EXPECT_EQ(false, a.CheckIfContained("cababac"));
    EXPECT_EQ(false, a.CheckIfContained("c"));
    EXPECT_EQ(false, a.CheckIfContained("bbb"));
    EXPECT_EQ(false, a.CheckIfContained("abcabc"));
    EXPECT_EQ(true, a.CheckIfContained("abc"));
    EXPECT_EQ(false, a.CheckIfContained("cab"));
    EXPECT_EQ(false, a.CheckIfContained("b"));
    EXPECT_EQ(false, a.CheckIfContained("a"));
    EXPECT_EQ(false, a.CheckIfContained("1"));
}

int main(int argc, char**argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}