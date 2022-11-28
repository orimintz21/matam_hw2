#include <iostream>
#include <assert.h>
#include "Skill.h"
#include "exceptions.h"

using std::string;
using std::ifstream;
using std::ofstream;
using std::cerr;
using std::endl;

namespace mtm
{
    Skill::Skill(int new_id, string new_name, int new_skill_points) :
        id(new_id), name(new_name), skill_points(new_skill_points){

    }

    int Skill::getId() const
    {
        return id;
    }

    string Skill::getName() const
    {
        string temp = name;
        return temp;
    }

    int Skill::getRequiredPoints() const
    {
        return skill_points;
    }

    Skill& Skill::operator+=(const int added_skill_points)
    {
        if(added_skill_points < 0)
        {
            throw NegativePoints();
        }    
        skill_points+=added_skill_points;
        return *this;
    }

    Skill Skill::operator++(int){
        Skill temp(id, name, skill_points);
        skill_points++;
        return temp;
    }

    bool operator==(const Skill& skill1, const Skill& skill2)
    {
        return skill1.getId() == skill2.getId();
    }

    bool operator!=(const Skill& skill1, const Skill& skill2)
    {
        return !(skill1 == skill2);
    }

    bool operator<(const Skill& skill1, const Skill& skill2)
    {
        return skill1.getId() < skill2.getId();
    }

    bool operator>=(const Skill& skill1, const Skill& skill2)
    {
        return !(skill1 < skill2); 
    }

    bool operator>(const Skill& skill1, const Skill& skill2)
    {
        return skill2 < skill1;
    }

    bool operator<=(const Skill& skill1, const Skill& skill2)
    {
        return skill2 >= skill1;
    }

    ostream& operator<<(ostream& stream, const Skill& skill)
    {
        return stream << skill.getName()<< "\n";
    }

    Skill operator+(const Skill& skill, const int amount)
    {   
        if(amount<0)
        {
            throw NegativePoints();
        }
        
        Skill temp = skill;
        temp += amount;
        return temp;
    }
    
    Skill operator+(const int amount ,const Skill& skill)
    {

        return skill +amount;

    }

}