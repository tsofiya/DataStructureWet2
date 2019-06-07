//
// Created by lucio on 6/3/2019.
//

#ifndef WET2_DYNAMICARRAYEXCEPTIONS_H
#define WET2_DYNAMICARRAYEXCEPTIONS_H
#include <exception>

    //General Exception, all others will inherit from:
    class ArrayExceptions : public std::exception {
    public:
        virtual ~ArrayExceptions() throw() {}
    };
//Exception: the key of an element we searched for in the AVLtree does not exist in the tree
    class IllegalArgument : public ArrayExceptions {
        virtual const char *what() const throw() {
            return "Wet2Exceptions: Illegal argument.";
        }
    };

class Failure : public ArrayExceptions {
    virtual const char *what() const throw() {
        return "Wet2Exceptions: Procedure failed.";
    }
};

class NullArgument : public ArrayExceptions {
    virtual const char *what() const throw() {
        return "Wet2Exceptions: Null argument.";
    }
};

class ElementDoesNotExist : public ArrayExceptions {
    virtual const char *what() const throw() {
        return "Wet2Exceptions: Element does not exist.";
    }
};






#endif //WET2_DYNAMICARRAYEXCEPTIONS_H
