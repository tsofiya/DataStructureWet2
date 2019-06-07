//
// Created by tsofi on 07/06/2019.
//

#ifndef WET2_WET2EXCEPTIONS_H
#define WET2_WET2EXCEPTIONS_H
namespace Wet2Utils{
    class Wet2Exceptions : public std::exception {
    public:
        virtual ~Wet2Exceptions() throw() {}
    };

    class InvalidInput:public Wet2Exceptions{
        virtual const char *what() const throw() {
            return "Wet2Exception: Invalid input.";
        }
    };

    class Failure : public Wet2Exceptions {
        virtual const char *what() const throw() {
            return "Wet1Exception: Failure.";
        }
    };

    class AlreadyExist : public Wet2Exceptions {
        virtual const char *what() const throw() {
            return "Wet1Exception: Already exist.";
        }
    };

    class KeyNotExist : public Wet2Exceptions {
        virtual const char *what() const throw() {
            return "Wet1Exception: Already exist.";
        }
    };

}
#endif //WET2_WET2EXCEPTIONS_H
