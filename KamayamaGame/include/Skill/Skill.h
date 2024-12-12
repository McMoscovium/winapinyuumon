#pragma once


#include <string>


class Skill {
private:
    std::string name = "Ç≤Ç›";
    std::string description = "ê_";
public:
    //serialóp
    template <class Archive>
    void serialize(Archive& archive) {
        archive(name, description);
    }
};