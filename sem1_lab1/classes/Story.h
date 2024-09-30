#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "GraphAdjList.h"
#include <algorithm>
using namespace std;

//-------------Classes for the Story---------------

enum class Role
{
    Antagonist,
    Protagonist,
    Supporting
};

class Location;
class RealityCheck;

class Character
{
    protected:
    string name;
    string location;
    Role role;
    vector <string> skills; //skills allow Character get to Location
    map <string, string> relationships; //name - relationship. Used for teaching another character a skill

    public:
    Character (string name, string location, Role role) : name(name), location(location), role(role) {}
    string get_name () const
       {
            return name;
       } 
    string get_location () const
       {
            return location;
       } 

    void change_location(Location& current_location, const string& destination, RealityCheck& reality_check);
    bool has_skill (const string& skill) const;
    void add_skill (string skill);
    void teach_skill (const string& skill, Character& character1); //allows a character to teach another character a skill (if they are not enemies)
    void add_relationships (Character& character1, const string& relationship);
    void print_character_info();
};

void Character:: print_character_info()
{
    cout << "Charaster " << name << "\nCurrent location: " << location << "\n Has skills: ";
    if (skills.empty())
    {
        cout << "None \n";
    }
    else
    {
        for (const auto& skill : skills)
        {
            cout << skill << " ";
        }
    }
    cout << "\n Role: ";
    switch(role)
    {
         case Role::Protagonist:
            cout << "Protagonist";
            break;
        case Role::Antagonist:
            cout << "Antagonist";
            break;
        case Role::Supporting:
            cout << "Supporting";
            break;
    }
    cout << "\n Relationships: ";
    if (relationships.empty())
    {
        cout << "None " << endl;
    }
    else
    {
        for (const auto& rel : relationships) {
            cout << rel.first << ": " << rel.second << ", ";
        }
    }
     cout << endl; 
}

bool Character:: has_skill (const string& skill) const
{
    return find(skills.begin(), skills.end(), skill) == skills.end();
}

void Character:: add_relationships (Character& character1, const std::string& relationship)
{
    if (relationships[character1.get_name()].empty())
    {
        relationships[character1.get_name()] = relationship;
        character1.relationships[this->get_name()] = relationship;
    }
    else
    {
        int answer;
        cout << "These two characters already have a relationship. Do you want to change the relationships between these characters?\n";
        cout << "Type in 0 if NO\n Type in 1 if YES" << endl;
        cin >> answer;
        
        if (answer != 0 and answer != 1)
        {
            cout << "Incorrect input. Please try again. " << endl;
        }
        if (answer)
        {
            relationships[character1.get_name()] = relationship;
            character1.relationships[this->get_name()] = relationship;
        }
    }
}

void Character:: change_location (Location& current_location, const std::string& destination, RealityCheck& reality_check)
{ 
    if (current_location.can_move_to(*this, location, destination) and reality_check.assign_location(*this, destination)) 
    {
        location = destination;
        cout << name << " moved to " << location << endl;
    }
}

void Character:: add_skill(string skill)
{
    if (!has_skill(skill))
        {
            skills.push_back(skill);
            cout << name << " learned the " << skill << " skill. " << endl;
        }
    else
        {
            cout << name << " already has the " << skill << " skill. " << endl;
        }
 }

void Character:: teach_skill (const string& skill, Character& character1)
{
    if (!has_skill(skill))
    {
        cout << name << " cannot teach this skill. They do not have the skill." << endl;
    }
    else if (relationships[character1.name] != "Enemy")
    {
        character1.add_skill(skill);
        cout << name << " teached " << character1.name << " " << skill << " skill." << endl;
    }
    else
    {
        cout << "Relationships between characters do not allow them to teach this skill" << endl;
    }
}


class Location : public GraphAdjList
{
    protected:
    string loc_name;
    map<string, vector<string>> required_skills; //write None if any skill is required

    public:
    string get_locname () const
    {
        return loc_name;
    }
    void add_loc_with_skills (const string& location, const vector<string>& required_skills);
    bool can_move_to (Character& character, const string& start, const string& destination);
    void print_map();
};
void Location:: print_map() 
{
        cout << "Current map:" << endl;
        print_graph(); // Use GraphAdjList to print the graph
}

void Location:: add_loc_with_skills(const string& location, const vector<string>& req_skills)
{
    add_vertex();
    required_skills[location] = req_skills;
}

bool Location:: can_move_to (Character& character, const string& start, const string& destination)
{
    //checking if path between start and destination exists
    int Distance = shortest_path(start, destination);
    if (Distance == -1)
    {
        cout << "No path exists between " << start << " and " << destination << "." << endl;
        return false;
    }

    //checking if character has required skills
    int ind = find_vertex_index(destination);
        if (ind == -1) 
        {
            cout << "Location not found!" << endl;
            return false;
        }

        auto it = required_skills.find(destination);
        if (it != required_skills.end()) 
        {
            for (const auto& skill : it -> second) 
            {
                if (!character.has_skill(skill)) 
                {
                    cout << "Character " << character.get_name() << " does not have the required skill: " << skill << " to move to " << destination << endl;
                    return false;
                }
            }
        }
        else
        {
            cout << "Destination " << destination << " not found in the skills map!" << endl;
            return false;
        }
        return true;
}

class Event
{
    private:
    string event_name;
    string description; // detailed description of the event
    vector <Character*> participants; //characters that partisipate in the event
    Location event_location;
    int time; //time when event occurs in hours (0-24)
    int duration; //of the event in hours
    vector<string> event_skills; // skills required to participate in the event

    public:
   Event(const string& event_name, const Location& loc, int time, int duration, vector<string> skill)
        : event_name(event_name), event_location(loc), time(time), duration(duration), event_skills(skill) {}
    int get_time () {return time;}
    int get_duration () {return duration;}
    void add_participants (Character* character, RealityCheck& reality_check);
};

void Event:: add_participants(Character* character, RealityCheck& reality_check)
{
        //reality check
    if (reality_check.assign_event(*character, *this)) 
    {
    //check if character has required skills
    for (const auto& skill : event_skills) 
    {
        if (!character -> has_skill(skill)) 
        {
            cout << character -> get_name() << " does not have the required skill: " << skill 
                << " to participate in " << event_name << "." << endl;
                return;
        }
    }
        participants.push_back(character);
        cout << character -> get_name() << " has been added to the event: " << event_name << endl;
    }
}

class RealityCheck
{
    private:
    map<string, string> character_locations;
    map<string, pair<Event*, int>> character_events; //name, event and event's end time

    public:
    bool assign_location(Character& character, const string& location_name);
    bool assign_event(Character& character, Event& event);

};

bool RealityCheck:: assign_event(Character& character, Event& event)
{
    int event_start_time = event.get_time();
    int event_end_time = event.get_time() + event.get_duration();
    if (character_events.find(character.get_name()) != character_events.end())
    {
        Event* current_event = character_events[character.get_name()].first;
        int current_event_end_time = character_events[character.get_name()].second;

        if (event_start_time < current_event_end_time)
        {
             cout << "Character " << character.get_name() << " is already in an event '" << current_event->get_time() 
                << ". They cannot join event " << event.get_time() << "' at this time." << endl;
             return false;
        }
    }
    character_events[character.get_name()] = {&event, event_end_time};
    cout << "Character " << character.get_name() << " has been assigned to event '" << event.get_time() << "'." << endl;
    return true;
}

bool RealityCheck:: assign_location (Character& character, const string& location_name)
{
    if (character_locations.find(character.get_name()) != character_locations.end()) 
    {
        cout << character.get_name() << " is already at another location." << endl;
        return false;
    }
    character_locations[character.get_name()] = location_name;
    return true;
}
