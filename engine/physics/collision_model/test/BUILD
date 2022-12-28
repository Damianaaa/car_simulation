load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_test")

cc_test(
    name = "collision_model_test",
    srcs = ["collision_model_test.cpp"],
    deps = [
        "//engine/physics/collision_model:collision",
        "@com_google_googletest//:gtest_main",
    ],
)
