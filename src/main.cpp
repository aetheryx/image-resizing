#include <fstream>
#include <thread>
#include <vector>
#include "hemi/array.h"

#include "constants.hpp"
#include "platform/platform.hpp"

hemi::Array<u8> input = hemi::Array<u8>(IN_WIDTH * IN_HEIGHT * sizeof(u32));
hemi::Array<u8> output = hemi::Array<u8>(OUT_WIDTH * OUT_HEIGHT * sizeof(u32));

int main() {
  std::ifstream input_file(INPUT_FILE, std::ios::binary | std::ios::ate);
  input_file.seekg(0, std::ios::beg);

  if (!input_file.read((char*)input.hostPtr(), input.size())) {
    printf("failed to read\n");
    exit(1);
  }

  for (int warmups = 0; warmups < 3; warmups++) {
    platform_run(input, output);
  }

  u64 t_sum = 0;
  u32 runs = 0;
  while (t_sum < 5000000) {
    t_sum += platform_run(input, output);
    runs++;
  }

  printf("%d\n", runs);

  std::ofstream output_file(OUTPUT_FILE, std::ios::out | std::ios::binary);
  output_file.write((char*)output.hostPtr(), output.size());
  output_file.close();
}
