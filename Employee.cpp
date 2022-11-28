#include <iostream>
#include <assert.h>
#include "Skill.h"
#include "exceptions.h"
#include "Citizen.h"
#include "Employee.h"
#include <iostream>
#include <set>


using std::string;
using std::ifstream;
using std::ofstream;
using std::cerr;
using std::cout;
using std::endl;
using std::pair;
using std::set;


namespace mtm
{
    Employee::Employee(int new_id, string new_first_name, string new_last_name, int new_birth_year) :
        Citizen(new_id, new_first_name, new_last_name, new_birth_year) , salary(0), score(0), skill_set(){
    }

    int Employee::getSalary() const
    {
        return salary;
    }

    int Employee::getScore() const
    {
        return score;
    }

    void Employee::learnSkill(const Skill skill)
    {   
        if(hasSkill(skill.getId()) == true)
        {
            throw SkillAlreadyLearned();
        }
        if(score < skill.getRequiredPoints())
        {
            throw CanNotLearnSkill();
        }
        skill_set.insert(skill);
    }

    void Employee::forgetSkill(const int skill_id)
    {
        for(set<Skill>::iterator it = skill_set.begin(); it!=skill_set.end(); ++it)
        {
            if(it->getId() == skill_id)
            {
                skill_set.erase(it);
                return;
            }
        }
        throw DidNotLearnSkill();
    }

    bool Employee::hasSkill(const int id) const
    {   
        if(skill_set.empty())
        {
            return false;
        }
        Skill temp = Skill(id, "name" , 0);
        set<Skill>::iterator it;
        it = skill_set.find(temp);
        if(it == skill_set.end())
        {
            return false;
        }
        return true;
    }

    void Employee::setSalary(const int new_salary)
    {
        if(new_salary + salary < 0)
        {
            salary = 0;
        }
        salary += new_salary;

        if(salary<0)
        {
            salary=0;
        }
    }

    void Employee::setScore(const int new_score)
    {
        if(score + new_score < 0)
        {
            score = 0;
        }
        else
        {
        score += new_score;
        }
    }

    ostream& Employee::printShort(ostream& stream) const
    {
        return stream << this->getFirstName() << " "<<this->getLastName() << "\n"
                        << "Salary: " << this->getSalary() << " Score: "<< this->getScore() <<endl;
    }

    ostream& Employee::printLong(ostream& stream) const 
    {
        stream << this->getFirstName() << " " << this->getLastName()
                        <<"\n" << "id - "<< this->getId() << " "<< "birth_year - " <<this->getBirthYear()<< endl
                        << "Salary: "<< this->getSalary() << " Score: " << this->getScore();
        set<Skill>::iterator it;
        it = skill_set.begin();
        if(it!= skill_set.end())
        {
            stream << " Skills: " << endl;

            while (it != skill_set.end())
            {
                stream << it->getName() << endl;
                ++it;
            }
        }
        else
        {
            stream << endl;
        }
        return stream;
    }
    
    bool Employee::canLearnSkills() const 
    {
        return true;
    }

    Employee* Employee::clone() const
    {   
        return new Employee(*this);
    }
}
