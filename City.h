#ifndef CITY_H_
#define CITY_H_

#include <ostream>
#include "exceptions.h"
#include "Citizen.h"
#include "Skill.h"
#include "Manager.h"
#include "Employee.h"
#include "Workplace.h"
#include "Faculty.h"
#include <set>
#include <memory>
#include <functional> 

using std::string;
using std::istream;
using std::ostream;
using std::endl;
using std::set;
using std::shared_ptr;
using std::dynamic_pointer_cast;


namespace mtm
{
    class City 
    {
    private:
        string name;
        set<shared_ptr<Citizen>, citizenComper> population;
        set<shared_ptr<Faculty<Condition>>> faculties;
        set<shared_ptr<Workplace>> workplaces;
    public:
        /**
         * @brief Construct a new City object
         * 
         * @param new_name the city's name
         */
        City(string new_name);
        /**
         * @brief Destroy the City object
         * 
         */
        ~City()=default;
        /**
         * @brief Construct a new City object
         * 
         * @param city 
         */
        City(City& city) = default;
        /**
         * @brief adds an employee to the city
         * 
         * @param new_id 
         * @param first_name 
         * @param last_name 
         * @param new_birth_year 
         */
        void addEmployee(int new_id, string first_name, string last_name, int new_birth_year);
        /**
         * @brief adds a manger to the city
         * 
         * @param new_id 
         * @param first_name 
         * @param last_name 
         * @param new_birth_year 
         */
        void addManager(int new_id, string first_name, string last_name, int new_birth_year);
        /**
         * @brief adds the faculty to the city
         * 
         * @param new_id 
         * @param new_course 
         * @param new_added_points 
         * @param condition 
         */
        void addFaculty(int new_id , Skill new_course , int new_added_points , Condition* condition);
        /**
         * @brief adds the workplace to the city
         * 
         * @param new_id 
         * @param name 
         * @param employee_salary 
         * @param manager_salary 
         */
        void createWorkplace(int new_id, string name, int employee_salary, int manager_salary);

        /**
         * @brief teachs the employee the faculy's skill
         * 
         * @param employee_id 
         * @param faculty_id 
         */
        void teachAtFaculty(int employee_id, int faculty_id);

        /**
         * @brief find if the citizen is in the popultion set
         * 
         * @param id 
         * @return true 
         * @return false 
         */
        bool findIfTheCitizenExists(int id);

        /**
         * @brief Get the Citizen from the population set
         * 
         * @param id 
         * @return Citizen* 
         */
        shared_ptr<Citizen> getCitizen(const int id);

        /**
         * @brief gets the faculty from the set
         * 
         * @param id 
         * @return Faculty<Condition>* 
         */
        shared_ptr<Faculty<Condition>> getFaculty(const int id);

        /**
         * @brief Get the Workplace object from the set
         * 
         * @param id 
         * @return Workplace* 
         */
        shared_ptr<Workplace> getWorkplace(const int id);

        /**
         * @brief find if the workpace exists in the city
         * 
         * @param id 
         * @return true 
         * @return false 
         */
        bool findIfTheWorkplaceExists(int id);

        /**
         * @brief find if the faculty exists in the city
         * 
         * @param id 
         * @return true 
         * @return false 
         */
        bool findIfTheFacultyExists(int id);
    
        
        /**
         * @brief  hire the employee under the manager in the workplace 
         * 
         * @param hire_condition 
         * @param employee_id 
         * @param manager_id 
         * @param workplace_id 
         */
        template <class function>
        void hireEmployeeAtWorkplace(function hire_condition, const int employee_id, const int manager_id, const int workplace_id);

        /**
         * @brief hires the manager
         * 
         * @param manager_id 
         * @param workplace_id 
         */
        void hireManagerAtWorkplace(const int manager_id, const int workplace_id);

        /**
         * @brief fire the employee from the workplace
         * 
         * @param employee_id 
         * @param manager_id 
         * @param workplace_id 
         */
        void fireEmployeeAtWorkplace(const int employee_id, const int manager_id, const int workplace_id);

        /**
         * @brief fire the manager from the workplce
         * 
         * @param manager_id 
         * @param workplace_id 
         */
        void fireManagerAtWorkplace(const int manager_id, const int workplace_id);

        /**
         * @brief prints every citizen that earns more then slalary
         * 
         * @param stream 
         * @param salary 
         * @return number of citizens with salary above salary
         */
        int getAllAboveSalary(ostream& stream , const int salary);

        /**
         * @brief cheacks if the employees are working in the same workplace
         * 
         * @param employee_id1 
         * @param employee_id2 
         * @return true 
         * @return false 
         */
        bool isWorkingInTheSameWorkplace(const int employee_id1, const int employee_id2);

        /**
         * @brief prints all the employees in the city that have that skill
         * 
         * @param stream 
         * @param id 
         * @return ostream& 
         */
        ostream& printAllEmployeesWithSkill(ostream& stream , const int id);

    };

    template <class function>
    void City::hireEmployeeAtWorkplace(function hire_condition, const int employee_id, const int manager_id, const int workplace_id)
    {
        shared_ptr<Citizen> employee_ptr;
        try
        {
            employee_ptr = getCitizen(employee_id);
        }
        catch(CitizenDoesNotExists&)
        {
            throw EmployeeDoesNotExist();
        }
        if(employee_ptr->canLearnSkills() == false)
        {
            throw EmployeeDoesNotExist();
        }

        if(findIfTheCitizenExists(manager_id) == true)
        {
             shared_ptr<Citizen> manager_ptr = getCitizen(manager_id);
            if (manager_ptr->canLearnSkills() == true)
            {
                throw ManagerDoesNotExist();
            }
            
        }
        else
        {
            throw ManagerDoesNotExist();
        }
        if(findIfTheWorkplaceExists(workplace_id) == false)
        {
            throw WorkplaceDoesNotExist();
        }

        shared_ptr<Workplace> workplace_ptr = getWorkplace(workplace_id);
        Citizen* regular_ptr_employee = &(*employee_ptr);
        Employee* employee_ptr_whith_employee_type  = dynamic_cast<Employee*>(regular_ptr_employee);
        workplace_ptr->hireEmployee(hire_condition, employee_ptr_whith_employee_type , manager_id);
        return;
    }

}

#endif //CITY_H_