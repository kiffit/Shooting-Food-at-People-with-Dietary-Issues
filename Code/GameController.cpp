// #include "GameController.h"
// #include <algorithm>
//
// void GameController::updateList(std::vector<std::shared_ptr<Entity> > &list, sf::Time &elapsed) {
//     // Run updates first
//     for (const auto &entity: list) {
//         entity->update(elapsed, *this);
//     }
//
//     // Remove dead ones after update pass
//     list.erase(
//         std::remove_if(list.begin(), list.end(),
//                        [](const std::shared_ptr<Entity> &e) {
//                            if (e->get_health() <= 0) {
//                                e->onDie();
//                                return true;
//                            }
//                            return false;
//                        }),
//         list.end());
// }
//
// void GameController::processCollisions() const {
//     // Calculate collisions
//     for (const auto &zombie: zombies_back) {
//         // Calculate projectile collisions first
//         for (const auto &projectile: projectiles_back) {
//             if (zombie->get_hitbox().findIntersection(projectile->get_hitbox()))
//                 projectile->onCollision(*zombie);
//         }
//
//         // Calculate plant-zombie collisions now, plants have advantage
//         for (const auto &plant: plants_back) {
//             if (zombie->get_hitbox().findIntersection(plant->get_hitbox())) {
//                 plant->onCollision(*zombie);
//                 zombie->onCollision(*plant);
//             }
//         }
//     }
// }
//
// void GameController::update(sf::Time &elapsed) {
//     // Process collisions first!
//     processCollisions();
//
//     // Update plants, zombies, and projectiles step, will delete all dead entities
//     updateList(plants_back, elapsed);
//     updateList(zombies_back, elapsed);
//     updateList(projectiles_back, elapsed);
//
//     // Swap buffers, necessary for avoiding race conditions and segfaults between the controller and window
//     swapBuffers();
// }
//
// void GameController::swapBuffers() {
//     std::scoped_lock lock(mutex_lock);
//     plants_front = plants_back;
//     zombies_front = zombies_back;
//     projectiles_front = projectiles_back;
// }
//
// void GameController::cleanup() {
//     std::scoped_lock lock(mutex_lock);
//     plants_front.clear();
//     plants_back.clear();
//     zombies_front.clear();
//     zombies_back.clear();
//     projectiles_front.clear();
//     projectiles_back.clear();
// }
