#include "List.h"

List::List()
{
}

List::List(const std::vector<Type*>& list) : elements(list)
{
}

List::~List()
{
    for (Type* t : elements)
        if(t && t->getIsTemp()) // Fix this line, was t->isTemp()
            delete t;
}

void List::append(Type* element)
{
    elements.push_back(element);
}

bool List::isPrintable() const
{
    return true;
}

std::string List::toString() const
{
    std::string result = "[";
    
    for (size_t i = 0; i < elements.size(); i++) {
        if (elements[i]) {
            result += elements[i]->toString();
        }
        
        if (i < elements.size() - 1) {
            result += ", ";
        }
    }
    
    result += "]";
    return result;
}

Type* List::getElementAt(size_t index) const
{
    if (index < elements.size())
        return elements[index];
    return nullptr;
}

size_t List::size() const
{
    return elements.size();
}