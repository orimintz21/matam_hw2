#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

#include <ostream>
#include "exceptions.h"
#include "Citizen.h"
#include "Skill.h"
#include <iostream>
#include <set>


using std::string;
using std::istream;
using std::ostream;
using std::endl;
using std::set;

namespace mtm
{
    class Employee : public Citizen
    {
    private:
        
        int salary;
        int score;
        set<Skill> skill_set;
        
    public:
        /**
         * @brief Construct a new Employee object
         * 
         * @param new_id 
         * @param first_name 
         * @param last_name 
         * @param new_birth_year 
         */
        Employee(int new_id, string first_name, string last_name, int new_birth_year);
        /**
         * @brief Copy constructor
         * 
         * @param employee 
         */
        Employee(const Employee& employee) = default;
        /**
         * @brief Destroy the Employee object
         * 
         */
        ~Employee() = default;
        /**
         * @brief Get the Salary object
         * 
         * @return int 
         */
        int getSalary() const override;
        /**
         * @brief Get the Score object
         * 
         * @return int 
         */
        int getScore() const override;
        /**
         * @brief learn a new skill
         * 
         * @param skill 
         */
        void learnSkill(const Skill skill) override;
        /**
         * @brief forgets the skill
         * 
         * @param skill 
         */
        void forgetSkill(const int skill_id) override;
        /**
         * @brief checks if the employee has that skill
         * 
         * @param id 
         * @return true 
         * @return false 
         */
        bool hasSkill(const int id) const override;
        /**
         * @brief checks if the employee can learn skill, return true
         * 
         * @return true 
         * @return false 
         */
        bool canLearnSkills() const override;
        /**
         * @brief Set the Salary object
         * 
         * @param new_salsry 
         */
        void setSalary(const int new_salsry) override;
        /**
         * @brief Set the Score object
         * 
         * @param new_score 
         */
        void setScore(const int new_score) override;
        /**
         * @brief prints the short massege
         * 
         * @param stream 
         * @return ostream& 
         */
        ostream& printShort(ostream& stream) const override;
        /**
         * @brief prints the long massege
         * 
         * @param stream 
         * @return ostream& 
         */
        ostream& printLong(ostream& stream) const override;
        /**
         * @brief creats a clone
         * 
         * @return Employee* 
         */
        Employee* clone() const override;
        

    }; 
}
#endif