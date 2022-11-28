#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

namespace mtm
{
    // all exceptions
    class Exception : std::exception {};

    //if skill gets a negative changes
    class NegativePoints : mtm::Exception {};
    
    //if the employee gets a skill he already learnd
    class SkillAlreadyLearned : mtm::Exception {};

    //if the employee doesn't have enought points
    class CanNotLearnSkill : mtm::Exception {};

    //if the employee didn't lern the skill
    class DidNotLearnSkill : mtm::Exception {};

    //if the employee is already hired under a manager
    class EmployeeAlreadyHired : mtm::Exception {};

    //if the employee is not hire
    class EmployeeIsNotHired : mtm::Exception {};

    //if the employee/manager got a negative salary
    class NegativeSalary : mtm::Exception {};

    //if the manager isn't hired
    class ManagerIsNotHired : mtm::Exception {};

    //if the manager is already hired
    class ManagerAlreadyHired : mtm::Exception {};

    //if the manager works somewhere alse
    class CanNotHireManager : mtm::Exception {};

    //if the employee already exists
    class EmployeeAlreadyExists : mtm::Exception {};

    //if the employee doesn't exists
    class EmployeeDoesNotExist : mtm::Exception {};
    
    //if the manager already exists
    class ManagerAlreadyExists : mtm::Exception {};

    //if the mangaer desn't exists
    class ManagerDoesNotExist : mtm::Exception {};

    //if the faculty already exists
    class FacultyAlreadyExists : mtm::Exception {};

    //if the faculty doesn't exists
    class FacultyDoesNotExist : mtm::Exception {};

    //if the workplace aloready exists 
    class WorkplaceAlreadyExists : mtm::Exception {};

    //if the workplace doesn't exists
    class WorkplaceDoesNotExist : mtm::Exception {};

    //if the employee didnt get the job
    class EmployeeNotSelected : mtm::Exception {};

    //if the emplyee doesn't pass the test to get into the faculty
    class EmployeeNotAccepted : mtm::Exception {};

    //if the citizen doesn't exists
    class CitizenDoesNotExists : mtm::Exception {};

    //if the citizen already exists
    class CitizenAlreadyExists : mtm::Exception {};
}

#endif //EXCEPTIONS_H_