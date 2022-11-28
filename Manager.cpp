#include <iostream>
#include <assert.h>
#include "Skill.h"
#include "exceptions.h"
#include "Citizen.h"
#include "Employee.h"
#include "Manager.h"
#include <memory>
#include <iostream>

using std::cout;
using std::shared_ptr;
using std::string;

namespace mtm
{
    Manager::Manager(int new_id, string new_first_name, string new_last_name, int new_birth_year) :
        Citizen(new_id, new_first_name, new_last_name, new_birth_year) , salary(0), employee_set(){
    }

    int Manager::getSalary() const
    {
        return salary;
    }

    void Manager::setSalary(const int new_salary)
    {
        if(new_salary + salary < 0)
        {
            salary = 0;
        }
        else
        {
        salary += new_salary;
        }
    }

    Citizen* Manager::getEmployee(const int id) const
    {   
        if(!hasEmployee(id))
        {
            throw EmployeeIsNotHired();
        }
        set<Citizen*>::iterator it;

        for (it = employee_set.begin() ; it != employee_set.end() ; it++)
        {
            if((*it)->getId() == id)
            {
                break;
            }
        }
        return *it;
    }

    void Manager::changeAllEmployeesSalary(const int amount)
    {
        set<Citizen*>::iterator it = employee_set.begin();
        for(set<Citizen*>::iterator it = employee_set.begin(); it != employee_set.end(); it++)
        {
            (*it)->setSalary(amount);
        }
    }

    void Manager::removeAllEmployee(const int employee_salary)
    {
        set<Citizen*>::iterator it = employee_set.begin();
        while(it != employee_set.end())
        {
            (*it)->setSalary(-employee_salary);
            removeEmployee((*it)->getId());
            it = employee_set.begin();
        }
    }

    bool Manager::hasEmployee(const int id) const
    {
        if(employee_set.empty())
        {
             return false;
        }
        set<Citizen*>::iterator it;
        for ( it = employee_set.begin() ; it != employee_set.end() ; it++)
        {
            if((*it)->getId() == id)
            {
                return true;
            }
        }
        return false;
    }

    void Manager::addEmployee(Citizen* new_employee)
    {
        Citizen* shared_new_employee(new_employee);
        if(hasEmployee(shared_new_employee->getId()))
        {
            throw EmployeeAlreadyHired();
        }
        employee_set.insert(shared_new_employee);
    }

    void Manager::removeEmployee(const int id)
    {
        set<Citizen*>::iterator it;

        for (it = employee_set.begin() ; it != employee_set.end() ; it++)
        {
            if((*it)->getId() == id)
            {
                
                employee_set.erase(it);
                return;
            }
        }
        throw EmployeeIsNotHired();
    }

    ostream& Manager::printShort(ostream& stream) const
    {
        stream << this->getFirstName() << " " << this->getLastName() <<endl 
            <<"Salary: " << this->getSalary();
        return stream<<endl;
    }

    ostream& Manager::printLong(ostream& stream) const
    {
        stream << this->getFirstName() << " " << this->getLastName() << endl
                    << "id - "<< this->getId() << " birth_year - " <<this->getBirthYear()<< endl
                    <<"Salary: " << this->getSalary()<< endl;
        set<Citizen*>::iterator it;
        it = employee_set.begin();
        if(it != employee_set.end())
        {
            stream << "Employees: " << endl;
            while (it != employee_set.end())
            {
                (*it)->printShort(stream);
                ++it;
            }
        }

        return stream;
    }
    
    Manager* Manager::clone() const
    {   
        return new Manager(*this);
    }
}