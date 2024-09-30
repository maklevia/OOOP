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

    void change_location (string newlocation);
    bool has_skill (string skill);
    void add_skill (string skill);
    void teach_skill (string skill, Character chatacter1); //allows a character to teach another character a skill (if they are not enemies)
    void add_relationships (Character character1, string relationship);
    void print_character_info();
};

bool Character:: has_skill (string skill)
{
    if (find(skills.begin(), skills.end(), skill) == skills.end())
    {
        return false;
    }
    else 
    {
        return true;
    }
}

void Character:: add_relationships (Character character1, string relationship)
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
        if (answer != 0 and answer != 1)
        {
            cout << "Incorrect input. Please try again. " << endl;
        }
        if (answer)
            relationships[character1.get_name()] = relationship;
    }
}

void Character:: change_location (string newlocation)
{ 
    if (loc.can_access(*this)) //111111
    {
        location = newlocation;
        cout << name << " moved to " << location << endl;
    }
    else
    {
        cout << name << " cannot move to " << location << "! They do not have requred skills." << endl;
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

void Character:: teach_skill (string skill, Character character1)
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
    vector <string> requrid_skills; //write None if any skill is required
    public:
    bool can_access(Character character);
};

