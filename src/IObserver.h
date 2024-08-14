//
// Created by Алексей Русских on 14.08.2024.
//

#ifndef BYTEPROCESSOR_OBSERVER_H
#define BYTEPROCESSOR_OBSERVER_H

/**
 * @class IObserver
 * @brief Interface for observer in the observer pattern.
 *
 * The IObserver class defines a standard interface for all observer objects,
 * which need to be notified of changes in the subject they are observing.
 */
class IObserver {
public:
    /**
     * @brief Virtual destructor for IObserver.
     *
     * Ensures that derived class destructors are called properly.
     */
    virtual ~IObserver() = default;

    /**
     * @brief Pure virtual function to be overridden by concrete observers.
     *
     * This method is called to notify the observer of a change in the subject's state.
     */
    virtual void Update() = 0;
};

#endif //BYTEPROCESSOR_OBSERVER_H