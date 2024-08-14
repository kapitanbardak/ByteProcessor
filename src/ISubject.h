//
// Created by Алексей Русских on 14.08.2024.
//

#ifndef BYTEPROCESSOR_ISUBJECT_H
#define BYTEPROCESSOR_ISUBJECT_H

#include "IObserver.h"

/**
 * @class ISubject
 * @brief Interface for the subject in the observer pattern.
 *
 * The ISubject class defines a standard interface for all subject objects,
 * which are observed by observers. It includes methods to attach, detach,
 * and notify observers, as well as to get the state of the subject.
 */
class ISubject {
public:
    /**
     * @brief Virtual destructor for ISubject.
     *
     * Ensures that derived class destructors are called properly.
     */
    virtual ~ISubject() = default;

    /**
     * @brief Pure virtual function to get the state of the subject.
     *
     * This method is called to retrieve the current state of the subject.
     *
     * @return The current state of the subject as a boolean value.
     */
    virtual bool GetState() = 0;

    /**
     * @brief Pure virtual function to attach an observer to the subject.
     *
     * This method is called to attach an observer to the subject so that it can be notified of state changes.
     *
     * @param observer Pointer to the observer to be attached.
     */
    virtual void Attach(IObserver* observer) = 0;

    /**
     * @brief Pure virtual function to detach an observer from the subject.
     *
     * This method is called to detach an observer from the subject, stopping it from receiving state change notifications.
     *
     * @param observer Pointer to the observer to be detached.
     */
    virtual void Detach(IObserver* observer) = 0;

private:
    /**
     * @brief Pure virtual function to notify all attached observers of a state change.
     *
     * This method is called to notify all observers that the subject's state has changed.
     */
    virtual void Notify() = 0;
};

#endif //BYTEPROCESSOR_ISUBJECT_H