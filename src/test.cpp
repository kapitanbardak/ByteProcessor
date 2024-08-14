#include <gtest/gtest.h>

#include <queue>
#include <mutex>
#include <condition_variable>

#include "ByteProcessor.h"

class TestSource : public ISource {
public:
    void addByte(uint8_t byte) {
        std::lock_guard<std::mutex> lock(mutex);
        dataQueue.push(byte);
        Notify();
    }

    uint8_t read() override {
        std::unique_lock<std::mutex> lock(mutex);
        uint8_t byte = dataQueue.front();
        dataQueue.pop();
        Notify();
        return byte;
    }

    bool GetState() override {
        return !dataQueue.empty();
    }

private:

    void Notify() override {
        for (auto& o : observers) {
            o->Update();
        }
    }

    void Attach(IObserver* observer) override {
        observers.push_back(observer);
    }

    void Detach(IObserver* observer) override {
        for (auto i = observers.begin(); i != observers.end(); ++i) {
            if (*i == observer) {
                observers.erase(i);
            }
        }
    }

    std::queue<uint8_t> dataQueue;
    std::mutex mutex;
    std::vector<IObserver*> observers;
};

class TestSink : public ISink {
public:
    std::vector<std::string> answers;

    void write(const std::string &data) override {
        std::lock_guard<std::mutex> lock(mutex);
        answers.push_back(data);
    }

private:
    std::mutex mutex;
};

class TestByteProcessor : public ::testing::Test {
 protected:
  void SetUp() {
    source = new TestSource();
    sink = new TestSink();
    byteProcessor = new ByteProcessor(*source, *sink);
  }

  void TearDown() {
      //delete byteProcessor;
      delete source;
      delete sink;
  }
    TestSource* source;
    TestSink* sink;
    ByteProcessor* byteProcessor;
};

TEST_F(TestByteProcessor, test1) {
    byteProcessor->start();

    source->addByte(0b00000011); // Unsigned integer 3
    source->addByte(0b01111111); // Signed integer -1
    source->addByte(0b10000001); // Character 'b'

    std::this_thread::sleep_for(std::chrono::seconds(1));

    byteProcessor->stop();

    ASSERT_EQ(sink->answers[2], "b");
    ASSERT_EQ(sink->answers[1], "-1");
    ASSERT_EQ(sink->answers[0], "3");
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
