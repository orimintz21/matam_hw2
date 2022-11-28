#include <iostream>
#include "Citizen.h"
#include "Skill.h"

using std::string;
using std::ifstream;
using std::ofstream;
using std::cerr;
using std::endl;

namespace mtm
{
    Citizen::Citizen(int new_id, string new_first_name, string new_last_name, int new_birth_year) :
        id(new_id), first_name(new_first_name), last_name(new_last_name), birth_year(new_birth_year){
            
        }

    int Citizen::getId() const
    {
        return id;
    }
    string Citizen::getFirstName() const
    {
        return first_name;
    }

    bool Citizen::hasSkill(const int id) const
    {
        return false;
    }

    void Citizen::forgetSkill(const int skill_id)
    {
        return;
    }


    bool Citizen::canLearnSkills() const
    {
        return false;
    }

    string Citizen::getLastName() const
    {
        return last_name;
    }

    int Citizen::getBirthYear() const
    {
        return birth_year;
    }

    void Citizen::setScore(const int new_score)
    {
        return;
    }

    void Citizen::setSalary(const int new_score)
    {
        return;
    }
    
    void Citizen::removeAllEmployee(const int employee_salary)
    {
        return;
    }
    void Citizen::learnSkill(const Skill skill)
    {
        return;
    }

    void Citizen::changeAllEmployeesSalary(const int amount)
    {
        return;
    }


    void Citizen::addEmployee(Citizen* new_employee)
    {
        return;
    }

    void Citizen::removeEmployee(const int id) 
    {
        return;
    }

    bool Citizen::hasEmployee(const int id) const
    {
        return false;
    }

    int Citizen::getScore() const
    {
        return -1;
    }

    Citizen* Citizen::getEmployee(const int id) const
    {
        return NULL;
    }

    bool operator==(const Citizen& citizen1, const Citizen& citizen2)
    {
        return (citizen1.getId() == citizen2.getId());
    }

    bool operator!=(const Citizen& citizen1, const Citizen& citizen2)
    {
        return !(citizen1 == citizen2);
    }

    bool operator<(const Citizen& citizen1, const Citizen& citizen2)
    {
        return (citizen1.getId() < citizen2.getId());
    }

    bool operator>=(const Citizen& citizen1, const Citizen& citizen2)
    {
        return !(citizen1 < citizen2);
    }

    bool operator>(const Citizen& citizen1, const Citizen& citizen2)
    {
        return (citizen2 < citizen1);
    }

    bool operator<=(const Citizen& citizen1, const Citizen& citizen2)
    {
        return (citizen2 >= citizen1);
    }

}
