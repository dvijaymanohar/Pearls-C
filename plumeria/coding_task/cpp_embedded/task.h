#include <cassert>
#include <cstdint>

#include <climits>

// -----------------------------------------------------------------------------
// Task 1 -- rotation
// -----------------------------------------------------------------------------

// In the ARM instruction set there is a rotate right instruction
// `ROR Rd, Rn, #N` which rotates bits in a 32-bit integer by N with
// wrap-around. Nowadays we program in higher-level languages, but C++ doesn't
// provide such an operation. Implement this function, it does not have to be
// optimized in any way.
uint32_t rotate_right(const uint32_t input, const int n) {
  uint32_t input_word = input;
  uint32_t temp_word = input;
  int bits_to_rotate = n;

  // Rotating 32 bits on a 32-bit integer is the same as rotating 0 bits or if
  // the input is 0, there is nothing to rotate
  if (n == sizeof(uint32_t) || 0 == input || 0 == n)
    return input;

  bits_to_rotate = bits_to_rotate % (sizeof(uint32_t) * 8);

  // Rotate input to the right
  input_word >>= bits_to_rotate;

  // Build mask for carried over bits
  temp_word <<= ((sizeof(uint32_t) * 8 - bits_to_rotate));

  return input_word | temp_word;
}

// -----------------------------------------------------------------------------
// Task 2 -- packing
// -----------------------------------------------------------------------------
// We have an array of 32 floats that are guaranteed to be either -1.0f or
// +1.0f. Write a function that 'bitpacks' this information into a single 32-bit
// word. The i-th bit of the result should be 1 if and only if the i-th float
// is 1.0f. This function does not have to be optimized in any way.
uint32_t pack_floats(const float x[32]) {
  uint32_t bit_pattern = 0;
  int i = 0;

  for (i = 0; i < 32; i++) {
    if (x[i] == 1.0f) {
      bit_pattern |= 1 << i;
    }
  }

  return bit_pattern;
}

// -----------------------------------------------------------------------------
// Task 3 -- binary inner product
// -----------------------------------------------------------------------------

// We want to compute the inner product of two arrays of floats that are all
// either -1.0f or +1.0f. The floats have been bitpacked by the `pack_floats`
// function above.
//
// Given bitpacked words x and y, each representing 32 values, compute the
// (binary) inner product.
//
// Remember that in each 32-bit word a 0-bit represents -1.0f, and a 1-bit
// represents +1.0f, so we have the following multiplication table:
//
// | x float | y float | x bit | y bit | float result | bit result |
// |---------|---------|-------|-------|--------------|------------|
// |  -1.0   |  -1.0   |   0   |   0   |      1.0     |     1      |
// |  -1.0   |   1.0   |   0   |   1   |     -1.0     |     0      |
// |   1.0   |  -1.0   |   1   |   0   |     -1.0     |     0      |
// |   1.0   |   1.0   |   1   |   1   |      1.0     |     1      |
//
// Remember that we want to compute the inner product of the original {-1, +1}
// numbers.
//
// You can reuse the following builtin `popcount`, no need to change it.
int popcount(uint32_t x) { return __builtin_popcountl(x); }

// Assumes little endian
void unint_to_binary(const uint32_t num, int *const binary_num) {
  uint32_t n = num;
  int i = 0;
  while (n > 0) {

    binary_num[i] = n % 2;
    n = n / 2;
    i++;
  }
}

int binary_inner_product(const uint32_t lhs, const uint32_t rhs) {
  int lhs_bits[sizeof(uint32_t) * 8] = {0};
  int rhs_bits[sizeof(uint32_t) * 8] = {0};
  int ret_val = 0;

  unint_to_binary(lhs, lhs_bits);
  unint_to_binary(rhs, rhs_bits);

  for (int i = 0; i < 32; i++) {
    if (lhs_bits[i] == rhs_bits[i])
      ret_val |= 1 << i;
  }

  return ret_val;
}

// -----------------------------------------------------------------------------
// Task 4 -- binary matrix-matrix multiplication
// -----------------------------------------------------------------------------

// Given two matrices of 32-bit words, compute the binary matrix-matrix
// multiplication. You can assume enough memory is allocated beforehand.
//
// The arguments to this function are two pointers to matrices, `lhs` and `rhs`.
//
// `lhs` is row-major, meaning that all the elements for a given row are
// adjacent to each other in memory.
//
// For example, if `lhs` is [[1 2]  then it is stored as [1 2 3 4 5 6]
//                           [3 4]
//                           [5 6]]
//
// `rhs` is column-major, meaning that all the elements for a given column are
// adjacent to each other in memory.
//
// For example, if `rhs` is [[1 2 3]  then it is stored as [1 4 2 5 3 6]
//                           [4 5 6]]
//
// `dst` is row-major, like `lhs`.
//
// Hint: You should use the `binary_inner_product` function from above.
//
void multiply_binary_matrices(const uint32_t *lhs, const uint32_t *rhs,
                              int *dst, int lhs_rows, int lhs_cols,
                              int rhs_rows, int rhs_cols) {
  assert(lhs_cols == rhs_rows);



  // ENTER CODE HERE
}

// -----------------------------------------------------------------------------
// Task 5 - buffer parsing
// -----------------------------------------------------------------------------

// Assume that we have a buffer (for example from a file, or external hardware)
// with the following contents:
//
// | offset | type           | description
// |--------|----------------|--------------
// | 0x0000 | 32-bit int     | number of data parts
// | 0x0004 | 32-bit float   | global_bias
// | 0x0008 | 32-bit int     | offset to result
// | 0x000C | 32-bit int     | offset to data 0
// | 0x0010 | 32-bit int     | offset to data 1
// | 0x0014 | 32-bit int     | offset to data 2
// | ...    | ...            | ...
//
// Each data part gives an offset (from the start of the entire buffer). At that
// offset in the buffer we have:
//
// | offset             | type           | description
// |--------------------|----------------|--------------
// | data_offset + 0x00 | 32-bit float   | x
// | data_offset + 0x04 | 32-bit int     | y
//
// Write a function that does the following:
// For each data part, compute the product (x * y) as a 32-bit float.
// Then take the sum of all results, and add `global_bias` to the final result.
// The result is one 32-bit float value.
// Write this result to the buffer at location 'offset to result'.
//
// Note: no need to worry about big-endian vs little-endian. Assume the data is
// encoded in the format that is native to your system (little-endian).

void parse_data(void *buffer) {
  // ENTER CODE HERE
}

// ENTER CODE HERE