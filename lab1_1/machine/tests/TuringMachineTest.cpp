#include "gtest/gtest.h"
#include "TuringMachine/TuringMachine.h"

using namespace turing_machine;

class TuringMachineTest : public ::testing::Test {
protected:
    void SetUp() override {
        tm = std::make_unique<TuringMachine>();
    }

    std::unique_ptr<TuringMachine> tm;
};

TEST_F(TuringMachineTest, InitialState) {
    EXPECT_EQ(tm->getCurrentState(), "q0");
    EXPECT_EQ(tm->getInitialState(), "q0");
    EXPECT_EQ(tm->getHaltState(), "halt");
    EXPECT_EQ(tm->getStepCount(), 0);
}

TEST_F(TuringMachineTest, AddRules) {
    tm->addRule("q0", '1', '0', 'R', "q0");
    tm->addRule("q0", '0', '1', 'R', "q0");
    EXPECT_EQ(tm->getProgram().getRule(), 2);
}

TEST_F(TuringMachineTest, StateManagement) {
    tm->setInitialState("q0");
    tm->setHaltState("stop");
    EXPECT_EQ(tm->getCurrentState(), "q0");
    EXPECT_EQ(tm->getHaltState(), "stop");
}

TEST_F(TuringMachineTest, SingleStep) {
    tm->getTape() = Tape("101", 'B');
    tm->addRule("q0", '1', '0', 'R', "q0");
    tm->addRule("q0", '0', '1', 'R', "q0");
    tm->addRule("q0", 'B', 'B', 'S', "halt");
    
    EXPECT_TRUE(tm->step());
    EXPECT_EQ(tm->getCurrentState(), "q0");
    EXPECT_EQ(tm->getTape().read(), '0');
    EXPECT_EQ(tm->getStepCount(), 1);
}

TEST_F(TuringMachineTest, FullExecution) {
    tm->getTape() = Tape("101", 'B');
    tm->addRule("q0", '1', '0', 'R', "q0");
    tm->addRule("q0", '0', '1', 'R', "q0");
    tm->addRule("q0", 'B', 'B', 'S', "halt");
    
    tm->run(false);
    EXPECT_EQ(tm->getCurrentState(), "halt");
    EXPECT_GT(tm->getStepCount(), 0);
}

TEST_F(TuringMachineTest, RunWithCallback) {
    tm->getTape() = Tape("1", 'B');
    tm->addRule("q0", '1', '0', 'S', "halt");
    
    int callbackCount = 0;
    auto callback = [&callbackCount](const TuringMachine& tm) {
       (void)tm;
       callbackCount++;
    };
    
    tm->runWithCallback(false, callback);
    EXPECT_GT(callbackCount, 0);
}

TEST_F(TuringMachineTest, MaxStepsExceeded) {
    tm->getTape() = Tape("1", 'B');
    tm->addRule("q0", '1', '1', 'R', "q0");
    tm->addRule("q0", 'B', 'B', 'R', "q0");
    tm->setMaxSteps(10);
    
    EXPECT_THROW(tm->run(false), MaxStepsExceededException);
}

TEST_F(TuringMachineTest, CopyConstructor) {
    tm->getTape() = Tape("101", 'B');
    tm->addRule("q0", '1', '0', 'R', "q1");
    tm->setInitialState("q0");
    
    TuringMachine tm2(*tm);
    EXPECT_EQ(tm2.getInitialState(), "q0");
    EXPECT_EQ(tm2.getProgram().getRule(), 1);
}

TEST_F(TuringMachineTest, Serialization) {
    tm->getTape() = Tape("101", 'B');
    tm->addRule("q0", '1', '0', 'R', "q1");
    tm->setInitialState("q0");
    tm->setHaltState("q1");
    
    std::string data = tm->serialize();
    TuringMachine tm2;
    tm2.deserialize(data);
    
    EXPECT_EQ(tm2.getInitialState(), "q0");
    EXPECT_EQ(tm2.getHaltState(), "q1");
    EXPECT_EQ(tm2.getProgram().getRule(), 1);
}

TEST_F(TuringMachineTest, SerializationRoundTrip) {
    TuringMachine tm1;
    tm1.getTape() = Tape("101", 'B');
    tm1.addRule("q0", '1', '0', 'R', "q1");
    tm1.setInitialState("q0");
    tm1.setHaltState("q1");
    tm1.setMaxSteps(500);
    
    std::string data = tm1.serialize();
    TuringMachine tm2;
    tm2.deserialize(data);
    
    EXPECT_EQ(tm2.getInitialState(), "q0");
    EXPECT_EQ(tm2.getHaltState(), "q1");
    EXPECT_EQ(tm2.getMaxSteps(), 500);
    EXPECT_EQ(tm2.getProgram().getRule(), 1);
}

TEST_F(TuringMachineTest, FileOperations) {
    std::ofstream file("test_config.txt");
    file << "[Config]\n";
    file << "initialState: q0\n";
    file << "haltState: halt\n";
    file << "[Tape]\n";
    file << "111\n";
    file << "[Program]\n";
    file << "q0 1 0 R q1\n";
    file << "q1 0 1 L halt\n";
    file.close();
    
    TuringMachine tm;
    tm.loadFromFile("test_config.txt");
    
    EXPECT_EQ(tm.getInitialState(), "q0");
    EXPECT_EQ(tm.getHaltState(), "halt");
    EXPECT_EQ(tm.getProgram().getRule(), 2);
    
    tm.saveToFile("test_save.txt");
    
    remove("test_config.txt");
    remove("test_save.txt");
}

TEST_F(TuringMachineTest, NoRulesStops) {
    TuringMachine tm;
    tm.getTape() = Tape("1", 'B');
    
    EXPECT_FALSE(tm.step());
    EXPECT_EQ(tm.getStepCount(), 0);
}

TEST_F(TuringMachineTest, ImmediateHalt) {
    TuringMachine tm;
    tm.getTape() = Tape("1", 'B');
    tm.addRule("q0", '1', '1', 'S', "halt");
    
    tm.step();
    EXPECT_EQ(tm.getCurrentState(), "halt");
    EXPECT_EQ(tm.getStepCount(), 1);
}

TEST_F(TuringMachineTest, ComplexStateTransitions) {
    TuringMachine tm;
    tm.getTape() = Tape("101", 'B');
    
    tm.addRule("q0", '1', '0', 'R', "q1");
    tm.addRule("q1", '0', '1', 'R', "q2"); 
    tm.addRule("q2", '1', '0', 'R', "q3");
    tm.addRule("q3", 'B', 'B', 'S', "halt");
    
    while (tm.step()) {
    }
    
    EXPECT_EQ(tm.getCurrentState(), "halt");
    EXPECT_EQ(tm.getStepCount(), 4);
}

TEST_F(TuringMachineTest, AssignmentOperator) {
    TuringMachine tm1;
    tm1.getTape() = Tape("101", 'B');
    tm1.addRule("q0", '1', '0', 'R', "q1");
    
    TuringMachine tm2;
    tm2 = tm1;
    
    EXPECT_EQ(tm2.getProgram().getRule(), 1);
    EXPECT_EQ(tm2.getTape().toString(), tm1.getTape().toString());
}

TEST_F(TuringMachineTest, ResetMachine) {
    TuringMachine tm;
    tm.getTape() = Tape("101", 'B');
    tm.addRule("q0", '1', '0', 'R', "q1");
    tm.setInitialState("q0");
    
    tm.step();
    EXPECT_GT(tm.getStepCount(), 0);
    
    tm.reset();
    EXPECT_EQ(tm.getCurrentState(), "q0");
    EXPECT_EQ(tm.getStepCount(), 0);
}

TEST(TuringMachineUncovered, LoadProgramInvalidFormat) {
    TuringMachine tm;
    std::stringstream stream;
    
    stream << "q0 1 0 R\n";
    stream << "q0 1 0 q1\n";
    stream << "q0 1 R q1\n";
    
    EXPECT_NO_THROW(tm.loadProgram(stream));

TEST(TuringMachineUncovered, LoadEmptyTape) {
    TuringMachine tm;
    std::stringstream stream;
    stream << "";
    
    tm.loadTape(stream);
    EXPECT_EQ(tm.getTape().read(), 'B');
    EXPECT_EQ(tm.getTape().getPosition(), 0);
}

TEST(TuringMachineUncovered, PrintMethodsOutput) {
    TuringMachine tm;
    tm.getTape() = Tape("101", 'B');
    tm.addRule("q0", '1', '0', 'R', "q1");
    tm.addRule("q1", '0', '1', 'L', "halt");
    
    std::stringstream output;
    
    tm.printState(output);
    std::string stateOutput = output.str();
    EXPECT_TRUE(stateOutput.find("State=") != std::string::npos);
    EXPECT_TRUE(stateOutput.find("Tape=") != std::string::npos);
    
    output.str("");
    
    tm.printRules(output);
    std::string rulesOutput = output.str();
    EXPECT_TRUE(rulesOutput.find("Program rules:") != std::string::npos);
    EXPECT_TRUE(rulesOutput.find("q0") != std::string::npos);
}
