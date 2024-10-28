#include <benchmark/benchmark.h>
#include <stack.h>

static void PushBenchmark(benchmark::State& state, Stack* stack) {
    for (auto _ : state) {
        push(stack, 1111111);
    }
}

class PushFixture : public benchmark::Fixture {
  protected:
    Stack* stack;

  public:
    void SetUp(const benchmark::State& state) override {
        stack = new Stack();
        initStack(stack);
    }

    void TearDown(const benchmark::State& state) override {
        destroyStack(stack);
    }
};

BENCHMARK_DEFINE_F(PushFixture, PushBenchmark)(benchmark::State& state) {
    PushBenchmark(state, stack);
}

BENCHMARK_REGISTER_F(PushFixture, PushBenchmark)
    ->RangeMultiplier(2)
    ->Range(1, 512);

static void PopBenchmark(benchmark::State& state, Stack* stack) {
    for (auto _ : state) {
        pop(stack);
    }
}

class PopFixture : public benchmark::Fixture {
  protected:
    Stack* stack;

  public:
    void SetUp(const benchmark::State& state) override {
        stack = new Stack();
        initStack(stack);
        long count = state.range(0);
        for (long i = 0; i <= count; i++) {
            push(stack, 1111111);
        }
    }

    void TearDown(const benchmark::State& state) override {
        destroyStack(stack);
    }
};

BENCHMARK_DEFINE_F(PopFixture, PopBenchmark)(benchmark::State& state) {
    PopBenchmark(state, stack);
}

BENCHMARK_REGISTER_F(PopFixture, PopBenchmark)
    ->RangeMultiplier(2)
    ->Range(1, 1024);

BENCHMARK_MAIN();
