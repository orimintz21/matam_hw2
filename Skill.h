#ifndef SKILL_H_
#define SKILL_H_

#include <ostream>
#include "exceptions.h"


using std::string;
using std::istream;
using std::ostream;
using std::endl;
using namespace mtm;
namespace mtm
{
    class Skill
    {
    private:
        int id;
        string name;
        int skill_points;

        
    public:
        /**
         * @brief Construct a new Skill object
         * 
         * @param new_id the skill's id
         * @param new_name the skill's name
         * @param new_skill_points the number of points that the employee needs to have to 
         * learn the skill
         */
        Skill(int new_id, string new_name, int new_skill_points);
        /**
         * @brief Destroy the Skill object
         * 
         */
        ~Skill() = default;
        /**
         * @brief Copy construct 
         */
        Skill(const Skill&) = default;
        /**
         * @brief Get the Id of the skill
         * 
         * @return int 
         */
        int getId() const;
        /**
         * @brief Get the Name object
         * 
         * @return string 
         */
        string getName() const;
        /**
         * @brief Get the Required Points for that skill
         * 
         * @return int 
         */
        int getRequiredPoints() const;
        /**
         * @brief adds the added_skill_points int to the skill_points
         * 
         * throws NegativePoints if added_skill_points<0
         * 
         * @param added_skill_points 
         * @return Skill& 
         */
        Skill& operator+=(const int added_skill_points);
        /**
         * @brief adds 1 to skill_points
         * 
         * @return Skill 
         */
        Skill operator++(int);
        };

    //operators, compers the skill_points:
    //if the number of points of skill1 = skill2
    bool operator==(const Skill& skill1, const Skill& skill2);
    //if the number of points of skill1 != skill2
    bool operator!=(const Skill& skill1, const Skill& skill2);
    //if the number of points of skill1 < skill2
    bool operator<(const Skill& skill1, const Skill& skill2);
    //if the number of points of skill1 <= skill2
    bool operator<=(const Skill& skill1, const Skill& skill2);
    //if the number of points of skill1 > skill2
    bool operator>(const Skill& skill1, const Skill& skill2);
    //if the number of points of skill1 >= skill2
    bool operator>=(const Skill& skill1, const Skill& skill2);

    /**
     * @brief adds the amount to skill_points
     * throws NegativePoints if amount<0
     * @param skill 
     * @param amount 
     * @return Skill& 
     */
    Skill operator+(const Skill& skill, const int amount);
    Skill operator+(const int amount, const Skill& skill);

    /**
     * @brief prints to the stream
     * 
     * @param stream 
     * @param skill 
     * @return ostream& 
     */
    ostream& operator<<(ostream& stream, const Skill& skill);


}

#endif //SKILL_H_