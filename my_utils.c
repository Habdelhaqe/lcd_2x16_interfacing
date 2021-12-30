#include"my_utils.h"

u8 compare2Strings(u8 *ptr_str1,u8 *ptr_str2 , u8 ignore_case){
	
	u8 compare_result = STRING_MATCH;
	
	for(u32 index = 0 ; *(ptr_str1+index) != NULL_CHAR || *(ptr_str2+index) != NULL_CHAR ; index++){
		
        if( ignore_case &&
			 ( ( (*(ptr_str1+index) >64 && *(ptr_str1+index)<91) || (*(ptr_str2+index) >96 && *(ptr_str2+index)<123) ) ||
			   ( (*(ptr_str2+index) >64 && *(ptr_str2+index)<91) || (*(ptr_str1+index) >96 && *(ptr_str1+index)<123) )   ) ){
			if( ( (*(ptr_str1+index)<91) && (*(ptr_str1+index) + ALPHA_CHARS_SHIFT) != *(ptr_str2+index)) || 
				( (*(ptr_str2+index)<91) && (*(ptr_str2+index) + ALPHA_CHARS_SHIFT) != *(ptr_str1+index))   ){
			compare_result = STRING_NOT_MATCH;
			break;
			}
		}else if( *(ptr_str1+index) != *(ptr_str2+index) ){
			compare_result = STRING_NOT_MATCH;
			break;
		}
		
	}
	
	return compare_result;	
}

void integerToChars(s32 num, u8* ptr_buffer, u8 radix){
    
	u8 sign = 0;
	u8 *buffer_temp = ptr_buffer;
    
	if(num < 0 ){
		sign ++;
		num = -num;
	}
	
	while(num){
		
		*ptr_buffer = ASCII_ZER0_CHARACTER + num%radix;
				
		num/=radix;
		
		ptr_buffer++;
	}
	
	if(radix == 10 && sign){
		*ptr_buffer++ = '-';
	}
	
	*ptr_buffer = NULL_CHAR;
	
	if(radix == 2 && sign){
        
		u8 index  , carry ;
		
		for(index = 0 ; *(buffer_temp+index)!=NULL_CHAR ; index++){
			
			*(buffer_temp + index) = 
                *(buffer_temp + index) == ASCII_ZER0_CHARACTER ? 
                        ASCII_ONE_CHARACTER : ASCII_ZER0_CHARACTER;

		}
		
		for(index = 0 , carry = 1 ; *(buffer_temp+index)!=NULL_CHAR ; index++){

			if( *(buffer_temp + index) == ASCII_ZER0_CHARACTER && carry ){
				*(buffer_temp + index) = ASCII_ONE_CHARACTER;
				carry = 0;
			}else if(*(buffer_temp + index) == ASCII_ONE_CHARACTER && carry ){
				*(buffer_temp + index) = ASCII_ZER0_CHARACTER ;
			}

		}
		
//		 *(buffer_temp + index) = ASCII_ZER0_CHARACTER + carry;

		for(; index < 8 * sizeof(s32) ;index++){
			*(buffer_temp + index) = ASCII_ONE_CHARACTER ;
		}
		*(buffer_temp + index) = NULL_CHAR;
	}

}