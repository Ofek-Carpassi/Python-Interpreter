#include "Parser.h"
#include <iostream>
#include "Helper.h"
#include "Type.h"
#include "InterpreterException.h"
#include "IndentationException.h"
#include "SyntaxException.h"
#include "Integer.h"
#include "Boolean.h"
#include "String.h"
#include "NameErrorException.h"
#include "List.h"

std::unordered_map<std::string, Type*> Parser::variables;

Type* Parser::parseString(const std::string& str)
{
    if (str.empty()) return nullptr;

    if (str[0] == ' ' || str[0] == '\t')
        throw IndentationException();

    // Remove white spaces
    std::string trimmed = str;
    Helper::trim(trimmed);

    // Check if the string is a variable
    Type* typeOfVar = getVariableValue(trimmed);
    if (typeOfVar != nullptr)
        return typeOfVar;

    // Check if the string is a method call (NEW!)
    if (handleMethodCall(trimmed))
        return nullptr;

    // Check if the string is an assignment
    if (makeAssignment(trimmed))
        return nullptr;

    Type* t = getTypeStatic(trimmed);
    if (t == nullptr)
        throw SyntaxException();    

    t->setIsTemp(true); // Mark as temporary so it gets cleaned up
    return t;
}

Type* Parser::getTypeStatic(std::string& str)
{
    // Start by removing white spaces in the start
    Helper::trim(str);
    
    Type* t = nullptr;
    
    // Check for list - must start with [ and end with ]
    if (str.size() >= 2 && str[0] == '[' && str[str.length() - 1] == ']') 
    {
        // Handle the list case
        std::vector<Type*> elements;
        
        // Handle empty list
        if (str.length() == 2) {
            return new List();
        }
        
        // Parse list elements
        std::string content = str.substr(1, str.length() - 2);
        std::string currentElement;
        
        int bracketDepth = 0;
        bool inSingleQuote = false;
        bool inDoubleQuote = false;
        
        for (size_t i = 0; i < content.length(); ++i) {
            char c = content[i];
            
            // Track quotes to handle strings with commas
            if (c == '\'' && !inDoubleQuote) {
                inSingleQuote = !inSingleQuote;
            } else if (c == '\"' && !inSingleQuote) {
                inDoubleQuote = !inDoubleQuote;
            }
            
            // Track bracket nesting for nested lists
            if (!inSingleQuote && !inDoubleQuote) {
                if (c == '[') bracketDepth++;
                else if (c == ']') bracketDepth--;
            }
            
            // Process element separator (comma)
            if (c == ',' && bracketDepth == 0 && !inSingleQuote && !inDoubleQuote) {
                // Found element separator
                Helper::trim(currentElement);
                if (!currentElement.empty()) {
                    Type* element = getTypeStatic(currentElement);
                    if (element) {
                        elements.push_back(element);
                    } else {
                        // Clean up if we couldn't parse an element
                        for (Type* elem : elements) {
                            delete elem;
                        }
                        return nullptr;
                    }
                }
                currentElement.clear();
            } else {
                currentElement += c;
            }
        }
        
        // Process the last element
        Helper::trim(currentElement);
        if (!currentElement.empty()) {
            Type* element = getTypeStatic(currentElement);
            if (element) {
                elements.push_back(element);
            } else {
                // Clean up if we couldn't parse the last element
                for (Type* elem : elements) {
                    delete elem;
                }
                return nullptr;
            }
        }
        
        t = new List(elements);
    }
    else if (Helper::isInteger(str))
    {
        Helper::removeLeadingZeros(str);
        t = new Integer(std::stoi(str));
    }
    else if (Helper::isBoolean(str))
    {
        bool b = str == "True" ? true : false;
        t = new Boolean(b);
    }
    else if (Helper::isString(str))
        t = new String(str);
    else
        return nullptr;

    return t;
}

bool Parser::isLegalVarName(const std::string& str)
{
    if (str.empty() || Helper::isDigit(str[0]))
        return false;
    
    for (char c : str)
        if (!(Helper::isLetter(c) || Helper::isDigit(c) || Helper::isUnderscore(c)))
            return false;
    
    return true;
}

bool Parser::makeAssignment(const std::string& str)
{
    std::size_t pos = str.find("=");
    if (pos == std::string::npos)
        return false;

    std::string varName = str.substr(0, pos);
    std::string varValue = str.substr(pos + 1);

    Helper::trim(varName);
    Helper::trim(varValue);

    if (!isLegalVarName(varName))
        throw NameErrorException(varName);

    // First check if varValue is a variable name
    Type* sourceVar = getVariableValue(varValue);
    Type* t = nullptr;
    
    if (sourceVar != nullptr) {
        if (auto intVal = dynamic_cast<Integer*>(sourceVar))
            t = new Integer(std::stoi(intVal->toString()));
        else if (auto boolVal = dynamic_cast<Boolean*>(sourceVar))
            t = new Boolean(boolVal->toString() == "True");
        else if (auto strVal = dynamic_cast<String*>(sourceVar)) {
            std::string value = strVal->toString();
            value = value.substr(1, value.length() - 2);
            t = new String(value);
        }
        else if (auto listVal = dynamic_cast<List*>(sourceVar)) {
            // Deep copy the list
            std::vector<Type*> newElements;
            for (size_t i = 0; i < listVal->size(); i++) {
                Type* element = listVal->getElementAt(i);
                
                // We need to create a deep copy of each element
                if (auto intElem = dynamic_cast<Integer*>(element))
                    newElements.push_back(new Integer(std::stoi(intElem->toString())));
                else if (auto boolElem = dynamic_cast<Boolean*>(element))
                    newElements.push_back(new Boolean(boolElem->toString() == "True"));
                else if (auto strElem = dynamic_cast<String*>(element)) {
                    std::string value = strElem->toString();
                    value = value.substr(1, value.length() - 2);
                    newElements.push_back(new String(value));
                }
                else if (auto nestedListElem = dynamic_cast<List*>(element)) {
                    // For nested lists, we need recursive deep copying
                    // This is simplified but should work for basic cases
                    std::string listStr = nestedListElem->toString();
                    Type* newNestedList = getTypeStatic(listStr);
                    if (newNestedList) {
                        newElements.push_back(newNestedList);
                    }
                }
            }
            
            t = new List(newElements);
        }
    } else {
        t = getTypeStatic(varValue);
        if (t == nullptr)
            throw NameErrorException(varValue);
    }

    // Clean up previous value if it exists
    auto it = variables.find(varName);
    if (it != variables.end()) {
        delete it->second;
        variables.erase(it);
    }

    variables.emplace(varName, t);
    return true;
}

Type* Parser::getVariableValue(std::string& str)
{
	// Remove white spaces
	Helper::trim(str);
	if (variables.find(str) == variables.end())
		return nullptr;
	return variables[str];
}

void Parser::clearVariables()
{
	for (auto it = variables.begin(); it != variables.end(); it++)
		delete it->second;

	variables.clear();
}

bool Parser::handleMethodCall(const std::string& str)
{
    size_t dotPos = str.find('.');
    if (dotPos == std::string::npos)
        return false;
    
    size_t openParenPos = str.find('(', dotPos);
    size_t closeParenPos = str.find(')', openParenPos);
    
    if (openParenPos == std::string::npos || closeParenPos == std::string::npos)
        return false;
    
    std::string objectName = str.substr(0, dotPos);
    Helper::trim(objectName);
    
    std::string methodName = str.substr(dotPos + 1, openParenPos - dotPos - 1);
    Helper::trim(methodName);
    
    std::string argStr = str.substr(openParenPos + 1, closeParenPos - openParenPos - 1);
    Helper::trim(argStr);
    
    // Check if object exists
    Type* object = getVariableValue(objectName);
    if (!object)
        throw NameErrorException(objectName);
    
    // Handle List methods
    if (auto listObj = dynamic_cast<List*>(object)) {
        if (methodName == "append") {
            // Parse the argument
            Type* arg = nullptr;
            
            // First check if arg is a variable
            Type* varArg = getVariableValue(argStr);
            if (varArg != nullptr) {
                // Deep copy the argument
                if (auto intVal = dynamic_cast<Integer*>(varArg))
                    arg = new Integer(std::stoi(intVal->toString()));
                else if (auto boolVal = dynamic_cast<Boolean*>(varArg))
                    arg = new Boolean(boolVal->toString() == "True");
                else if (auto strVal = dynamic_cast<String*>(varArg)) {
                    std::string value = strVal->toString();
                    value = value.substr(1, value.length() - 2);
                    arg = new String(value);
                }
                else if (auto listVal = dynamic_cast<List*>(varArg)) {
                    // Create deep copy of list through toString and parsing
                    std::string listStr = listVal->toString();
                    arg = getTypeStatic(listStr);
                }
            } else {
                arg = getTypeStatic(argStr);
            }
            
            if (arg == nullptr)
                throw SyntaxException();
            
            // Set as non-temporary since it will be owned by the list
            arg->setIsTemp(false);
            listObj->append(arg);
            return true;
        }
    }
    
    throw SyntaxException(); // Method not supported
}