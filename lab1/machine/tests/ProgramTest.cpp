#include "gtest/gtest.h"
#include "Program/Program.h"

using namespace turing_machine;

class ProgramTest : public ::testing::Test {
protected:
    void SetUp() override {
        program = std::make_unique<Program>();
        program->addRule("q0", '1', '0', 'R', "q0");
        program->addRule("q0", '0', '1', 'R', "q0");
        program->addRule("q0", 'B', 'B', 'S', "halt");
    }

    std::unique_ptr<Program> program;
};

TEST_F(ProgramTest, AddAndCountRules) {
    EXPECT_EQ(program->getRule(), 3);
    EXPECT_TRUE(program->hasRule("q0", '1'));
    EXPECT_TRUE(program->hasRule("q0", '0'));
    EXPECT_TRUE(program->hasRule("q0", 'B'));
}

TEST_F(ProgramTest, GetTransition) {
    Transition t;
    EXPECT_TRUE(program->getTransition("q0", '1', t));
    EXPECT_EQ(t.readSymbol, '1');
    EXPECT_EQ(t.writeSymbol, '0');
    EXPECT_EQ(t.moveDirection, 'R');
    EXPECT_EQ(t.nextState, "q0");
}

TEST_F(ProgramTest, RemoveRule) {
    program->removeRule("q0", '1');
    EXPECT_EQ(program->getRule(), 2);
    EXPECT_FALSE(program->hasRule("q0", '1'));
}

TEST_F(ProgramTest, NonExistentRule) {
    Transition t;
    EXPECT_FALSE(program->getTransition("q1", '1', t));
    EXPECT_FALSE(program->hasRule("q1", '1'));
}

TEST_F(ProgramTest, GetAllStates) {
    auto states = program->getStates();
    EXPECT_EQ(states.size(), 1);
    EXPECT_EQ(states[0], "q0");
}

TEST_F(ProgramTest, Serialization) {
    std::string data = program->serialize();
    Program newProgram;
    newProgram.deserialize(data);
    EXPECT_EQ(newProgram.getRule(), program->getRule());
}

TEST_F(ProgramTest, Clear) {
    program->clear();
    EXPECT_EQ(program->getRule(), 0);
    EXPECT_FALSE(program->hasRules());
}
