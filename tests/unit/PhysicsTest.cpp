#include "../../include/Physics/Physics.h"
#include "../../include/Environement/Carnivore.h"
#include "gtest/gtest.h"
#include <memory>

class PhysicsTest : public ::testing::Test {
  protected:
  Physics physics;
  float collisionDistance = 50.0f; // Example collision distance

  void SetUp() override {
    // Initialization code here
  }

  std::shared_ptr<Entity> CreateEntityAtPosition(float x, float y) {
    return std::make_shared<Carnivore>(
      Carnivore(Vector2(x, y), 0, 0, collisionDistance, 0));
  }
};

TEST_F(PhysicsTest, NoCollisionForDistantEntities) {
  std::shared_ptr<Entity> entity1 = CreateEntityAtPosition(100, 100);
  std::shared_ptr<Entity> entity2 = CreateEntityAtPosition(300, 300);
  std::vector<std::shared_ptr<Entity>> entities = {entity1, entity2};

  auto getCollidingEntities = physics.getCollidingEntities(entities);
  EXPECT_TRUE(getCollidingEntities.empty());
}

TEST_F(PhysicsTest, CollisionForCloseEntities) {
  std::shared_ptr<Entity> entity1 = CreateEntityAtPosition(110, 110);
  std::shared_ptr<Entity> entity2 =
    CreateEntityAtPosition(110, 110 + collisionDistance - 1);
  std::vector<std::shared_ptr<Entity>> entities = {entity1, entity2};

  auto getCollidingEntities = physics.getCollidingEntities(entities);
  EXPECT_FALSE(getCollidingEntities.empty());
  EXPECT_EQ(getCollidingEntities.size(), 1u);
  EXPECT_TRUE(getCollidingEntities.find(std::make_tuple(entity1, entity2)) !=
              getCollidingEntities.end());
}

TEST_F(PhysicsTest, CorrectNumberOfCollisions) {
  std::shared_ptr<Entity> entity1 = CreateEntityAtPosition(100, 100);
  std::shared_ptr<Entity> entity2 =
    CreateEntityAtPosition(100, 100 + collisionDistance / 2);
  std::shared_ptr<Entity> entity3 =
    CreateEntityAtPosition(100, 100 + collisionDistance * 3);
  std::vector<std::shared_ptr<Entity>> entities = {entity1, entity2, entity3};

  auto getCollidingEntities = physics.getCollidingEntities(entities);
  // Expecting entity1 and entity2 to be colliding
  // Not expecting entity3 to be colliding with either entity1 or entity2
  EXPECT_EQ(getCollidingEntities.size(), 1u);
}

TEST_F(PhysicsTest, MultipleCollisions) {
  auto entity1 = CreateEntityAtPosition(100, 100);
  auto entity2 = CreateEntityAtPosition(105, 105); // close to entity1
  auto entity3 = CreateEntityAtPosition(150, 150);
  auto entity4 = CreateEntityAtPosition(155, 155); // close to entity3
  std::vector<std::shared_ptr<Entity>> entities = {entity1, entity2, entity3,
                                                   entity4};
  auto collisions = physics.getCollidingEntities(entities);
  EXPECT_EQ(collisions.size(), 6u);
}

TEST_F(PhysicsTest, CollisionAtBoundary) {
  auto entity1 = CreateEntityAtPosition(100, 100);
  auto entity2 = CreateEntityAtPosition(100, 100 + collisionDistance +
                                               collisionDistance + 1);
  std::vector<std::shared_ptr<Entity>> entities = {entity1, entity2};
  auto collisions = physics.getCollidingEntities(entities);
  EXPECT_TRUE(collisions.empty());
}

TEST_F(PhysicsTest, CollisionJustInsideBoundary) {
  auto entity1 = CreateEntityAtPosition(100, 100);
  auto entity2 = CreateEntityAtPosition(100, 100 + collisionDistance +
                                               collisionDistance - 0.1f);
  std::vector<std::shared_ptr<Entity>> entities = {entity1, entity2};
  auto collisions = physics.getCollidingEntities(entities);
  EXPECT_FALSE(collisions.empty());
}

// Add more tests to cover edge cases, error conditions, and typical use cases.
