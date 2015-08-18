//
//  custom_string.h
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 4/24/15.
//
//


#ifndef MobileFoodOrderClient_custom_string_h
#define MobileFoodOrderClient_custom_string_h

#include <string>
#include <iostream>

#include <string>
#include <sstream>

namespace std
{
    template < typename T > std::string to_string( const T& n )
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        
        std::ostringstream os;
        os << value;
        return os.str();
        
#else
        
        return std::to_string(value);
        
#endif
    }
}

#endif /* defined(__MobileFoodOrderClient__custom_string__) */