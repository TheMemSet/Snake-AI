#ifndef AI_HPP_INCLUDED
#define AI_HPP_INCLUDED

#include <utility>
#include <vector>

class AI
{
public:
    char update (std::vector <std::pair <int, int>>&snake,std::vector <std::pair <int, int>>&fruit);
};

#endif // AI_HPP_INCLUDED
