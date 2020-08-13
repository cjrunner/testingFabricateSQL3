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

extern char sqlTemplate[];  //see constants.c
extern unsigned long sizeOfTemplate;

// P R O T O T Y P E    P R O T O T Y P E    P R O T O T Y P E    P R O T O T Y P E    P R O T O T Y P E    P R O T O T Y P E
//void fabricateSQL(int numberOfTokensEqualToNumberOfReplacements, /* number of tokens (and replacements) to process */ \
//                  char **tokens, /*  an array of pointers to characters forming the tokens */ \
//                  char **replacements, /* an array of pointers to characters forming the replacemnet strings */ \
//                  char *input_c_string_template_buffer, /* points to the buffer containing the template */ \
//                  char *resulting_c_StringBuffer, /* points to the buffer contining the resulting sql */ \
//                  int sizeOf_resulting_c_StringBuffer, /* size of the previous buffer */  \
//                  int debugFlag /* output debug messages when set to >0 [TRUE] */     );

int main(int argc, const char * argv[]) { //const char *argv[] is the same as **argv
    // ******************************************************************************************************************************* \
    Note: fabricateSQL, the dylib under test, is found at: \
    /Users/cjc/Library/Developer/Xcode/DerivedData/Build/Products/Debug/libfabricateSQL.dylib \
    This program can load the above dynamic library (dylib) which this program tests, then before compiling: \
    a) place `/Users/cjc/Library/Developer/Xcode/DerivedData/Build/Products/Debug/libfabricateSQL.dylib` in \
    "Dynamic Library Install Name"; \
    b) Place `-lfabricateSQL` in "Other Linker Flags". \
    *******************************************************************************************************************************
    int d;
    printf( "Hello, %s\nsqlTemplate looks like:\n%s\nWe have %d input Parameters; command line parameters look like:\n",  \
           argv[0], sqlTemplate, argc);
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
        printf ("The order of the command line parameters is:\n1. The decimal siteid\n2. the date of interest (in YYYY-MM-DD format)\n \
                3. The zenithdistance of sunrise/sunset as a decimal floating point number (like 90.5833..)\n4. The numer of lines of data before \
                sunrise/sunset (as a decimal integer)\n5. The number of lines after sunrise/sunset (as a decimal integer)\n6. An indicaton of \
                sunset/sunrise, then use the ASCII character character strings of `SS` or `SunSet` character for sunset, \
                or the ASCII character string `SR` or `SunRise` for sunrise\n7. An opional any single Alpha character to indicate the \
                desire to ouput debugging information.\n");
        exit(1);
    }
    void *p;
    char *cbb_results = (char *) calloc(sizeOfTemplate*2, 1);
    char *ptrSQL_Input_Template = (char *)calloc(sizeOfTemplate, 1 );
    p = (char *)memcpy(ptrSQL_Input_Template, sqlTemplate, sizeOfTemplate ); //memcpy requires #include <string.h>
    //
    //  constants.cpp
    //  dataSurroundingSunSet
    //
    //  Created by Clifford Campo on 8/7/20.
    //  Copyright © 2020 CliffordCampo. All rights reserved.
    //
    //        SS *doSunSet =  new SS; //How does a C program know about c++ classes?
    
    char *str[expectedNumberOfTokenReplacements]; // Array containing pointers to the strings replacing the tokens.
    //    Take the replacement values from the command line.
    
    str[0] = (char *)argv[1];  // siteid {"26", "2020-08-06", "90.583333", "3", "3"};
    str[1] = (char *)argv[2];  // date
    str[2] = (char *)argv[3];  // ZenithDistance
    str[3] = (char *)argv[4];  // rows before SR or SS event
    str[4] = (char *)argv[5];  // rows after SR or SS event
    str[5] = (char *)argv[6];  // Indicator of sunrise (`SR` or `SunRise`) or sunset (`SS` or `SunSet`)
    
    
    if (d) {
        printf ("Replacement Array str[%d] looks like:\n",  expectedNumberOfTokenReplacements);
        for (int i=0; i<expectedNumberOfTokenReplacements; i++) {
            printf("\tstr[%d] = %s\n", i, str[i] );
        }
    }
    char *stt[expectedNumberOfTokenReplacements];   // Array containing pointers to the tokens.
    stt[0] = "SITEID";
    stt[1] = "_DATE_";
    stt[2] = "SUNSETDEF";
    stt[3] = "BEFORESUNSET";
    stt[4] = "AFTERSUNSET";
    stt[5] = "SRorSS";
    if (d) {
        printf ("Token Array stt[%d] looks like:\n",  expectedNumberOfTokenReplacements);
        for (int i=0; i<expectedNumberOfTokenReplacements; i++) {
            printf("\tstt[%d] = %s\n", i, stt[i] );
        }
    }
    
    
    //1
    //    std::string inputTemplate = sssql; //Initialize inputTemplate;
    ;
    if (d) printf ("========> about to call fabricateSQL\n");
    fabricateSQL(expectedNumberOfTokenReplacements , &stt[0], &str[0], ptrSQL_Input_Template, cbb_results, (int)sizeOfTemplate*2, d);
    if (d) printf("=======> Returned from fabricateSQL\n");
    if (d) printf("Call-back buffer, cbb, looks like:\n");
    printf  (")%s\n", cbb_results);
    if (d) printf("Done =============================================================================\n");
    free(ptrSQL_Input_Template);
    free(cbb_results);
    return 0;
}
