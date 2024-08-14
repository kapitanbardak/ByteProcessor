//
// Created by Алексей Русских on 14.08.2024.
//

#ifndef BYTEPROCESSOR_ISINK_H
#define BYTEPROCESSOR_ISINK_H

#include <string>

/**
 * @class ISink
 * @brief Interface for a sink in a data processing pipeline.
 *
 * The ISink class defines a standard interface for all sink objects,
 * which are responsible for receiving and handling processed data.
 */
class ISink {
public:
    /**
     * @brief Virtual destructor for ISink.
     *
     * Ensures that derived class destructors are called properly.
     */
    virtual ~ISink() = default;

    /**
     * @brief Pure virtual function to be overridden by concrete sinks.
     *
     * This method is called to write data to the sink.
     *
     * @param data The processed data to be written.
     */
    virtual void write(const std::string &data) = 0;
};

#endif //BYTEPROCESSOR_ISINK_H