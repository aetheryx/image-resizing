#include <vector>
#include <thread>
#include "platform.hpp"
#include "../algorithms/algorithm.hpp"
#include "../constants.hpp"
#include ALGORITHM_IMPL

void resize(int id, u8* input, u8* output) {
  for (u32 y = id; y < OUT_HEIGHT; y += NUM_THREADS) {
    for (u32 x = 0; x < OUT_WIDTH; x++) {
      write_pixel(x, y, input, output);
    }
  }
}

u64 platform_run(hemi::Array<u8> &input, hemi::Array<u8> &output) {
  u8* input_ptr = input.hostPtr();
  u8* output_ptr = output.hostPtr();

  std::vector<std::thread> threads(NUM_THREADS);

  const auto before = std::chrono::system_clock::now();
  for (u32 i = 0; i < NUM_THREADS; i++) {
    threads[i] = std::thread(resize, i, input_ptr, output_ptr);
  }
  for (auto& th : threads) {
    th.join();
  }
  const auto after = std::chrono::system_clock::now();

  return std::chrono::duration_cast<std::chrono::microseconds>(after - before).count();
}
