//
//  main.c
//  testingFabricateSQL3
//
//  Created by Clifford Campo on 8/10/20.
//  Copyright © 2020 CliffordCampo. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "testingFabricateSQL3.h"

extern char sqlTemplateSS[];  //see constants.c
extern unsigned long sizeOfTemplateSS;

// P R O T O T Y P E    P R O T O T Y P E    P R O T O T Y P E    P R O T O T Y P E    P R O T O T Y P E    P R O T O T Y P E
//void fabricateSQL(int numberOfTokensEqualToNumberOfReplacements, /* number of tokens (and replacements) to process */ \
//                  char **tokens, /*  an array of pointers to characters forming the tokens */ \
//                  char **replacements, /* an array of pointers to characters forming the replacemnet strings */ \
//                  char *input_c_string_template_buffer, /* points to the buffer containing the template */ \
//                  char *resulting_c_StringBuffer, /* points to the buffer contining the resulting sql */ \
//                  int sizeOf_resulting_c_StringBuffer, /* size of the previous buffer */  \
//                  int debugFlag /* output debug messages when set to >0 [TRUE] */     );

int main(int argc, const char **argv) { //const char *argv[] is the same as **argv
    // ******************************************************************************************************************************* \
    Note: fabricateSQL, the dylib under test, is found at: \
    /Users/cjc/Library/Developer/Xcode/DerivedData/Build/Products/Debug/libfabricateSQL.dylib \
    This program can load the above dynamic library (dylib) which this program tests, then before compiling: \
    a) place `/Users/cjc/Library/Developer/Xcode/DerivedData/Build/Products/Debug/libfabricateSQL.dylib` in \
    "Dynamic Library Install Name"; \
    b) Place `-lfabricateSQL` in "Other Linker Flags". \
    *******************************************************************************************************************************
    int d;
    int rc;
    printf( "0. Hello, %s\nsqlTemplate looks like:\n%s\nWe have %d input Parameters; command line parameters look like:\n",  \
           argv[0], sqlTemplateSS, argc);
    for (int i=0; i < argc; i++) {
        printf ("\t%d. %s\n", i, argv[i]);
    }
    if (argc <= 7) {
        d = 0; //Assume no debugging. Debugging enables by setting one more command line input, of ANY character.
    } else {
        d = 1; //Enable debugging info from dylib.
    }
    int expectedNumberOfTokenReplacements = argc-1-d; //This is the expected number of command line arguments we expect to have if \
    we don't set the debugging flag.
    
    //    const unsigned long sizeOfTemplate = sizeof(*sqlTemplate)+1;
    if (argc == 2) {
        printf ("1. The order of the command line parameters is:\n1. The decimal siteid\n2. the date of interest (in YYYY-MM-DD format)\n \
                3. The zenithdistance of sunrise/sunset as a decimal floating point number (like 90.5833..)\n4. The numer of lines of data before \
                sunrise/sunset (as a decimal integer)\n5. The number of lines after sunrise/sunset (as a decimal integer)\n6. An indicaton of \
                sunset/sunrise, then use the ASCII character character strings of `SS` or `SunSet` character for sunset, \
                or the ASCII character string `SR` or `SunRise` for sunrise\n7. An opional any single Alpha character to indicate the \
                desire to ouput debugging information.\n");
        exit(1);
    }
    void *p;
    char *cbb_results = (char *) calloc(sizeOfTemplateSS*2, 1);
    char *ptrSQL_Input_Template = (char *)calloc(sizeOfTemplateSS, 1 );
    p = (char *)memcpy(ptrSQL_Input_Template, sqlTemplateSS, sizeOfTemplateSS ); //memcpy requires #include <string.h>
    //
    //  constants.cpp
    //  dataSurroundingSunSet
    //
    //  Created by Clifford Campo on 8/7/20.
    //  Copyright © 2020 CliffordCampo. All rights reserved.
    //
    //        SS *doSunSet =  new SS; //How does a C program know about c++ classes?
    char *ss[7][2];
//    char *ss[][2] = { /* Works for 2-column arrays of an arbitrary number of rows */ \
//        {"SITEID", ""}, /* Let us see how the compiler responds to NULL. According to debugger NULL looks like an
//                           address of 00 00 00 00 00 00 00 00 */ \
        {"_DATE_",""},\
        {"SUNSETDEF","90.58333333"}, \
        {"BEFORESUNSET", "3"}, \
        {"AFTERSUNSET","3"},\
        {"SRorSS","SR"}, \
        {"TERM", ""} /* "TERM" signifies last row while the second argument of this row is of zero length */ \
    };

//    ss[1][1] = (char *)(argv+1);
//    ss[2][1] = (char *)(argv+2);
    char **ptrss;
    ptrss = &ss[0][0];
    unsigned long i=0;
    unsigned long j=0;
    while (  i < ( argc - d )  ) {
//    for (unsigned long i=0; i <  expectedNumberOfTokenReplacements +1; i++ ) {
        //        printf("%s\t%s\n", ss[i][0], ss[i][1]); is another way to represent the print statement;
 //       ss[i+1][1] = (char *)(argv+i+1); //Fill the second column of each row of the 2-dimentional array, named ss, with the \
        value from command line
        ss[j][0] = (char *)argv[i+1];  //Copy the pointer to the token
        ss[j][1] = (char *)argv[i+2];  //Copy the pointer to the token's replacement value
        printf("%lu\tAddress %#lx\t%s\t%#lx\t%s\n", i, (unsigned long)*(ptrss+i), (char *)(*(ptrss+i)), (unsigned long)*(ptrss+i+1), (char *)(*(ptrss+i+1)) );
        
        j = 1 + j;
        i = 2 + i; //get the next pair of token/replacemnet values
    }

    
    ;
    if (d) printf ("4. ========> about to call fabricateSQL\n");
    fabricateSQLr2(expectedNumberOfTokenReplacements , &ss[0][0], ptrSQL_Input_Template, cbb_results, (int)sizeOfTemplateSS*2, d);
    if (d) printf("5 =======> Returned from fabricateSQL\n");
    if (d) printf("6 Call-back buffer, cbb, looks like:\n");
    printf  ("%s\n", cbb_results);
    if (d) printf("7.  Done =============================================================================\n");
    free(ptrSQL_Input_Template);
    free(cbb_results);
    return 0;
}
