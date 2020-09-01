//
//  testingFabricateSQL3.h
//  testingFabricateSQL3
//
//  Created by Clifford Campo on 8/11/20.
//  Copyright © 2020 CliffordCampo. All rights reserved.
//

#ifndef testingFabricateSQL3_h
#define testingFabricateSQL3_h
// P R O T O T Y P E    P R O T O T Y P E    P R O T O T Y P E    P R O T O T Y P E    P R O T O T Y P E    P R O T O T Y P E
void fabricateSQLr2(char *pd, /* pointer to buffer containing fabricateSQL's performance data. If NULL then no performance data. */ \
                  char **tokensAndReplacements,        /*  a 2-dimensional array of pointers to characters forming the tokens and  \
                    replacements. \
                    Note that the first parameter of fabricateSQLr2, above, defines the size of this array. */ \
                  char *input_c_string_template_buffer,                         /* points to the buffer containing the template */ \
                  char *resulting_c_StringBuffer,                           /* points to the buffer contining the resulting sql,
                       having all Tokens replaced by their replacement c-strings.                                               */ \
                  int sizeOf_resulting_c_StringBuffer,                                 /* size of the resulting_c_string buffer */ \
                  int debugFlag                                                 /* output debug messages when set to >0 [TRUE] */ );
//Above is how one calls the c++-coded dylib, fabricateSQL
static const char *  SUNRISE = "<";
static const char  * SUNSET =  ">";
typedef struct sqlArray {
    char *psql;
    unsigned long ulsql;
} sqlArray;
#endif /* testingFabricateSQL3_h */
