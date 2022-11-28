#include <ostream>
#include "exceptions.h"
#include "Citizen.h"
#include "Skill.h"
#include "Manager.h"
#include "Employee.h"
#include "Workplace.h"
#include "Faculty.h"
#include "City.h"
#include <set>
#include <memory>
#include <functional> 
#include <assert.h>

using std::string;
using std::istream;
using std::ostream;
using std::endl;
using std::set;
using std::shared_ptr;
using std::dynamic_pointer_cast;

namespace mtm
{
    
    City::City(string new_name) :
        name(new_name), population(), faculties(), workplaces(){
    }

    void City::addEmployee(int new_id, string first_name, string last_name, int new_birth_year)
    {
        if(findIfTheCitizenExists(new_id))
        {
            throw  CitizenAlreadyExists();
        }
        shared_ptr<Employee> employee (new Employee(new_id, first_name, last_name, new_birth_year));
        
        population.insert(employee);
        return;
    }

    bool City::findIfTheCitizenExists(int id)
    {
        set<shared_ptr<Citizen>>::iterator it;
        for(it = population.begin(); it!= population.end(); it++)
        {
            if((*it)->getId() == id)
            {
                return true;
            }
        }
        return false;
    }

    bool City::findIfTheWorkplaceExists(int id)
    {
        set<shared_ptr<Workplace>>::iterator it;
        for(it = workplaces.begin(); it!= workplaces.end(); it++)
        {
            if((*it)->getId() == id)
            {
                return true;
            }
        }
        return false;
    }

    bool City::findIfTheFacultyExists(int id)
    {
        set<shared_ptr<Faculty<Condition>>>::iterator it;
        for(it = faculties.begin(); it != faculties.end(); it++)
        {
            if((*it)->getId() == id)
            {
                return true;
            }
        }
        return false;
    }


    void City::addManager(int new_id, string first_name, string last_name, int new_birth_year)
    {
        if(findIfTheCitizenExists(new_id))
        {
            throw CitizenAlreadyExists();
        }

        shared_ptr<Manager> manager (new Manager(new_id, first_name, last_name, new_birth_year));
        population.insert(manager);
        return;
    }
    
    
    void City::addFaculty(int new_id,  Skill new_course, int new_added_points, Condition* condition)
    {
        if(findIfTheFacultyExists(new_id))
        {
            throw FacultyAlreadyExists();
        }

        shared_ptr<Faculty<Condition>> faculty (new Faculty<Condition>(new_id, new_course, new_added_points, condition));
        faculties.insert(faculty);
        return;
    }

    void City::createWorkplace(int new_id, string name, const int employee_salary, const int manager_salary)
    {
        if(findIfTheWorkplaceExists(new_id))
        {
            throw WorkplaceAlreadyExists();
        }

        shared_ptr<Workplace> workplace (new Workplace(new_id, name, employee_salary, manager_salary));
        workplaces.insert(workplace);
        return;
    }

    void City::teachAtFaculty(int employee_id, int faculty_id)
    {   
        shared_ptr<Citizen> employee_shared_ptr = NULL;
        set<shared_ptr<Citizen>>::iterator it;
        for(it = population.begin(); it != population.end(); it++)
        {
            if((*it)->getId() == employee_id)
            {
                employee_shared_ptr = *it;
            }
        }
        if(employee_shared_ptr == NULL)
        {
            throw EmployeeDoesNotExist();
        }
        if(employee_shared_ptr->canLearnSkills() == false)
        {
            throw EmployeeDoesNotExist();
        }

        shared_ptr<Faculty<Condition>> faculty_ptr = getFaculty(faculty_id);
        Employee* employee_ptr = dynamic_cast<Employee*>(&(*employee_shared_ptr));


        faculty_ptr->teach(employee_ptr);
    }

    void City::hireManagerAtWorkplace(const int manager_id, const int workplace_id)
    {
        shared_ptr<Citizen> manager_ptr;
        try
        {
            manager_ptr = getCitizen(manager_id);
        }
        catch(CitizenDoesNotExists&)
        {
            throw ManagerDoesNotExist();
        }
        
        if(manager_ptr->canLearnSkills() != false)
        {
            throw ManagerDoesNotExist();
        }

        shared_ptr<Workplace> workplace_ptr = getWorkplace(workplace_id);

        workplace_ptr->hireManager(&(*manager_ptr));
        
        return;
    }



    void City::fireEmployeeAtWorkplace(const int employee_id, const int manager_id, const int workplace_id)
    {
        if(findIfTheCitizenExists(employee_id) == false)
        {
            throw EmployeeDoesNotExist();
        }
        shared_ptr<Citizen> employee_ptr = getCitizen(employee_id);
        if(employee_ptr->canLearnSkills() == false)
        {
            throw EmployeeDoesNotExist();
        }

        if(findIfTheCitizenExists(manager_id) == false)
        {
            throw ManagerDoesNotExist();
        }
        shared_ptr<Citizen> manager_ptr = getCitizen(manager_id);
        if(manager_ptr->canLearnSkills() == true)
        {
            throw EmployeeDoesNotExist();
        }
        
        if(workplaces.empty())
        {
            throw WorkplaceDoesNotExist();
        }


        set<shared_ptr<Workplace>>::iterator it;
        for(it = workplaces.begin(); it != workplaces.end() ; ++it)
        {
            if((*it)->getId() == workplace_id)
            {   
                try
                {
                (*it)->fireEmployee(employee_id, manager_id);
                }
                catch(EmployeeIsNotHired&)
                {
                    throw EmployeeDoesNotExist();
                }
                return;
            }
        }

        throw WorkplaceDoesNotExist();
        return;
    }

     void City::fireManagerAtWorkplace(const int manager_id, const int workplace_id)
     {
        if(workplaces.empty())
        {
            throw WorkplaceDoesNotExist();
        }
        set<shared_ptr<Workplace>>::iterator it;
        
        for(it = workplaces.begin(); it != workplaces.end() ; ++it)
        {
            if((*it)->getId() == workplace_id)
            {
                try
                {
                    (*it)->fireManagerAndEmployees(manager_id);
                }
                catch(ManagerIsNotHired&)
                {
                    throw ManagerDoesNotExist();
                }
                return;
            }
        }

        throw WorkplaceDoesNotExist();
        return;
     }

    int City::getAllAboveSalary(ostream& stream , const int salary)
    {   
        int count = 0;
        set<shared_ptr<Citizen>>::iterator it;
        for(it = population.begin(); it != population.end(); ++it)
        {
            if((*it)->getSalary() >= salary)
            {
                count++;
                (*it)->printShort(stream);
            }
        }
        return count;
    }

    bool City::isWorkingInTheSameWorkplace(const int employee_id1, const int employee_id2)
    {   
        if(workplaces.empty())
        {
            throw EmployeeDoesNotExist();   
        }

        if(findIfTheCitizenExists(employee_id1) && findIfTheCitizenExists(employee_id2))
        {
            shared_ptr<Citizen> employee_ptr1 = getCitizen(employee_id1);
            if(employee_ptr1->canLearnSkills() == false)
            {
                throw EmployeeDoesNotExist();   
            }
            
            shared_ptr<Citizen> employee_ptr2 = getCitizen(employee_id2);
            if(employee_ptr2->canLearnSkills() == false)
            {
                throw EmployeeDoesNotExist();   
            }
        }
        else
        {
            throw EmployeeDoesNotExist();
        }

        set<shared_ptr<Workplace>>::iterator it;
        for(it = workplaces.begin(); it != workplaces.end(); ++it)
        {
            if((*it)->hasEmployee(employee_id1))
            {
                if((*it)->hasEmployee(employee_id2))
                {
                    return true;
                }
                return false;
            }            
        }
        return false;

    }

    ostream& City::printAllEmployeesWithSkill(ostream& stream, const int id)
    {
        set<shared_ptr<Citizen>>::iterator it;
        for(it = population.begin(); it!= population.end(); ++it)
        {
            if((*it)->hasSkill(id))
            {
                (*it)->printShort(stream);
            }
        }
        return stream;
    }

    shared_ptr<Citizen> City::getCitizen(const int id)
    {
        set<shared_ptr<Citizen>>::iterator it;
        for(it = population.begin(); it != population.end(); it++)
        {
            if((*it)->getId() == id)
            {
                return *it;
            }
        }

        throw CitizenDoesNotExists();
    }

    shared_ptr<Faculty<Condition>> City::getFaculty(const int id)
    {
        set<shared_ptr<Faculty<Condition>>>::iterator it;
        for(it = faculties.begin(); it != faculties.end(); it++)
        {
            if((*it)->getId() == id)
            {
                return *it;
            }
        }

        throw FacultyDoesNotExist();
    }

    shared_ptr<Workplace> City::getWorkplace(const int id)
    {
        set<shared_ptr<Workplace>>::iterator it;
        for(it = workplaces.begin(); it != workplaces.end(); it++)
        {
            if((*it)->getId() == id)
            {
                return *it;
            }
        }
        throw WorkplaceDoesNotExist();
    }    
}
