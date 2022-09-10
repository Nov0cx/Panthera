load("//extern/vulkan/rules/platform:windows.bzl", "vulkan_windows")
load("//extern/vulkan/rules/platform:linux.bzl", "vulkan_linux")
load("//extern/vulkan/rules/platform:macos.bzl", "vulkan_macos")

def vulkan_repositories(sdk_path = None):
    """Loads the required repositories into the workspace.

    Args:
        sdk_path: An absolute or relative path to a Vulkan SDK.
            Either this attribute or the $VULKAN_SDK environment variable must be set.
    """

    vulkan_windows(
        name = "vulkan_windows",
        path = sdk_path,
    )

    vulkan_linux(
        name = "vulkan_linux",
        path = sdk_path,
    )

    vulkan_macos(
        name = "vulkan_macos",
        path = sdk_path,
    )
