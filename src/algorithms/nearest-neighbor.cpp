#include "algorithm.hpp"
#include "../constants.hpp"

DEV_TAGS
inline void write_pixel(u32 x, u32 y, u8* input, u8* output) {
  u32 src_x = (float)x * FACTOR;
  u32 src_y = (float)y * FACTOR;
  u32 src_idx = ((src_y * IN_WIDTH) + src_x) * CHANNELS;
  u32 dest_idx = ((y * OUT_WIDTH) + x) * CHANNELS;

  for (u32 channel = 0; channel < CHANNELS; channel++) {
    output[dest_idx + channel] = input[src_idx + channel];
  }
}
