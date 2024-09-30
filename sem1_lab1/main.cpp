#include <iostream>
#include "classes/GraphAdjMatrix.h"
#include "classes/Story.h"
using namespace std;

int main() {
    // Створюємо персонажів
    Character hero("John", "City", Role::Protagonist);
    Character villain("Dark Lord", "Mountain", Role::Antagonist);
    Character ally("Sarah", "Village", Role::Supporting);

    // Додаємо навички персонажам
    hero.add_skill("Fighting");
    hero.add_skill("Strategy");
    villain.add_skill("Magic");
    ally.add_skill("Healing");

    // Додаємо відносини між персонажами
    hero.add_relationships(ally, "Friend");
    villain.add_relationships(hero, "Enemy");

    // Створюємо локації
    Location world_map;
    world_map.add_loc_with_skills("City", {});
    world_map.add_loc_with_skills("Village", {});
    world_map.add_loc_with_skills("Mountain", {"Magic"});

    // Створюємо перевірку реальності
    RealityCheck reality_check;

    // Переміщуємо персонажа між локаціями
    hero.change_location(world_map, "Village", reality_check);
    villain.change_location(world_map, "City", reality_check);

    // Створюємо події
    Event battle("Final Battle", world_map, 10, 2, {"Fighting", "Strategy"});
    Event negotiation("Peace Talk", world_map, 12, 1, {"Strategy"});

    // Додаємо персонажів до подій
    battle.add_participants(&hero, reality_check);
    battle.add_participants(&villain, reality_check);
    negotiation.add_participants(&hero, reality_check);
    negotiation.add_participants(&ally, reality_check);

    // Генеруємо звіти
    cout << ReportGenerator::generate_character_report(hero);
    cout << ReportGenerator::generate_character_report(villain);
    cout << ReportGenerator::generate_event_report(battle);
    cout << ReportGenerator::generate_event_report(negotiation);
    cout << ReportGenerator::generate_location_report(world_map);

    return 0;
}


