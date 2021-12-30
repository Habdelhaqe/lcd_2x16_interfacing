/* 
 * File:   my_utils.h
 * Author: Engs
 *
 * Created on 29 December 2021, 16:22
 */

#ifndef MY_UTILS_H
#define	MY_UTILS_H
    
    #include "common_types_defs.h"

    #define STRING_MATCH 1
    #define STRING_NOT_MATCH 0
    
    u8 compare2Strings(u8 *ptr_str1,u8 *ptr_str2,u8 ignore_case);
    
    void integerToChars(s32 num , u8 *ptr_buffer , u8 radix);

#endif	/* MY_UTILS_H */
