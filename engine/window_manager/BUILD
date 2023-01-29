cc_library(
    name = "window_manager",
    hdrs = ["hdr/window_manager.h"],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "textures",
    hdrs = ["hdr/textures.h"],
    srcs = ["src/textures.cpp"],
    deps = ["//engine/physics/collision_model:collision"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "texture_slider",
    hdrs = ["hdr/texture_slider.h"],
    srcs = ["src/texture_slider.cpp"],
    deps = [":textures"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "button",
    hdrs = ["hdr/button.h"],
    srcs = ["src/button.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "state_button",
    hdrs = ["hdr/state_button.h"],
    srcs = ["src/state_button.cpp"],
    visibility = ["//visibility:public"],
    deps = [":button"],
)

cc_library(
    name = "texture_adder",
    hdrs = ["hdr/texture_adder.h"],
    srcs = ["src/texture_adder.cpp"],
    visibility = ["//visibility:public"],
    deps = [
        ":button",
        ":state_button",
        ":textures",
        ":texture_slider",
        ":window_manager",
    ],
)

cc_library(
    name = "state_observer",
    hdrs = ["hdr/state_observer.h"],
    srcs = ["src/state_observer.cpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "side_bar",
    hdrs = ["hdr/side_bar.h"],
    srcs = ["src/side_bar.cpp"],
    deps = [
        ":button",
        ":state_button",
        ":state_observer",
        ":texture_slider",
        ":texture_adder",
        ":window_manager",
    ],
    visibility = ["//visibility:public"],
)