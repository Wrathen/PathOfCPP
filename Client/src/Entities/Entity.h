#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include "Miscellaneous/GUID.h"

class Entity {
    friend class EntityManager;
public:
    Entity();
    Entity(std::string name);

    void Delete();
    std::string ToString();
private:
    void AssignGUID(GUID guid) { this->guid = guid; }

public:
    std::string name;
    GUID guid = 0;
};