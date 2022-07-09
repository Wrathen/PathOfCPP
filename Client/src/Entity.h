#pragma once
#include <stdio.h>
#include <iostream>
#include <string>

typedef unsigned int GUID;

class Entity {
    friend class EntityManager;
public:
    Entity();
    Entity(std::string name);

    void Delete();
    std::string ToString();
private:
    void AssignGUID(unsigned int guid) { this->guid = guid; }

public:
    std::string name;
    unsigned int guid = 0;
};