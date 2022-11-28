#ifndef CITIZEN_H_
#define CITIZEN_H_

#include <ostream>
#include <memory>
#include "exceptions.h"
#include "Skill.h"

using std::string;
using std::istream;
using std::ostream;
using std::endl;
using std::shared_ptr;

namespace mtm
{
    class Citizen
    {
    private:
        int id;
        string first_name;
        string last_name;
        int birth_year;

    public:
        /**
         * @brief Construct a new Citizen object
         * 
         * @param new_id the citizen's id
         * @param new_first_name the citizen's first name
         * @param new_last_name the citizen's last name
         * @param new_birth_year the citizen's birth year
         */
        Citizen(int new_id, string new_first_name, string new_last_name, int new_birth_year);
        /**
         * @brief Copy Construct
         * 
         */
        Citizen(const Citizen&) = default;
        /**
         * @brief Destroy the Citizen object
         * 
         */
        virtual ~Citizen() = default;
        /**
         * @brief Get the Id object
         * 
         * @return int 
         */
        int getId() const;
        /**
         * @brief Get the First Name object
         * 
         * @return string 
         */
        string getFirstName() const;
        /**
         * @brief Get the Last Name object
         * 
         * @return string 
         */
        string getLastName() const;
        /**
         * @brief Get the Birth Year object
         * 
         * @return int 
         */
        int getBirthYear() const;
        /**
         * @brief Get the Salary object
         * 
         * @return int 
         */
        virtual int getSalary() const = 0;
        
        /**
         * @brief Get the Score object
         * 
         * @return int 
         */
        virtual int getScore() const;
        
        /**
         * @brief for polymorphisem
         * 
         */
        virtual void setSalary(const int new_salsry) = 0;
        /**
         * @brief Set the Score object
         * 
         * @param new_score 
         */
        virtual void setScore(const int new_score);
        /**
         * @brief prints the short massege
         * 
         * @param stream 
         * @return ostream& 
         */

        virtual bool canLearnSkills() const;
        /**
         * @brief retruns if the citizen has that skill, def is false
         * 
         * @param id 
         * @return true 
         * @return false 
         */
        virtual bool hasSkill(const int id) const;
        /**
         * @brief does nothing, for polimorphisem
         * 
         * @param skill_id 
         */
        virtual void forgetSkill(const int skill_id);
        /**
         * @brief does nothing, for polimorphisem
         * 
         * @param skill 
         */
        virtual void learnSkill(const Skill skill);
        /**
         * @brief for polymorphisem
         * 
         */
        virtual void removeAllEmployee(const int employee_salary);
        /**
         * @brief for polymorphisem
         * 
         * @param amount 
         */
        virtual void changeAllEmployeesSalary(const int amount);


        /**
         * @brief for polymorphisem
         * 
         *
         * 
         * @param new_employee 
         */
        virtual void addEmployee(Citizen* new_employee);

                /**
         * @brief for polymorphisem
         * 
         *
         * 
         * @param id 
         */
        virtual void removeEmployee(const int id);

        /**
         * @brief for polymorphisem
         * 
         *
         * 
         * @param id 
         */
        virtual bool hasEmployee(const int id) const;

                /**
         * @brief for polymorphisem
         * 
         *
         * 
         * @param id 
         */
        virtual Citizen* getEmployee(const int id) const;

        /**
         * @brief prints the short massege
         * 
         * @param stream 
         * @return ostream& 
         */
        virtual ostream& printShort(ostream& stream) const = 0;
        /**
         * @brief prints the long massege
         * 
         * @param stream 
         * @return ostream& 
         */
        virtual ostream& printLong(ostream& stream) const = 0;
        /**
         * @brief creat a cole
         * 
         * @return Citizen* 
         */
        virtual Citizen* clone() const = 0;            
    };
    //compres the id of the citizens
    bool operator==(const Citizen& citizen1, const Citizen& citizen2);
    bool operator!=(const Citizen& citizen1, const Citizen& citizen2);
    bool operator<(const Citizen& citizen1, const Citizen& citizen2);
    bool operator<=(const Citizen& citizen1, const Citizen& citizen2);
    bool operator>(const Citizen& citizen1, const Citizen& citizen2);
    bool operator>=(const Citizen& citizen1, const Citizen& citizen2);
    
    //a class for compering shared ptr citizens, copmers by ther id's
    class citizenComper
    {
        public:
            citizenComper() = default;
            ~citizenComper() = default;
            citizenComper(const citizenComper&) = default;
            bool operator() (const shared_ptr<Citizen> citizen1, const shared_ptr<Citizen> citizen2) const
            {
                return (*citizen1)<(*citizen2);
            }
    };

    //a class for compering citizens ptr, compers by ther id's
    class citizenComperRegularPtr
    {
        public:
            citizenComperRegularPtr() = default;
            ~citizenComperRegularPtr() = default;
            citizenComperRegularPtr(const citizenComperRegularPtr&) = default;
            
            bool operator() (const Citizen* citizen1, const Citizen* citizen2) const
            {
                return (*citizen1)<(*citizen2);
            }
    };
}
#endif  //CITIZEN_H_
