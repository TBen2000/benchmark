#include "../IDataStorage.hpp"

class PrintDataStorage : public IDataStorage
{
public:
    virtual void store(const int event, const std::string component, const std::string buffer);
    virtual std::string getName();
};
