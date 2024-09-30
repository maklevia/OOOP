#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "classes/doctest.h"
#include "classes/GraphAdjMatrix.h"
#include "classes/Story.h"

TEST_CASE ("Testing Character") 
{
    Character protagonist("Mariia", "Room", Role::Protagonist);

    SUBCASE("Test Get Name") 
    {
        CHECK(protagonist.get_name() == "Mariia");
    }

    SUBCASE("Test Add Skill") 
    {
        protagonist.add_skill("Sleep");
        CHECK(protagonist.has_skill("Sleep") == true);
    }

    SUBCASE("Test Teach Skill") 
    {
        Character learner("Sonia", "City", Role::Supporting);
        protagonist.add_skill("Sleep");
        protagonist.teach_skill("Sleep", learner);
        CHECK(learner.has_skill("Sleep") == true);
    }

    SUBCASE("Test Add Relationship") 
    {
        Character antagonist("Deadline", "Somewhere", Role::Antagonist);
        protagonist.add_relationships(antagonist, "Enemy");
        CHECK(protagonist.get_relationships().at("Deadline") == "Enemy");
    }
}

TEST_CASE("Testing Event") 
{
    Location location;
    vector<string> skills{"Sleep", "Eat"};
    Event battle("Battle", location, 10, 2, skills);

    SUBCASE("Test Get Event Name") 
    {
        CHECK(battle.get_event_name() == "Battle");
    }

    SUBCASE("Test Add Participant") 
    {
        Character charachter("Mariia", "Room", Role::Protagonist);
        RealityCheck check;
        battle.add_participants(&charachter, check);
        CHECK(battle.get_event_name() == "Battle");
    }
}