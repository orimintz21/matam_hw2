#include <iostream>
#include <assert.h>
#include "Skill.h"
#include "exceptions.h"
#include "Citizen.h"
#include "Employee.h"
#include "Manager.h"
#include <set>
#include "Workplace.h"

using std::string;
namespace mtm
{

    Workplace::Workplace(int new_id, string new_name, int new_employees_salary, int new_managers_salary) :
        id(new_id), name(new_name), employees_salary(new_employees_salary), managers_salary(new_managers_salary), manager_set(){
    }
        
    int Workplace::getId() const
    {
        return id;
    }

    string Workplace::getName() const
    {
        return name;
    }

    int Workplace::getWorkersSalary() const
    {
        return employees_salary;
    }

    int Workplace::getManagersSalary() const
    {
        return managers_salary;
    }

    void Workplace::hireManager(Citizen* new_manager)
    {
        Citizen* new_manager_ptr(new_manager);
        if (manager_set.empty()==false)
        {
            set<Citizen*>::iterator it = manager_set.find(new_manager_ptr);
            if(it != manager_set.end())
            {
                throw ManagerAlreadyHired();
            }
        }
        assert(new_manager->canLearnSkills() == false);
        if(new_manager->getSalary() > 0)
        {
            throw CanNotHireManager();
        }
        manager_set.insert(new_manager_ptr);
        new_manager_ptr->changeAllEmployeesSalary(employees_salary);
        new_manager->setSalary(managers_salary);
        return;
    }


    void Workplace::fireEmployee(const int employee_id, const int manager_id)
    {
        if(manager_set.empty())
         {
             throw ManagerIsNotHired();
         }
        set<Citizen*>::iterator it;
        for(it = manager_set.begin(); it != manager_set.end(); it++)
        {
            if((*it)->getId() == manager_id)
            {
                if(((*it)->hasEmployee(employee_id))==false)
                {
                    throw EmployeeIsNotHired();
                }
                Citizen* fired = (*it)->getEmployee(employee_id);
                fired->setSalary(-(employees_salary));
                (*it)->removeEmployee(employee_id);
                return;
            }
        }
        throw ManagerIsNotHired();
    }

    void Workplace::fireManager(const int manager_id)
    {
        if(manager_set.empty())
        {
            throw ManagerIsNotHired();
        }
        

        set<Citizen*>::iterator it;
        for(it = manager_set.begin(); it != manager_set.end(); it++)
        {
            if((*it)->getId() == manager_id)
            {
                (*it)->changeAllEmployeesSalary(-employees_salary);
                (*it)->setSalary(-(managers_salary));
                manager_set.erase(it);
                return;
            }
        }
        throw ManagerIsNotHired();
    }

    void Workplace::fireManagerAndEmployees(const int manager_id)
    {
        if(manager_set.empty())
         {
             throw ManagerIsNotHired();
         }
        set<Citizen*>::iterator it;
        for(it = manager_set.begin(); it != manager_set.end(); it++)
        {
            if((*it)->getId() == manager_id)
            {
                (*it)->removeAllEmployee(employees_salary);
                (*it)->setSalary(-(managers_salary));
                manager_set.erase(it);
                return;
            }
        }
        throw ManagerIsNotHired();
    }


    bool Workplace::hasEmployee(const int id) const
    {   
        if(manager_set.empty())
        {
            return false;
        }
        set<Citizen*>::iterator it;
        for(it = manager_set.begin(); it != manager_set.end(); it++)
        {
            if((*it)->hasEmployee(id))
            {
                return true;
            }
        }
        return false;
    }

    ostream& operator<<(ostream& stream, const Workplace& workplace)
    {
        stream << "Workplace name - " << workplace.getName();
        if(workplace.manager_set.empty())
        {   
            stream << endl;
            return stream;
        }
        stream << " Groups:"<<endl;
        set<Citizen*>::iterator it = workplace.manager_set.begin();
        while (it != workplace.manager_set.end())
        {
            stream << "Manager ";
            (*it)->printLong(stream);
            it++;
        }
        return stream;
    }

}
