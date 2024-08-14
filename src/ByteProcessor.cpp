/**
 * @class ByteProcessor
 * @brief Class responsible for processing bytes from a source and writing results to a sink.
 *
 * The ByteProcessor class is an implementation of an observer pattern, which listens to a source,
 * processes the bytes received, and writes the processed data to a sink. The processing is done
 * in a separate thread.
 */

#include "ByteProcessor.h"
#include <thread>
#include <atomic>

/**
 * @brief Constructs a ByteProcessor object.
 *
 * Initializes the ByteProcessor with a reference to a source and a sink, and attaches itself as an observer to the source.
 *
 * @param source Reference to the data source.
 * @param sink Reference to the data sink.
 */
ByteProcessor::ByteProcessor(ISource& source, ISink& sink)
        : source(source), sink(sink), running(false) {
    source.Attach(this);
}

/**
 * @brief Starts the processing thread.
 *
 * If the processing thread is not already running, this function starts it by setting the running flag
 * to true and launching the thread which executes the run method.
 */
void ByteProcessor::start() {
    if (!running) {
        running = true;
        processingThread = std::thread(&ByteProcessor::run, this);
    }
}

/**
 * @brief Stops the processing thread.
 *
 * If the processing thread is running, this function stops it by setting the running flag to false
 * and waiting for the thread to join.
 */
void ByteProcessor::stop() {
    if (running) {
        running = false;
        if (processingThread.joinable()) {
            processingThread.join();
        }
    }
}

/**
 * @brief Destructor for ByteProcessor.
 *
 * Ensures that the processing thread is stopped before the object is destroyed.
 */
ByteProcessor::~ByteProcessor() {
    stop();
}

/**
 * @brief Main processing loop.
 *
 * This method runs in a separate thread and continuously waits for a notification to process the next byte
 * from the source. Depending on the byte's type, it processes the byte and writes the result to the sink.
 */
void ByteProcessor::run() {
    while (running) {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, [this] { return true; });
        if (observerState) {
            uint8_t byte = source.read();
            uint8_t dataType = (byte >> 6) & 0b11;
            uint8_t dataValue = byte & 0b00111111;
            std::string result;

            switch (dataType) {
                case 0b00:
                    result = std::to_string(dataValue);
                    break;
                case 0b01:
                    result = std::to_string(static_cast<int8_t>(dataValue << 2) >> 2);
                    break;
                case 0b10:
                    result = std::string(1, 'a' + dataValue);
                    break;
                default:
                    result = "?"; // Unknown type
                    break;
            }
            sink.write(result);
        }
    }
}

/**
 * @brief Updates the observer state and notifies the processing thread.
 *
 * This method is called by the source when there is new data to be processed. It updates the observer state
 * and notifies the processing thread to wake up and process the new data.
 */
void ByteProcessor::Update() {
    observerState = source.GetState();
    cv.notify_one();
}