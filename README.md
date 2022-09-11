
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
Note: clang-cl is in work

### Linux
Not really working yet


