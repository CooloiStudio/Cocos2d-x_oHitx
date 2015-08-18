//
//  custom_string.h
//  MobileFoodOrderClient
//
//  Created by ZhongHan on 4/24/15.
//
//


#ifndef MobileFoodOrderClient_custom_string_h
#define MobileFoodOrderClient_custom_string_h

#include <iostream>
#include <string>
#include <sstream>

namespace std
{
    template < typename T > std::string to_string( const T& n )
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        
        std::ostringstream os;
        os << n;
        return os.str();
        
#else
        
        return std::to_string(n);
        
#endif
    }
}

#endif /* defined(__MobileFoodOrderClient__custom_string__) */
