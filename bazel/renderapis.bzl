def load_api_configs():
    native.config_setting(
        name = "opengl",
        define_values = {"USE_OPENGL": "1"},
        visibility = ["//visibility:public"],
    )
    native.config_setting(
        name = "vulkan",
        define_values = {"USE_VULKAN": "1"},
        visibility = ["//visibility:public"],
    )
    native.config_setting(
        name = "metal",
        define_values = {"USE_METAL": "1"},
        visibility = ["//visibility:public"],
    )
    native.config_setting(
        name = "d3d12",
        define_values = {"USE_D3D12": "1"},
        visibility = ["//visibility:public"],
    )
    # all of the above
    native.config_setting(
        name = "all_apis",
        define_values = { "ALL_APIS": "1" },
        visibility = ["//visibility:public"],
    )