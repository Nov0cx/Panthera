
![windows](https://github.com/Nov0cx/Panthera/actions/workflows/windows.yml/badge.svg)
![ubuntu](https://github.com/Nov0cx/Panthera/actions/workflows/ubuntu.yml/badge.svg)
<br/>
[![Roadmap](https://upload.wikimedia.org/wikipedia/en/8/8c/Trello_logo.svg)](https://trello.com/b/lO2g2KYQ/panthera)

##### Disclaimer: Current development only under windows

# Panthera
 > This is an open source C++ Game Engine under the [Apache 2.0 license](https://www.apache.org/licenses/LICENSE-2.0).
 > <br/>I'm planning to use [Carbon-Lang](https://github.com/carbon-language/carbon-lang) in the future.
 > <br/><br/>
 > I want to implement [Rust](https://www.rust-lang.org/) and [Go](https://go.dev/) as scripting languages.
 
# Setup
In the setup phase, bazel will run 2 python scripts
and install [Vulkan](https://www.vulkan.org/) if it isn't already installed.
The script will open the Vulkan Installer there you have to download core and all debug options.
<br/>
<br/>
Run:
```bash
bazel run //vulkan:Packages
bazel run //vulkan:VulkanDownload
```

Oneliner:
```bash
git clone https://github.com/Nov0cx/Panthera.git && cd Panthera && bazel run //vulkan:Packages && bazel run //vulkan:VulkanDownload && bazel run //extern:Optick
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
Run Leopardus (Editor):
```bash
bazel run --config=not_msvc_config //Leopardus:Leopardus
```

For debug append '_debug' to the config name. For release builds append '_release' to the config name.

### MSVC
Build all:
```bash
bazel build --config=msvc_config //...
```
Build core:
```bash
bazel build --config=msvc_config //Panthera-Core/...
```
Run Leopardus (Editor):
```bash
bazel run --config=msvc_config //Leopardus:Leopardus
```

For debug append '_debug' to the config name. For release builds append '_release' to the config name.

# Dependencies:
We only depend on [Bazel](https://bazel.build/install/bazelisk) if Vulkan is already installed (otherwise python3 is needed).
Bazel does the complete package management for us. If you install bazelisk, rename the file into bazel and add it to the path.

