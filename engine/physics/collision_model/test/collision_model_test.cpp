#include "engine/physics/collision_model/hdr/area_description.h"

#include <SFML/Graphics.hpp>
#include "gtest/gtest.h"
namespace physics
{

struct LineCollisionTestParameters {
    LineDescription l1;
    LineDescription l2;
    sf::Vector2f intersection_point;
};

class LineCollisionTest : public ::testing::TestWithParam<LineCollisionTestParameters>
{};

TEST_P(LineCollisionTest, Test)
{
    const auto params = GetParam();
    const auto result = params.l1.getIntersectionPoint(params.l2);

    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), params.intersection_point);
}

INSTANTIATE_TEST_SUITE_P(TestIntersections, LineCollisionTest, ::testing::Values(
    LineCollisionTestParameters{
        LineDescription{sf::Vector2f{2.f, 0.f}, sf::Vector2f{2.f, 2.f}},
        LineDescription{sf::Vector2f{1.f, 1.f}, sf::Vector2f{3.f, 1.f}},
        sf::Vector2f{2.f, 1.f}
    },
    LineCollisionTestParameters{
        LineDescription{sf::Vector2f{2.f, 2.f}, sf::Vector2f{2.f, 0.f}},
        LineDescription{sf::Vector2f{3.f, 1.f}, sf::Vector2f{1.f, 1.f}},
        sf::Vector2f{2.f, 1.f}
    },
    LineCollisionTestParameters{
        LineDescription{sf::Vector2f{1.f, 1.f}, sf::Vector2f{3.f, 3.f}},
        LineDescription{sf::Vector2f{1.f, 3.f}, sf::Vector2f{3.f, 1.f}},
        sf::Vector2f{2.f, 2.f}
    }
    // LineCollisionTestParameters{
    //     LineDescription{sf::Vector2f{0.f, 0.f}, sf::Vector2f{0.f, 0.f}},
    //     LineDescription{sf::Vector2f{0.f, 0.f}, sf::Vector2f{0.f, 0.f}},
    //     sf::Vector2f{0.f, 0.f}
    // },
    // LineCollisionTestParameters{
    //     LineDescription{sf::Vector2f{0.f, 0.f}, sf::Vector2f{0.f, 0.f}},
    //     LineDescription{sf::Vector2f{0.f, 0.f}, sf::Vector2f{0.f, 0.f}},
    //     sf::Vector2f{0.f, 0.f}
    // }
));
}  // physics
