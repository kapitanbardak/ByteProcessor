//
// Created by  Алексей Русских on 14.08.2024.
//

#ifndef BYTEPROCESSOR_BYTEPROCESSOR_H
#define BYTEPROCESSOR_BYTEPROCESSOR_H

#include <thread>
#include <atomic>
#include <iostream>
#include <sstream>

#include "ISink.h"
#include "ISource.h"
#include "IObserver.h"

class ByteProcessor : public IObserver {
public:
    ByteProcessor(ISource& source, ISink& sink);
    void start();
    void stop();
    void Update() override;
    ~ByteProcessor();

private:
    void run();
    ISource& source;
    ISink& sink;
    std::atomic<bool> running;
    std::thread processingThread;
    bool observerState;
    std::condition_variable cv;
    std::mutex mutex;
};

#endif //BYTEPROCESSOR_BYTEPROCESSOR_H
