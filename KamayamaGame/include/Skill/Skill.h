#pragma once


#include <string>


class Skill {
private:
    std::string name = "����";
    std::string description = "�_";
public:
    //serial�p
    template <class Archive>
    void serialize(Archive& archive) {
        archive(name, description);
    }
};