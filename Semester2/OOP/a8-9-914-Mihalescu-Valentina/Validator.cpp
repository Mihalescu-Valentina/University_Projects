#include "Event.h"
#include "Validator.h"
using namespace std;

ValidationException::ValidationException(std::string _message) : message{ _message }
{
}

std::string ValidationException::getMessage() const {
    return this->message;
}

ValidationExceptionInherited::ValidationExceptionInherited(std::string _message) : message{ _message }
{
}

const char* ValidationExceptionInherited::what() const noexcept {
    return message.c_str();
}

void EventValidator::validate(Event& e) {
    string errors;
    if (e.getDate().compareDay(std::to_string(0)) || !e.getDate().compareDay(std::to_string(31)))
        errors += string("The day must be a number between 1 and 31 maximum.\n");
    if (e.getDate().compareMonth(std::to_string(0)) && !e.getDate().compareMonth(std::to_string(13)))
        errors += string("The month must be a number between 1 and 12.\n");
    if (e.getDate().compareYear(std::to_string(0)))
        errors += string("The year cannot be 0 or negative.\n");
    if (e.getNrPeople() < 0)
        errors += string("Cannot have a negative number of people attending an event.\n");

    if (errors.size() > 0)
        throw ValidationException(errors);
}