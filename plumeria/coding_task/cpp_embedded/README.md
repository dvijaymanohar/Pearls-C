# C++ Interview Task

Welcome to this coding test. In this test you will be working with many bitwise operations but don't worry if you are not too familiar with that, we'll give you enough hints.

At Plumerai, we have developed neural networks where the activations (inputs to a layer) and weights (parameters of the network) are 1-bit numbers.

You'll be asked to implement some functions for operating on 1-bit values in an efficient way.

Before you start, here are some definitions and reminders related to bitwise operations.

## Definitions

For simplicity we will assume that we are working on a 32-bit system, so everything that happens is in blocks of 32 bits.
A [word](https://en.wikipedia.org/wiki/Word_(computer_architecture)) simply means one piece of data that is 32 bits wide, this could be an integer or float or something else.

The `popcount` of a word is the number of 1-bits in that word. So when `x` is `000...00001101101` (in binary) then `popcount(x) = 5`.

## Reminders about bits and bitwise operations

If `x` is a 32-bit word, for example:
```cpp
uint32_t x = 0b01011111000010111011010011100111;
```
Then:
- the bits on the left side are the *most* significant bits (bit 31, bit 30, bit 29).
- the bits on the right side are the *least* significant bits (bit 0, bit 1, bit 2).

| C++ expression | Meaning                                                |
| -------------- | ------------------------------------------------------ |
| `0b1011`       | Constant bitstring (with `1011` at the rightmost bits) |
| `~x`           | Negate the bitstring `x` (flip all bits in `x`)        |
| `x & y`        | Take the bitwise `AND` of `x` and `y`                  |
| `x | y`        | Take the bitwise `OR` of `x` and `y`                   |
| `x ^ y`        | Take the bitwise `XOR` of `x` and `y`                  |
| `x << y`       | Shift the bits in `x` to the left `y` steps            |
| `x >> y`       | Shift the bits in `x` to the right `y` steps           |


## Getting Started

You should be able to build and run the example code by executing the following command on your shell:

```
make
```

We've prepared two files:
- `task.h`: Includes descriptions of the programming tasks and some boilderplate functions.
- `task_test.cpp`: This is used to test the correctness of the functions defined in `task.h`.

Please let us know if you run into problems building the provided boilerplate on your system, we are happy to provide a shared environment for you to work on this task. Feel free to use your own IDE and build system, by starting a new project with `task.h` and `task_test.cpp` if you feel more comfortable with it.
