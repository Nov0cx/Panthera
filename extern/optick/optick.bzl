def _impl(ctx):
    optick_path = ctx.os.environ["OPTICK"]
    if optick_path == '' or optick_path == None:
        fail('OPTICK environment variable not set')

    ctx.symlink(optick_path, "optick_path")

    buildfile = """
cc_library(
    name = "optick_hdrs",
    hdrs = glob(["optick_path/src/*.h"]),
    defines = [
            "OPTICK_ENABLE_GPU_VULKAN=0",
            "OPTICK_ENABLE_GPU_D3D12=0",
            "OPTICK_LIB=1",
            "OPTICK_EXPORTS",
    ],
    visibility = ["//visibility:public"],
    strip_include_prefix = "optick_path/src/",
)

cc_binary(
    name =  "optick",
    srcs = glob(["optick_path/src/*.cpp"]),

    defines = [
        "OPTICK_ENABLE_GPU_VULKAN=0",
        "OPTICK_ENABLE_GPU_D3D12=0",
        "OPTICK_LIB=1",
        "OPTICK_EXPORTS",
    ],
    visibility = ["//visibility:public"],
    linkshared = True,
    deps = [":optick_hdrs"],
    #strip_include_prefix = "optick_path/src/",
)
    """

    ctx.file("BUILD.bazel", buildfile)

optick_lib = repository_rule(
    implementation = _impl,
    environ = ['OPTICK'],
)

def load_optick_lib():
    optick_lib(
        name = 'optick_lib',
    )