#include <stdio.h>
typedef unsigned char uint8_t;

// array is a bit stream of data stored as bytes where the MSB is the leading
// bit extract every 5th bit starting with the 3rd bit of the stream. Accumulate
// into a byte (MSB first) and print (as a char) once 8 bits have been
// extracted. Repeat until the end of stream.

uint8_t array[] = {0x07, 0xc0, 0x60, 0x0f, 0x52, 0x07, 0xc0, 0x0c, 0x8c, 0x2f,
                   0x07, 0xc0, 0xc1, 0xac, 0xb4, 0x05, 0xd1, 0x41, 0x0e, 0x85,
                   0x07, 0x06, 0x80, 0x72, 0x14, 0x07, 0x06, 0x00, 0x70, 0x19,
                   0x06, 0x0f, 0x82, 0x11, 0x08, 0x06, 0x0e, 0x88, 0x62, 0x10,
                   0x04, 0x1e, 0x08, 0x00, 0x10, 0x04, 0x1e, 0x08, 0x42, 0x00,
                   0x04, 0x1f, 0x00, 0x40, 0x00};

void extract(uint8_t *byteArray, int length) {
  uint8_t channel_no = 0;  // To keep track of the channel
  uint8_t accumulator = 0; // Variable to accumalate the bits
  uint8_t bit_counter = 0; // Variable to keep track of bits in a byte
  int bit_pos = 0;
  uint8_t array_index = 0;
  uint8_t extracted_bit[3] = {0};
  uint8_t extracted_bit_counter = 0;

  // Repeat till the end of the stream
  for (array_index = 0; array_index < length; array_index++) {
    for (bit_pos = 7; bit_pos >= 0; bit_pos--) {
      // Extract the every 5th bit with the 3rd bit of the channel 2 (channels:
      // 0 to 4)
      if (channel_no == 2) {
        extracted_bit[extracted_bit_counter] =
            (byteArray[array_index] >> bit_pos) & 1;

        extracted_bit_counter++;
        // printf("Extracted bit counter = %d\n", extracted_bit_counter);
      }

      channel_no++;

      // Resetting the channel no.
      if (channel_no > 4)
        channel_no = 0;
    }

    // Accumalating the extracted bits into a byte
    for (int i = 0; i < extracted_bit_counter; i++) {
      accumulator |= extracted_bit[i] << (8 - bit_counter);

      // Once it extracts the bit
      bit_counter++;
    }

    extracted_bit_counter = 0;

    // 8 bits have been accumulated, printing the character
    if (bit_counter % 8 == 0) {
      printf("%c", accumulator);

      // Resetting the accumulator and bit_counters
      accumulator = 0;
      bit_counter = 0;
    }
  }
}

int main() {
  extract(array, sizeof(array));

  return 0;
}

/**
  Bit 7 - Channel 0
      6 - Channel 1
      5 - Channel 2
      4 - Channel 3
      3 - Channel 4
      2 - Channel 0
      1 - Channel 1
      0 - Channel 2

      7 - Channel 3
      6 - Channel 4
      5 - Channel 0
      4 - Channel 1
      3 - Channel 2
      2 - Channel 3
      1 - Channel 4
      0 - Channel 0
*/