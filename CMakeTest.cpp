#include <iostream>
#include "HashTable.h"
#include <gtest/gtest.h>

class HashTableTest : public testing::Test{
protected:
    void SetUp() override{
        t1.insert("Alekey Sidorov", {.age = 20, .weight = 70});
        t1.insert("Nikita Ivanov", {.age = 17, .weight = 75});
        t1.insert("Rita Voronova", {.age = 18, .weight = 55});

        t2.insert("Ivan Petrov", {.age = 21, .weight = 82});
        t2.insert("Sergey Titov", {.age = 20, .weight = 66});
        t2.insert("Roman Popov", {.age = 18, .weight = 58});
        t2.insert("Maria Gromova", {.age = 19, .weight = 47});
    }
    HashTable t0;
    HashTable t1;
    HashTable t2;

};
TEST_F(HashTableTest, SwapWorks){
    t1.swap(t2);
    EXPECT_EQ(t1.size(), 4);
    EXPECT_EQ(t2.size(), 3);
    EXPECT_EQ(t2["Rita Voronova"].weight, 55);
}
TEST_F(HashTableTest, EraseWorks){
    bool r = t2.erase("Ivan Petrov");
    EXPECT_EQ(r, true);
}
TEST_F(HashTableTest, EmptyWorks){
    bool r = t1.empty();
    EXPECT_EQ(r, false);
    r = t0.empty();
    EXPECT_EQ(r, true);
}
TEST_F(HashTableTest, ContainsWorks){
    bool r = t1.contains("Nikita Ivanov");
    EXPECT_EQ(r, true);
    r = t1.contains("Tom Holland");
    EXPECT_EQ(r, false);
}
TEST_F(HashTableTest, AtWorks){
    Value& s = t1.at("Alekey Sidorov");
    EXPECT_EQ(s.weight, 70);
    ASSERT_ANY_THROW(t1.at("check"));
}
TEST_F(HashTableTest, OperatorsWork){
    bool r1 = t1 == t2;
    EXPECT_EQ(r1, false);
    bool r2 = t1 != t2;
    EXPECT_EQ(r2, true);
    unsigned int r3 = t2["Roman Popov"].weight;
    EXPECT_EQ(r3, 58);
    t1 = t2;
    r1 = t1 == t2;
    EXPECT_EQ(r1, true);
}
TEST_F(HashTableTest, CopyConstructWorks){
    HashTable t3 = t1;
    EXPECT_EQ(t3.size(), 3);
    bool r0 = t3.contains("Rita Voronova");
    EXPECT_EQ(r0, true);
    bool r2 = t3.contains("Maria Gromova");
    EXPECT_EQ(r2, false);

}
TEST_F(HashTableTest, MoveConstructWorks){
    HashTable t4 = std::move(t2);

    bool r0 = t4.contains("Sergey Titov");
    bool r1 = t4.contains("Roman Popov");
    bool r2 = t4.contains("Maria Gromova");
    bool r3 = t2.empty();
    EXPECT_EQ(r0, true);
    EXPECT_EQ(r1, true);
    EXPECT_EQ(r2, true);
    EXPECT_EQ(r3, true);
}