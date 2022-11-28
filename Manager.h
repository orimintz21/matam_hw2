#ifndef MANAGER_H_
#define MANAGER_H_

#include <ostream>
#include "exceptions.h"
#include "Citizen.h"
#include "Skill.h"
#include "Employee.h"
#include <memory>
#include <iostream>
#include <set>

using std::string;
using std::istream;
using std::cout;
using std::ostream;
using std::endl;
using std::set;
using std::shared_ptr;

namespace mtm
{

    class Manager: public Citizen
    {
    private:
        int salary;
        set<Citizen*, citizenComperRegularPtr> employee_set;

    public:
        /**
         * @brief Construct a new Manager object
         * 
         * @param new_id 
         * @param first_name 
         * @param last_name 
         * @param new_birth_year 
         */
        Manager(int new_id, string first_name, string last_name, int new_birth_year);
        /**
         * @brief Destroy the Manager object
         * 
         */
        ~Manager() = default;
        /**
         * @brief Copy constructor
         * 
         * @param manager 
         */
        Manager(const Manager& manager) = default;
        /**
         * @brief Get the Salary object
         * 
         * @return int 
         */
        int getSalary() const override;
        /**
         * @brief Set the Salary object
         * 
         * @param new_salary 
         */
        void setSalary(const int new_salary);
        
        /**
         * @brief remove all employees
         * 
         */
        void removeAllEmployee(const int employee_salary) override;

        void changeAllEmployeesSalary(const int amount) override;
        /**
         * @brief add the Employee to the set
         * 
         * @param new_employee 
         */
        void addEmployee(Citizen* new_employee) override;
        /**
         * @brief removes the Employee from the set
         * 
         * @param id 
         */
        void removeEmployee(const int id) override;
        /**
         * @brief check if the manager has that employee
         * 
         * @param id 
         * @return true 
         * @return false 
         */
        bool hasEmployee(const int id) const override;
        /**
         * @brief Get the Employee object from the set
         * 
         * @param id 
         * @return Employee 
         */
        Citizen* getEmployee(const int id) const override;
        /**
         * @brief prints the short masage
         * 
         * @param stream 
         * @return ostream& 
         */
        ostream& printShort(ostream& stream) const override;
        /**
         * @brief prints the long massage
         * 
         * @param stream 
         * @return ostream& 
         */
        ostream& printLong(ostream& stream) const override;
        /**
         * @brief creates a clone
         * 
         * @return Manager* 
         */
        Manager* clone() const override;
    


    };
}

#endif //MANAGER_H_