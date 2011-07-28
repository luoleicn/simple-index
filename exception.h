#ifndef _EXCEPTION_H
#define _EXCEPTION_H

#include <iostream>

namespace luolei { namespace hit { namespace cir { namespace se { namespace exceptions {
    class BasicException{
        private:
            std::string msg;
        public:
            BasicException(std::string s);
            std::string getMsg();
    };

    class GVIException : public BasicException{
        public:
            GVIException(std::string s);
    };

    class S9Exception : public BasicException{
        public:
            S9Exception(std::string s);
    };


}}}}}//namespace luolei::hit::cir::se::exceptions
#endif //_EXCEPTION_H
