cl_opts = ["/std:c++20"]
clang_cl_opts = ["/std:c++20"]
gnu_opts = ["-std=c++20"]

copts = select({
    "@bazel_tools//tools/cpp:msvc": cl_opts,
    "@bazel_tools//tools/cpp:clang-cl": clang_cl_opts,
    "//conditions:default": gnu_opts,
})