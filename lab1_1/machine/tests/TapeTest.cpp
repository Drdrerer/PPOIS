#include "gtest/gtest.h"
#include "Tape/Tape.h"

using namespace turing_machine;

class TapeTest : public ::testing::Test {
protected:
    void SetUp() override {
        tape = std::make_unique<Tape>("101", 'B');
    }

    std::unique_ptr<Tape> tape;
};

TEST_F(TapeTest, Initialization) {
    EXPECT_EQ(tape->read(), '1');
    EXPECT_EQ(tape->getPosition(), 0);
}

TEST_F(TapeTest, ReadWrite) {
    tape->write('0');
    EXPECT_EQ(tape->read(), '0');
}

TEST_F(TapeTest, Movement) {
    tape->move('R');
    EXPECT_EQ(tape->getPosition(), 1);
    EXPECT_EQ(tape->read(), '0');
    
    tape->move('L');
    EXPECT_EQ(tape->getPosition(), 0);
}

TEST_F(TapeTest, BlankSymbol) {
    tape->move('R');
    tape->move('R');
    tape->move('R');
    EXPECT_EQ(tape->read(), 'B');
}

TEST_F(TapeTest, Serialization) {
    std::string data = tape->serialize();
    Tape newTape;
    newTape.deserialize(data);
    EXPECT_EQ(newTape.read(), tape->read());
    EXPECT_EQ(newTape.getPosition(), tape->getPosition());
}

TEST_F(TapeTest, Bounds) {
    auto bounds = tape->getBounds();
    EXPECT_EQ(bounds.first, 0);
    EXPECT_EQ(bounds.second, 2);
}

TEST_F(TapeTest, Clear) {
    tape->clear();
    EXPECT_EQ(tape->getPosition(), 0);
    EXPECT_EQ(tape->read(), 'B');
}
