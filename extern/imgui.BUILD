cc_library(
    name = "imgui",
    srcs = ["imgui.cpp", "imgui_draw.cpp", "imgui_tables.cpp", "imgui_widgets.cpp", "imgui_demo.cpp","backends/imgui_impl_glfw.cpp", "backends/imgui_impl_opengl3.cpp"],
    hdrs = ["imconfig.h", "imgui.h", "imgui_internal.h", "imstb_rectpack.h", "imstb_textedit.h", "imstb_truetype.h","backends/imgui_impl_glfw.h", "backends/imgui_impl_opengl3.h", "backends/imgui_impl_opengl3_loader.h"],
    deps = [
          "@com_github_Nov0cx_glad//:glad",
          "@com_github_Nov0cx_glfw//:glfw",
          ],
    visibility = ["//visibility:public"],
)