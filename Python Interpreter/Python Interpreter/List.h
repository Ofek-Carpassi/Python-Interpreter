// List.h
#pragma once
#include "Type.h"
#include <vector>

class List : public Type
{
public:
    // Constructor
    List();
    List(const std::vector<Type*>& list);

    // Destructor
    ~List();

    // add element to list
    void append(Type* element);

    virtual bool isPrintable() const override;
    virtual std::string toString() const override;

    Type* getElementAt(size_t index) const;
    size_t size() const;

private:
    std::vector<Type*> elements;
};