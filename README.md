# ideas

## implementation
* recurse through functions, instrumenting and counting captures as you go
  * Need a separate copy for each function call to get the correct bit number...or, can we pass an base number arg?
* handling loops?
  * max iterations could be a setting
* store bits for each captured variables corresponding to index capture number as you might go through different branches which do or do not hit captures
* find the maximum usage for any given path and allocate that much for each call of the fragment shader
  * we could either overallocate, or do a first pass where we just count the total number of fragments...requires a readback

## features
* fragment view or frame view
  * fragment view shows you individual values for a fragment
  * frame view puts all fragments into an image to view at once visually

## options
* capture sub-section of the render frame for less memory usage
* max iterations for unbounded loops

# Tint

---
Note: This repo is read-only, minimized mirror of [the Dawn repo](https://dawn.googlesource.com/dawn).

**Tint changes should be made in [the Dawn repo](https://dawn.googlesource.com/dawn).**

---

Tint is a compiler for the WebGPU Shader Language (WGSL).

This is not an officially supported Google product.

## Requirements

* Git
* CMake (3.10.2 or later)
* Ninja (or other build tool)
* Python, for fetching dependencies
* [depot_tools] in your path

## Build options

* `TINT_BUILD_SPV_READER` : enable the SPIR-V input reader (off by default)
* `TINT_BUILD_WGSL_READER` : enable the WGSL input reader (on by default)
* `TINT_BUILD_SPV_WRITER` : enable the SPIR-V output writer (on by default)
* `TINT_BUILD_WGSL_WRITER` : enable the WGSL output writer (on by default)
* `TINT_BUILD_FUZZERS` : enable building fuzzzers (off by default)

## Building
Tint uses Chromium dependency management so you need to install [depot_tools]
and add it to your PATH.

[depot_tools]: http://commondatastorage.googleapis.com/chrome-infra-docs/flat/depot_tools/docs/html/depot_tools_tutorial.html#_setting_up

### Getting source & dependencies

```sh
# Clone the repo as "tint"
git clone https://dawn.googlesource.com/tint tint
cd tint

# Bootstrap the gclient configuration
cp standalone.gclient .gclient

# Fetch external dependencies and toolchains with gclient
gclient sync
```

### Compiling using CMake + Ninja

```sh
mkdir -p out/Debug
cd out/Debug
cmake -GNinja ../..
ninja # or autoninja
```

### Compiling using CMake + make

```sh
mkdir -p out/Debug
cd out/Debug
cmake ../..
make # -j N for N-way parallel build
```

### Compiling using gn + ninja

```sh
mkdir -p out/Debug
gn gen out/Debug
autoninja -C out/Debug
```

### Fuzzers on MacOS

If you are attempting fuzz, using `TINT_BUILD_FUZZERS=ON`, the version of llvm
in the XCode SDK does not have the needed libfuzzer functionality included.

The build error that you will see from using the XCode SDK will look something
like this:

```text
ld: file not found:/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/11.0.0/lib/darwin/libclang_rt.fuzzer_osx.a
```

The solution to this problem is to use a full version llvm, like what you would
get via homebrew, `brew install llvm`, and use something like `CC=<path to full
clang> cmake ..` to setup a build using that toolchain.

### Checking [chromium-style] issues in CMake builds

The gn based work flow uses the Chromium toolchain for building in anticipation
of integration of Tint into Chromium based projects. This toolchain has
additional plugins for checking for style issues, which are marked with
[chromium-style] in log messages. This means that this toolchain is more strict
then the default clang toolchain.

In the future we will have a CQ that will build this work flow and flag issues
automatically. Until that is in place, to avoid causing breakages you can run
the [chromium-style] checks using the CMake based work flows. This requires
setting `CC` to the version of clang checked out by `gclient sync` and setting
the `TINT_CHECK_CHROMIUM_STYLE` to `ON`.

```sh
mkdir -p out/style
cd out/style
cmake ../..
CC=../../third_party/llvm-build/Release+Asserts/bin/clang cmake -DTINT_CHECK_CHROMIUM_STYLE=ON ../../ # add -GNinja for ninja builds
```

## Issues

Please file any issues or feature requests at
https://bugs.chromium.org/p/tint/issues/entry

## Contributing

Please see the [contributing guide in the Dawn repo](https://dawn.googlesource.com/dawn/+/refs/heads/main/CONTRIBUTING.md).
