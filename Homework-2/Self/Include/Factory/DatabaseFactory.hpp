//
// Created by Alex Tran on 2/18/24.
//

#ifndef SELF_DATABASEFACTORY_H
#define SELF_DATABASEFACTORY_H
#include "../Interface/IRecord.hpp"
#include "../Concrete/TravelerInfo.hpp"

class DatabaseFactory {
public:
    static std::shared_ptr<IRecord> CreateTravelerInfo() {
        return std::make_shared<TravelerInfo>();
    }
};


#endif //SELF_DATABASEFACTORY_H
