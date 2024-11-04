#include "algorithm.hpp"
#include "../constants.hpp"

const u32 CHUNK_SIZE = 4;

DEV_TAGS
inline void write_pixel(u32 x, u32 y, u8* input, u8* output) {
  u32 src_x = (float)x * FACTOR;
  u32 src_y = (float)y * FACTOR;

  u32 dest_idx = ((y * OUT_WIDTH) + x) * CHANNELS;
  for (u8 channel = 0; channel < CHANNELS - 1; channel++) {
    u64 sum = 0;
    for (u32 dy = 0; dy < CHUNK_SIZE; dy++) {
      for (u32 dx = 0; dx < CHUNK_SIZE; dx++) {
        u32 src_idx = (((src_y + dy) * IN_WIDTH) + (src_x + dx)) * CHANNELS;
        sum += input[src_idx + channel];
      }
    }
    u8 avg = sum / (CHUNK_SIZE * CHUNK_SIZE);
    output[dest_idx + channel] = avg;
  }

  output[dest_idx + 3] = 0xFF; // alpha
}
