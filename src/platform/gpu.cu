#include <thread>
#include "platform.hpp"
#include "../algorithms/algorithm.hpp"
#include "../constants.hpp"
#include ALGORITHM_IMPL

__global__
void resize(u8* input, u8* output) {
  uint x = (blockIdx.x * blockDim.x) + threadIdx.x;
  uint y = (blockIdx.y * blockDim.y) + threadIdx.y;
  write_pixel(x, y, input, output);
}

u64 platform_run(hemi::Array<u8> &input, hemi::Array<u8> &output) {
  u8* input_ptr = input.devicePtr();
  u8* output_ptr = output.devicePtr();

  dim3 threadsPerBlock(16, 16);
  dim3 numBlocks((OUT_WIDTH/threadsPerBlock.x) + 1, (OUT_HEIGHT/threadsPerBlock.y) + 1);

  const auto before = std::chrono::system_clock::now();
  resize<<<numBlocks, threadsPerBlock>>>(input_ptr, output_ptr);
  cudaDeviceSynchronize();
  const auto after = std::chrono::system_clock::now();

  return std::chrono::duration_cast<std::chrono::microseconds>(after - before).count();
}
