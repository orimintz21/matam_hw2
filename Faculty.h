#ifndef FACULTY_H_
#define FACULTY_H_

#include <ostream>
#include "exceptions.h"
#include "Citizen.h"
#include "Skill.h"
#include "Employee.h"
#include <set>
#include <functional> 

using std::string;
using std::istream;
using std::ostream;
using std::endl;
using std::set;
namespace mtm
{
    class Condition{
    public:
        virtual bool operator()(Employee* employee) =0;
    };

    template <typename Test>
    class Faculty
    {
    private: 
        int id;
        Skill course;
        int added_points;
        Test* function;
    public:

        /**
         * @brief Construct a new Faculty object
         * 
         * @param id faculty id's
         * @param course the skill the faculty teaches
         * @param added_points the number of points the fuculty adds to the students
         * @param new_condition the condiont to get into the faculty
         */
        explicit Faculty(int id, Skill course, int added_points, Test* new_condition);
        /**
         * @brief destructor
         * 
         */
        virtual ~Faculty() = default;
        /**
         * @brief Copy Constructor
         * 
         */
        Faculty(const Faculty&) = default;
        /**
         * @brief Get the Skill object
         * 
         * @return Skill - gets the skill the faculty teaches
         */
        Skill getSkill() const;
        /**
         * @brief Get the Id object
         * 
         * @return int - the facults id
         */
        int getId() const;
        /**
         * @brief Get the Added Points object
         * 
         * @return int - the number of points the faculty adds to it's students
         */
        int getAddedPoints() const;
        /**
         * @brief teach the student if s/he passes the condition 
         * 
         * @param student_ptr - a pointer to the student
         */
        void teach(Employee* student_ptr);


    };

    template <typename Test>
    Faculty<Test>::Faculty(int new_id, Skill new_course , int new_added_points, Test* new_condition) :
                id(new_id), course(new_course), added_points(new_added_points), function(new_condition){
                }


    template <typename Test>
    Skill Faculty<Test>::getSkill() const
    {
        return this->course;
    }

    template <typename Test>
    int Faculty<Test>::getId() const
    {
        return this->id;
    }

    template <typename Test>
    int Faculty<Test>::getAddedPoints() const
    {
        return this->added_points;
    }

    template <typename Test>
    void Faculty<Test>::teach(Employee* student_ptr)
    {
        if((*function)(student_ptr))
        {
            student_ptr->learnSkill(course);
            student_ptr->setScore(added_points);
        }
        else
        {
            throw EmployeeNotAccepted();
        }
    }


}


#endif //FACULTY_H_