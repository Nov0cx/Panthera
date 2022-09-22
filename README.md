
![windows](https://github.com/Nov0cx/Panthera/actions/workflows/windows.yml/badge.svg)
![ubuntu](https://github.com/Nov0cx/Panthera/actions/workflows/ubuntu.yml/badge.svg)
<br/>
[![Rework Roadmap](https://img.shields.io/badge/Rework%20Roadmap-Click%20Here-blue)](https://trello.com/b/nQbj6DuP/panthera-rework)
[![Main Roadmap](https://img.shields.io/badge/Main%20Roadmap-Click%20Here-blue)](https://trello.com/b/lO2g2KYQ/panthera)

##### Disclaimer: Current development only under windows

# Panthera
 > This is an open source C++ Game Engine under the [Apache 2.0 license](https://www.apache.org/licenses/LICENSE-2.0).
 > <br/>I'm planning to use [Carbon-Lang](https://github.com/carbon-language/carbon-lang) in the future.
 > <br/><br/>
 > I want to implement [Rust](https://www.rust-lang.org/) and [Go](https://go.dev/) as scripting languages.
 
# Setup
 1. Clone the repository (git clone https://github.com/Nov0cx/Panthera.git)
 2. Install [Bazel](https://bazel.build/install/bazelisk) and add it to your PATH
 3. Install [Python](https://www.python.org/downloads/)
 4. run `cd Panthera && bazel run //extern/vulkan:Packages && bazel run //extern/vulkan:VulkanDownload`

# Build

-------------

### Windows
```bash
bazel run --config=msvc_win_x64_rel //Leopardus:Leopardus
```
Note: clang-cl is in [work](https://github.com/bazelbuild/bazel/issues/16249) 

### Linux
Not really working yet


