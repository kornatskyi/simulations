#include "../../include/Entity.h"
#include "gtest/gtest.h"

TEST(EntityTest, Initialization) {
  Entity entity(Vector2(100, 100), 50, 90);
  EXPECT_EQ(entity.position.x, 100);
  EXPECT_EQ(entity.position.y, 100);
  // More assertions...
}
