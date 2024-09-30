#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

//-------------Classes for the Story---------------

enum class Role
{
    Antagonist,
    Protagonist,
    Supporting
};

class Location;

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

    void change_location(const Location& newlocation);
    bool has_skill (const string& skill) const;
    void add_skill (string skill);
    void teach_skill (const string& skill, Character& character1); //allows a character to teach another character a skill (if they are not enemies)
    void add_relationships (Character& character1, const string& relationship);
    bool can_access(Location loc);
    void print_character_info();
};

bool Character:: has_skill (const string& skill) const
{
    return find(skills.begin(), skills.end(), skill) == skills.end();
}

void Character:: add_relationships (Character& character1, const string& relationship)
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

void Character:: change_location(const Location& newlocation)
{ 
    if (newlocation.can_access(*this)) 
    {
        location = newlocation.get_locname();
        cout << name << " moved to " << location << endl;
    }
    else
    {
        cout << name << " cannot move to " << newlocation.get_locname() << "! They do not have the required skills." << endl;
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


class Location
{
    protected:
    string loc_name;
    vector <string> required_skills; //write None if any skill is required

    public:
    Location(string name, vector<string> skills) : loc_name(name), required_skills(skills) {}
    string get_locname () const
    {
        return loc_name;
    }
    bool can_access(const Character& character) const;
    
};

bool Location:: can_access (const Character& character) const
{
    for (const auto& skill : required_skills)
    {
        if (!character.has_skill(skill))
        {
            return false;
        }
    }
    return true;
}

