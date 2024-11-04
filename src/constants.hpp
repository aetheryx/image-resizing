#pragma once
#include <cstdint>

// Typedefs
typedef uint64_t u64;
typedef uint32_t u32;
typedef uint8_t u8;

// Constants
static const u32 IN_WIDTH = 7680;
static const u32 IN_HEIGHT = 4320;
static const float FACTOR = 3.0;
static const u32 OUT_WIDTH = ((float)IN_WIDTH / FACTOR);
static const u32 OUT_HEIGHT = ((float)IN_HEIGHT / FACTOR);
static const u32 CHANNELS = 4;
static const u32 NUM_THREADS = 16;

static const char* INPUT_FILE = "input_images/input.rgba";
static const char* OUTPUT_FILE = "build/output.rgba";
