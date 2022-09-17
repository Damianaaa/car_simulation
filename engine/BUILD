load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = [
        "//:imgui",
        "//engine/window_manager",
        "//engine/models/car_model"
    ],
)