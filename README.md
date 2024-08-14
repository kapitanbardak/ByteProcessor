# ByteProcessor Program Documentation

## Overview

This C++ program, known as "ByteProcessor," is designed to read bytes from a source, convert them into string characters, and send the converted results to a sink. It strictly adheres to the C++17 standard and follows the Google C++ Style Guide. The source code is structured in the `src` folder and includes a CMake configuration file for building and testing.

## Program Features

- Read bytes from a source in a separate thread.
- Convert bytes into string characters based on specified formats.
- Send the converted string characters to a sink.
- Start and stop the processing thread via class API.
- Unit testing with gtest and gmock.
- Documentation for all classes and functions.

## Byte Processing Logic

The program reads bytes consisting of bits that encode the type and data:

- Bits 6-7: `type` - Encodes the data type.
  - `0b00`: Unsigned integer.
  - `0b01`: Signed integer.
  - `0b10`: Latin alphabet letter ('a' = `0b000000`, 'b' = `0b000001`, etc.).
- Bits 0-5: `data` - Stores the actual data.

## Program Structure

The program follows object-oriented principles and might implement the Model-View-Controller (MVC) pattern:

- **Model**: ByteProcessor class handles the core processing logic.
- **View**: Not applicable in this context.
- **Controller**: Not applicable in this context.

## Design Patterns

The program incorporates the following design patterns:

1. **Observer Pattern**: `ISource` notifies `ByteProcessor` when new data is available.
2. **Singleton Pattern**: Ensures a single instance of the `ByteProcessor` main processing class.
3. **Command Pattern**: Encapsulates actions for reading, processing, and writing data.

## Class Overview

### ByteProcessor Class

The `ByteProcessor` class is responsible for reading bytes from a source, converting them into string characters, and writing the results to a sink in a separate thread.

#### Public Methods

- `ByteProcessor(ISource& source, ISink& sink)`: Constructor.
- `~ByteProcessor()`: Destructor.
- `void start()`: Starts the processing thread.
- `void stop()`: Stops the processing thread.
- `void Update()`: Updates the observer state and notifies the processing thread.

### IObserver Interface

Defines the observer interface in the observer pattern.

#### Public Methods

- `virtual ~IObserver() = default`: Virtual destructor.
- `virtual void Update() = 0`: Pure virtual method to notify the observer of a state change.

### ISink Interface

Defines the sink interface for receiving and handling processed data.

#### Public Methods

- `virtual ~ISink() = default`: Virtual destructor.
- `virtual void write(const std::string& data) = 0`: Pure virtual method to write data to the sink.

### ISource Interface

Defines the source interface for providing raw data.

#### Public Methods

- `virtual ~ISource() = default`: Virtual destructor.
- `virtual uint8_t read() = 0`: Pure virtual method to read data from the source.

### ISubject Interface

Defines the subject interface in the observer pattern.

#### Public Methods

- `virtual ~ISubject() = default`: Virtual destructor.
- `virtual bool GetState() = 0`: Pure virtual method to get the state of the subject.
- `virtual void Attach(IObserver* observer) = 0`: Pure virtual method to attach an observer.
- `virtual void Detach(IObserver* observer) = 0`: Pure virtual method to detach an observer.

## Unit Testing

Extensive unit tests cover modules related to byte processing, conversion, and data handling. Tests ensure the reliability and correctness of the program.