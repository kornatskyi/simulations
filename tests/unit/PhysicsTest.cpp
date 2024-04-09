#include "../../include/Physics.h"
#include "../../include/Entity.h"
#include "gtest/gtest.h"

class PhysicsTest : public ::testing::Test {
  protected:
  Physics physics;
  float collisionDistance = 50.0f; // Example collision distance

  void SetUp() override {
    // Initialization code here
  }

  Entity CreateEntityAtPosition(float x, float y) {
    return Entity(Vector2(x, y), 0, 0, collisionDistance);
  }
};

TEST_F(PhysicsTest, NoCollisionForDistantEntities) {
  Entity entity1 = CreateEntityAtPosition(100, 100);
  Entity entity2 = CreateEntityAtPosition(300, 300);
  std::vector<Entity> entities = {entity1, entity2};

  auto collidingEntities = physics.collidingEntities(entities);
  EXPECT_TRUE(collidingEntities.empty());
}

TEST_F(PhysicsTest, CollisionForCloseEntities) {
  Entity entity1 = CreateEntityAtPosition(110, 110);
  Entity entity2 = CreateEntityAtPosition(110, 110 + collisionDistance - 1);
  std::vector<Entity> entities = {entity1, entity2};

  auto collidingEntities = physics.collidingEntities(entities);
  EXPECT_FALSE(collidingEntities.empty());
  EXPECT_EQ(collidingEntities.size(), 1u);
  EXPECT_EQ(collidingEntities.front(), std::make_tuple(entity1, entity2));
}

TEST_F(PhysicsTest, CorrectNumberOfCollisions) {
  Entity entity1 = CreateEntityAtPosition(100, 100);
  Entity entity2 = CreateEntityAtPosition(100, 100 + collisionDistance / 2);
  Entity entity3 =
    CreateEntityAtPosition(100, 100 + collisionDistance + collisionDistance);
  std::vector<Entity> entities = {entity1, entity2, entity3};

  auto collidingEntities = physics.collidingEntities(entities);
  // Expecting entity1 and entity2 to be colliding
  // Not expecting entity3 to be colliding with either entity1 or entity2
  EXPECT_EQ(collidingEntities.size(), 1u);
}

// Add more tests to cover edge cases, error conditions, and typical use cases.
