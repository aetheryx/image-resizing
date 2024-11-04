#pragma once
#include "../constants.hpp"

#ifndef ALGORITHM_IMPL
#define ALGORITHM_IMPL "../algorithms/algorithm.hpp"
#endif

#if defined(HEMI_CUDA_DISABLE)
#define DEV_TAGS
#else
#define DEV_TAGS __device__
#endif

DEV_TAGS
inline void write_pixel(u32 x, u32 y, u8* input, u8* output);
