#define BIORBD_API_EXPORTS
#include "s2mError.h"

#include "s2mString.h"

void s2mError::s2mAssert(bool cond, const s2mString &s){
    if (!cond){
        std::cout << "ERROR: " << s << std::endl;
        throw std::runtime_error(s);
    }

}

void s2mError::s2mWarning(bool cond, const s2mString &s){
    if (!cond){
        std::cout << "Warning: " << s << std::endl;
    }
}
