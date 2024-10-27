#include <csignal>
#include <gtest/gtest.h>
#include <stack.h>

class StackTest : public ::testing::Test {
  protected:
    Stack* stack = new Stack();

  private:
    void SetUp() override {
        initStack(stack);
    }

    void TearDown() override {
        destroyStack(stack);
    }
};

TEST_F(StackTest, isEmptyFunctionTest) {
    EXPECT_TRUE(isEmpty(stack));
}

TEST_F(StackTest, PushFunctionTest) {
    push(stack, 5);
    EXPECT_EQ(getTop(stack)->data, 5);
    push(stack, 7);
    EXPECT_EQ(getTop(stack)->data, 7);
    EXPECT_FALSE(isEmpty(stack));
};

// Обработчик для SIGSEGV
void SignalHandler(int signal) {
    throw std::runtime_error("Segmentation fault captured");
}

TEST_F(StackTest, PopFunctionTest) {
    push(stack, 7);
    push(stack, 5);
    pop(stack);
    EXPECT_EQ(getTop(stack)->data, 7);
    pop(stack);
    EXPECT_TRUE(isEmpty(stack));

    std::signal(SIGSEGV, SignalHandler);
    EXPECT_NO_THROW(pop(stack));

    // Восстанавливаем стандартное поведение для сигнала после теста
    std::signal(SIGSEGV, SIG_DFL);
};

TEST_F(StackTest, SearchByValueFunctionTest) {
    push(stack, 7);
    push(stack, 5);
    push(stack, -1);
    push(stack, 4);
    push(stack, 8);

    EXPECT_EQ(getTop(stack)->data, 8);

    Node* node = searchByValue(stack, -1);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->data, -1);

    Node* null_node = searchByValue(stack, 3);
    ASSERT_EQ(null_node, nullptr);

    Node* top_node = searchByValue(stack, 8);
    ASSERT_NE(top_node, nullptr);
    EXPECT_EQ(top_node->data, 8);

    Node* bottom_node = searchByValue(stack, 7);
    ASSERT_NE(bottom_node, nullptr);
    EXPECT_EQ(bottom_node->data, 7);
};

TEST_F(StackTest, SearchByIndexFunctionTest) {
    push(stack, 7);
    push(stack, 5);
    push(stack, -1);
    push(stack, 4);
    push(stack, 8);

    EXPECT_EQ(getTop(stack)->data, 8);

    Node* node = searchByIndex(stack, 3);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->data, 5);

    Node* null_node = searchByIndex(stack, 9);
    ASSERT_EQ(null_node, nullptr);

    Node* top_node = searchByIndex(stack, 0);
    ASSERT_NE(top_node, nullptr);
    EXPECT_EQ(top_node->data, 8);

    Node* bottom_node = searchByIndex(stack, 4);
    ASSERT_NE(bottom_node, nullptr);
    EXPECT_EQ(bottom_node->data, 7);
};

TEST_F(StackTest, TraverseStackFunctionTest) {
    push(stack, 4);
    push(stack, 7);
    push(stack, 1);
    testing::internal::CaptureStdout();
    traverseStack(stack);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Stack elements: 1 7 4 \n");
}
