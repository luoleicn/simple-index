#include "exception.h"

namespace luolei { namespace hit { namespace cir { namespace se { namespace exceptions {
    BasicException::BasicException(std::string s){
        msg = s;
    }
    std::string BasicException::getMsg(){
        return msg;
    }

    GVIException::GVIException(std::string s):BasicException(s){
    }

    S9Exception::S9Exception(std::string s):BasicException(s){
    }

}}}}}//namespace luolei::hit::cir::se::exceptions
