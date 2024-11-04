CXX := "g++"
NVCC := "nvcc"
FLAGS := "-O3 -Wno-deprecated-declarations -std=c++17 -I third_party/hemi"

# builds an executable for a given platform and algorithm
# platform: `cpu` | `gpu`
# algorithm: `nearest-neighbor` | `bilinear-interpolation`
build platform algorithm:
  #!/bin/bash -x
  if [[ {{platform}} == "cpu" ]]; then
    BASE="{{CXX}} src/platform/cpu.cpp -D HEMI_CUDA_DISABLE"
  else
    BASE="{{NVCC}} src/platform/gpu.cu"
  fi

  $BASE src/main.cpp {{FLAGS}} -DALGORITHM_IMPL=\"../algorithms/{{algorithm}}.cpp\" -o build/bin

# builds and runs an executable for a given platform and algorithm
# platform: `cpu` | `gpu`
# algorithm: `nearest-neighbor` | `bilinear-interpolation`
run platform algorithm: (build platform algorithm)
  build/bin

# converts a generated rgba image to a viewable PNG, displays it
render size:
  rm build/output.png || exit 0
  convert -depth 8 -size {{size}} build/output.rgba build/output.png
  code build/output.png

# generates `input_images` of various tile sizes from a URL
# url: the JPG image to use as the input
gen_inputs url:
  #!/bin/bash
  curl {{url}} > input_images/input.jpg
  convert input_images/input.jpg input_images/input.png
  convert input_images/input.png -depth 8 input_images/input.rgba
  for tile_sz in {2..8}; do
    inputs=$(printf 'input_images/input.png %.0s' $(seq 1 $((tile_sz*tile_sz))))
    dim="${tile_sz}x${tile_sz}"
    montage $inputs -tile "$dim" -geometry +0+0 input_images/tile-$dim.png
    convert input_images/tile-$dim.png -depth 8 input_images/tile-$dim.rgba
  done