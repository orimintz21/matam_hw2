#ifndef WORKPLACE_H_
#define WORKPLACE_H_

#include <ostream>
#include "exceptions.h"
#include "Citizen.h"
#include "Skill.h"
#include "Employee.h"
#include "Manager.h"
#include <set>

using std::string;
using std::istream;
using std::ostream;
using std::endl;
using std::set;

namespace mtm
{
    class Workplace
    {
    private:
        int id;
        string name;
        int employees_salary;
        int managers_salary;
        set<Citizen*, citizenComperRegularPtr> manager_set;

    public:
        /**
         * @brief Construct a new Workplace object
         * 
         * @param id 
         * @param name 
         * @param employees_salary 
         * @param managers_salary 
         */
        Workplace(int id, string name, int employees_salary, int managers_salary);
        /**
         * @brief Destroy the Workplace object
         * 
         */
        ~Workplace() = default;
        /**
         * @brief Construct a new Workplace object
         * 
         * @param workplace 
         */
        Workplace(const Workplace& workplace) = default;
        /**
         * @brief hires the employee under the manager if he passes the condion
         * a tamplate function
         * 
         * @tparam condition 
         * @param new_employee 
         * @param manager_id 
         */
        template<class condition>
        void hireEmployee(const condition, Employee* new_employee, int manager_id);
        /**
         * @brief Get the workplace's Id
         * 
         * @return int 
         */
        int getId() const;
        /**
         * @brief Get the workplace's name
         * 
         * @return string 
         */
        string getName() const;
        /**
         * @brief Get the salary of the employees
         * 
         * @return int 
         */
        int getWorkersSalary() const;
        /**
         * @brief Get the salary of the managers
         * 
         * @return int 
         */
        int getManagersSalary() const;
        /**
         * @brief hire the manager and all the em
         * 
         * @param new_manager 
         */
        void hireManager(Citizen* new_manager);
        /**
         * @brief fires the employee
         * 
         * @param employee_id 
         * @param manager_id 
         */
        void fireEmployee(const int employee_id, const int manager_id);
        /**
         * @brief fires the manager and keeps the employees under him
         * 
         * @param manager_id 
         */
        void fireManager(const int manager_id);
        /**
         * @brief fires the manager and all the employees under him
         * 
         * @param manager_id 
         */
        void fireManagerAndEmployees(const int manager_id);
        /**
         * @brief finds if the employee works in the workpace
         * 
         * @param id 
         * @return true 
         * @return false 
         */
        bool hasEmployee(const int id) const;
        /**
         * @brief prints the format
         * 
         * @param stream 
         * @param workplace 
         * @return ostream& 
         */
        friend ostream& operator<<(ostream& stream, const Workplace& workplace);
    };

    template<class func>
    void Workplace::hireEmployee(func hiring_condition, Employee* new_employee, int manager_id)
    {
        if(!hiring_condition(new_employee))
        {
            throw EmployeeNotSelected();
        }
        
        set<Citizen*>::iterator it;
        for(it = manager_set.begin(); it != manager_set.end(); it++)
        {
            if((*it)->getId() == manager_id)
            {
                if((*it)->hasEmployee(new_employee->getId()))
                {
                    throw EmployeeAlreadyHired();
                }
                (*it)->addEmployee(new_employee);
                new_employee->setSalary(employees_salary);
                return;
            }
        }
        throw ManagerIsNotHired();
    }
}

#endif //WORKPLACE_H_