![windows](https://github.com/Nov0cx/Panthera/actions/workflows/windows.yml/badge.svg)
![ubuntu](https://github.com/Nov0cx/Panthera/actions/workflows/ubuntu.yml/badge.svg)

# Panthera
 > This is an open source C++ Game Engine under the [Apache 2.0 license](https://www.apache.org/licenses/LICENSE-2.0).
 > <br/>I'm planning to use [Carbon-Lang](https://github.com/carbon-language/carbon-lang) in the future.
 > <br/><br/>
 > I want to implement [Rust](https://www.rust-lang.org/) and [Go](https://go.dev/) as scripting languages.
 
# Setup
In the setup phase, bazel will run a shell script (works on Windows) 
and install [Vulkan](https://www.vulkan.org/) if it isn't already installed. 
It will create a Lib folder which is excluded form git.
The script will open the Vulkan Installer there you have to download core and all debug options.
<br/>
<br/>
Run:
```bash
bazel run //vulkan/...
```

# Build

### Not MSVC

Build all:
```bash
bazel build --config=not_msvc_config //...
```
Build core:
```bash
bazel build --config=not_msvc_config //Panthera-Core/...
```
Run Leopardus(Editor):
```bash
bazel run --config=not_msvc_config //Leopardus:Leopardus
```

#### Optional:
Use --cxxopt="-std=c++20" instead of --config=not_msvc_config

### MSVC
Build all:
```bash
bazel build --config=msvc_config //...
```
Build core:
```bash
bazel build --config=msvc_config //Panthera-Core/...
```
Run Leopardus(Editor):
```bash
bazel run --config=msvc_config //Leopardus:Leopardus
```

# Dependencies:
We only depend on [Bazel](https://bazel.build/install/bazelisk).
Bazel does the complete package management for us.

