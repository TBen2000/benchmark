#include "ProtobufEncoder.hpp"
#include "Protobuf/addressbook.pb.h"
#include "../IDs.hpp"
#include "../ConcreteDataStructure/Person.hpp"

std::string ProtobufEncoder::encode(std::shared_ptr<IDataStructure> structure)
{
    std::string container;
    if (structure->getID() == PersonID)
    {
        auto pointer = dynamic_cast<Person *>(structure.get());
        //auto pointer = std::dynamic_pointer_cast<std::shared_ptr<Person>>(structure);
        tutorial::AddressBook address_book;
        tutorial::Person * person = address_book.add_people();
        person->set_name(pointer->getName());
        person->set_email(pointer->getEmail());
        std::vector<PhoneNumber> numbers = pointer->getNumbers();
        for (PhoneNumber &num : numbers)
        {
            tutorial::Person::PhoneNumber *phoneNumber = person->add_phones();
            phoneNumber->set_number(num.getNumber());

            if (num.getNumberType() == MOBILE)
                phoneNumber->set_type(tutorial::Person::MOBILE);
            else if (num.getNumberType() == HOME)
                phoneNumber->set_type(tutorial::Person::HOME);
            else if (num.getNumberType() == WORK)
                phoneNumber->set_type(tutorial::Person::WORK);
            else
                std::cout << "Unknown phone type.  Using default." << std::endl;
        }

        container =  person->SerializeAsString();
    }


    return container;
}

std::string ProtobufEncoder::getName()
{
    return "Protobuf";
}
