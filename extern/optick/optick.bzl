def _impl(ctx):
    optick_path = ctx.os.environ["OPTICK"]
    if optick_path == '' or optick_path == None:
        fail('OPTICK environment variable not set')

    ctx.symlink(optick_path, "optick_path")

    buildfile = """
cc_library(
    name = "optick",
    srcs = glob(["optick_path/src/*.cpp"]),
    hdrs = glob(["optick_path/src/*.h"]),
    defines = [
        "OPTICK_ENABLE_GPU_VULKAN=0",
        "OPTICK_ENABLE_GPU_D3D12=0",
    ],
    visibility = ["//visibility:public"],
    strip_include_prefix = "optick_path/src/",
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