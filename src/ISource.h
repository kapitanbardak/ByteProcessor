//
// Created by Алексей Русских on 14.08.2024.
//

#ifndef BYTEPROCESSOR_ISOURCE_H
#define BYTEPROCESSOR_ISOURCE_H

#include <stdint.h>
#include "ISubject.h"

/**
 * @class ISource
 * @brief Interface for a data source in a data processing pipeline.
 *
 * The ISource class defines a standard interface for all source objects,
 * which are responsible for providing raw data to be processed.
 */
class ISource : public ISubject {
public:
    /**
     * @brief Virtual destructor for ISource.
     *
     * Ensures that derived class destructors are called properly.
     */
    virtual ~ISource() = default;

    /**
     * @brief Pure virtual function to be overridden by concrete sources.
     *
     * This method is called to read data from the source.
     *
     * @return A byte of data read from the source.
     */
    virtual uint8_t read() = 0;
};

#endif //BYTEPROCESSOR_ISOURCE_H