# image-resizing
This repository includes the source code, tooling and statistical analysis for the SE R&D research paper.

## Application
### Setup (macOS)
1. Install the C++ compiler through Xcode: `xcode-select --install`
2. Install the `ImageMagick` programs through Brew: `brew install imagemagick`
3. Install the `just` recipe runner through Brew: `brew install just`

### Setup (GPUs)
1. Deploy a server with an NVIDIA GPU, e.g. from [TensorDock](https://www.tensordock.com/)
2. Install the CUDA toolkit from [developer.nvidia.com](https://developer.nvidia.com/cuda-downloads?target_os=Linux&target_arch=x86_64&Distribution=Ubuntu&target_version=22.04&target_type=deb_network)
3. Install the `ImageMagick` programs through apt: `sudo apt install imagemagick`
4. Install the `just` recipe runner, see [casey/just](https://github.com/casey/just?tab=readme-ov-file#linux).

### Usage
1. `mkdir build && mkdir input_images`
2. Generate the input images from a URL using `just gen_inputs`, e.g. `just gen_inputs https://4kwallpapers.com/images/wallpapers/mclaren-w1-supercar-7680x4320-19246.jpg`
3. Now you can run the application: run `just run <platform> <algorithm>`, e.g. `just run cpu bilinear-interpolation`. This will write the downsized image to `build/output.rgba`
4. To convert the image from RGBA to PNG and open it, run `just render <size>`, where `<size>` is the output resolution configured by the scaling factor in `src/constants.hpp`. Example: `just render 1920x1080`

## Benchmarks
- Raw data was generated using [`benchmarking/runner/run.js`](benchmarking/runner/run.js), which runs each configuration (across factors, platforms and algorithms) 10 times.
- Data is aggregated to a CSV file using [`benchmarking/runner/aggregate.js`](benchmarking/runner/aggregate.js).
- CSV file is read by the Jupyter notebooks, which use pandas and matplotlib to generate graphs. See [bar](benchmarking/notebooks/bar.ipynb), [line](benchmarking/notebooks/line.ipynb) and [energy](benchmarking/notebooks/energy.ipynb).