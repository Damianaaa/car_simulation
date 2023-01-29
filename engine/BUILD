load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = [
        "//:imgui",
        "//engine/window_manager:window_manager",
        "//engine/window_manager:side_bar",
        "//engine/models/car_model",
        "//engine/sensors/lidar",
        "//engine/physics/collision_model:collision"
    ],
    # linkopts = ["-lpthread"],
)