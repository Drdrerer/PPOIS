#include "gtest/gtest.h"
#include "Transition/Transition.h"

using namespace turing_machine;

class TransitionTest : public ::testing::Test {
protected:
    void SetUp() override {
        transition = std::make_unique<Transition>('1', '0', 'R', "q1");
    }

    std::unique_ptr<Transition> transition;
};

TEST_F(TransitionTest, Constructor) {
    EXPECT_EQ(transition->readSymbol, '1');
    EXPECT_EQ(transition->writeSymbol, '0');
    EXPECT_EQ(transition->moveDirection, 'R');
    EXPECT_EQ(transition->nextState, "q1");
}

TEST_F(TransitionTest, Equality) {
    Transition t2('1', '0', 'R', "q1");
    EXPECT_TRUE(*transition == t2);
    
    Transition t3('0', '1', 'L', "q2");
    EXPECT_FALSE(*transition == t3);
}

TEST_F(TransitionTest, ToString) {
    std::string str = transition->toString();
    EXPECT_EQ(str, "1 0 R q1");
}

TEST_F(TransitionTest, DefaultConstructor) {
    Transition t2;
    EXPECT_EQ(t2.readSymbol, ' ');
    EXPECT_EQ(t2.writeSymbol, ' ');
    EXPECT_EQ(t2.moveDirection, 'S');
    EXPECT_EQ(t2.nextState, "");
}
