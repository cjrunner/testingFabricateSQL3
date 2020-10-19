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

//see constants.c
extern const char *ptrSS;
extern char sqlTemplateSS[];
extern unsigned long sizeOfTemplateSS;
extern char sqlTemplateNOON[];
extern unsigned long sizeOfTemplateNOON;
extern char *ptrSQLTemplateNOON;
extern char *ptrSQLTemplateSS;
extern char *ptrSQLTemplateSR;
extern unsigned long sizeOfTemplateSR;
extern sqlArray sqa[2][2];
extern sqlArray  *ptrSA;
extern char **fabricateArrays;

extern fabstruct fs[3];
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
/*
    const int maxRows = 4;
    const int maxColumns=2;
    sqlArray sqa[maxRows][maxColumns];
    sqa[3]->psql = NULL;
    sqa[3]->ulsql = 0;
    sqa[2]->psql = ptrSQLTemplateSS;           //Points to a character string of: PREAMBLE SELECT * FROM …
    sqa[2]->ulsql = sizeOfTemplateSS;          //returns a reasonable result of 1214 bytes
    //NOT THIS    sqa[2]->ulsql = sizeof(ptrSQLTemplateSS);  //returns a size of 8, the number of bytes comprising the size of a pointer
    sqa[1]->psql = ptrSQLTemplateNOON;         //Points to a character string of: PREAMBLE SELECT * FROM …
    sqa[1]->ulsql = sizeOfTemplateNOON;        //Returns a reasonable result of 1330 bytes
    //NOT THIS    sqa[1]->ulsql =sizeof(ptrSQLTemplateNOON); //Returns a value of 8, the number of bytes comprising the size of a pointer
    sqa[0]->psql = ptrSQLTemplateSR;           //Points to a character string of: PREAMBLE SELECT * FROM …
    sqa[0]->ulsql = sizeOfTemplateSR;          //Returns a reasonable result of 1262 bytes
    //NOT THIS    sqa[0]->ulsql = sizeof(ptrSQLTemplateSR);  //Returns a reasonable value of 8, the number of bytes comprising a pointer
    sqlArray  **ptrSA;
    sqlArray  *ptrsa;
    ptrsa = &sqa[0][0]; //Establish addressability to the array of structurs of type sqlArray
    ptrSA = &ptrsa;
    for (int k=0; k<maxRows; k++) {
        printf("%d, In source module constants.cpp, the 2X2 array named sqa looks like:\n%s \nand is of length %lu.\n", k, \
               sqa[k]->psql, sqa[k]->ulsql);
    }
 
    int rc;
    printf( "0. Hello, %s\nsqlTemplate looks like:\n%s\nWe have %d input Parameters; command line parameters look like:\n",  \
           argv[0], sqlTemplateSS, argc);
    for (int i=0; i < argc; i++) {
        printf ("\t%d. %s\n", i, argv[i]);
    }
    if (strcmp("DEBUG", *(argv + argc-1)) ) { //argc-1 means that we look for the last command line argument to indicate if we \
        go into debug mode. If the last command line argument is not `DEBUG` then we are not in debug mode.
        d = 0; //Assume no debugging. Debugging enables by setting one more command line input, of ANY character.
    } else {
        d = 1; //Enable debugging info from dylib.
    }
 */
 //   int expectedNumberOfTokenReplacements = argc-1-d; //This is the expected number of command line arguments we expect to have if \
    we don't set the debugging flag.
//    int numberOfTokenReplacementPairs = expectedNumberOfTokenReplacements>>1;
    //    const unsigned long sizeOfTemplate = sizeof(*sqlTemplate)+1;
    if (argc == 2) {
        printf ("01. The order of the command line parameters is:\n1. The decimal siteid\n02. the date of interest (in YYYY-MM-DD format)\n \
                03. The zenithdistance of sunrise/sunset as a decimal floating point number (like 90.5833..)\n4. The numer of lines of data before \
                sunrise/sunset (as a decimal integer)\n5. The number of lines after sunrise/sunset (as a decimal integer)\n6. An indicaton of \
                sunset/sunrise, then use the ASCII character character strings of `SS` or `SunSet` character for sunset, \
                or the ASCII character string `SR` or `SunRise` for sunrise\n7. An opional any single Alpha character to indicate the \
                desire to ouput debugging information.\n");
        exit(1);
    }
    int d;
    for (int i=0; i < argc; i++) printf ("\t%d. %s\n", i, argv[i]);
    if (strcmp("DEBUG", *(argv + argc-1)) ) { //argc-1 means that we look for the last command line argument to indicate if we \
        go into debug mode. If the last command line argument is not `DEBUG` then we are not in debug mode.
        d = 0; //Assume no debugging. Debugging enables by setting one more command line input, of ANY character.
    } else {
        d = 1; //Enable debugging info from dylib.
    }
    //
    //  constants.cpp
    //  dataSurroundingSunSet
    //
    //  Created by Clifford Campo on 8/7/20.
    //  Copyright © 2020 CliffordCampo. All rights reserved.
    //
    //        SS *doSunSet =  new SS; //How does a C program know about c++ classes?
 //   char *ss[numberOfTokenReplacementPairs][2];
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
  //  char **ptrss; //Point to an array of pointrs to character arrays (sometimes called c-strings);
 //   ptrss = &ss[0][0]; //Point to the first element of the array of pointers to character arrays.
 //   unsigned long i=0;
//    unsigned long j=0;
 //   while (  i < ( argc - d )  ) {
        //    for (unsigned long i=0; i <  expectedNumberOfTokenReplacements +1; i++ ) {
        //        printf("%s\t%s\n", ss[i][0], ss[i][1]); is another way to represent the print statement;
        //       ss[i+1][1] = (char *)(argv+i+1); //Fill the second column of each row of the 2-dimentional array, named ss, with the \
        value from command line
  //      ss[j][0] = (char *)argv[i+1];  //Copy the pointer to the token
  //      ss[j][1] = (char *)argv[i+2];  //Copy the pointer to the token's replacement value
  //      printf("%lu\tAddress %#lx\t%s\t%#lx\t%s\n", i, (unsigned long)*(ptrss+i), (char *)(*(ptrss+i)), (unsigned long)*(ptrss+i+1), (char *)(*(ptrss+i+1)) );
        
   //     j = 1 + j;
   //     i = 2 + i; //get the next pair of token/replacemnet values
   // }
    timings *ptrPerformanceBuffer;
    int rc = 0;
    void *p;
    int k=0;
    FILE *fp = fopen ("/Users/cjc/sql/testingFabricateSQL3.sql", "w");
    char **ptrMyArrays;
    fabstruct *f;  //Establish Addressability to typedef struct named fabsstruct
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    do {
        f = &fs[k]; //Get the k-th entry
        ptrMyArrays = f->fa; //Points to Preamble
        char *cbb_results = (char *) calloc(( f->templateSize + ( (f->templateSize)<<2) ), 1); //Since we don't know if the \
        token/replacement process used to fabricate the SQL will result in result that is greater than or less than the size of \
        the input template, we will request an outbuffer size that is 25% greater than the template size. Probably more than \
        enough space.
        char *ptrSQL_Input_Template = (char *)calloc(f->templateSize, 1 );
        ptrPerformanceBuffer = (timings *)calloc(1,1);
        p = (char *)memcpy(ptrSQL_Input_Template, f->fa, f->templateSize ); //memcpy requires #include <string.h>
        if (d) printf ("04.%d ========> about to call fabricateSQL\n", k);
 //       rc = expectedNumberOfTokenReplacements>>1; // Let rc contain the number of template/replacement pairs.
        fabricateSQLr2(ptrPerformanceBuffer, f->fa, f->myTemplate, cbb_results, f->templateSize, d);
        //    fabricateSQLr2(ptrPerformanceBuffer, &ss[0][0], ptrSQL_Input_Template, cbb_results, (int)sizeOfTemplateSS*2, d);
        //    fabricateSQLr2(ptrPerformanceBuffer, &ss[0][0], NULL, cbb_results, (int)sizeOfTemplateSS*2, d);
        //    fabricateSQLr2(NULL, &ss[0][0], NULL, cbb_results, (int)sizeOfTemplateSS*2, d);
        //    fabricateSQLr2(NULL, &ss[0][0], NULL, cbb_results, (int)NULL, d);
        if (d) printf("05.%d =======> Returned from fabricateSQL\n", k);
        if (d) printf("06.%d Call-back buffer, cbb, looks like:\n", k);
        printf  ("07. %s\n", cbb_results);
        rc=fprintf(fp, "08. %s\n", cbb_results);
        if (rc) printf("09. Got a non-zero return code from fprintf of %d\n", rc);
        if (d) printf("10.%d  Done =============================================================================\n", k);
        printf("fabricateSQL's total execution time: %lu nsec;\ntime to do constructor processing: %lu nsec;\ntime to do fabricate processing: %lu nsec;\ntime to do delete processing: %lu nsec.", \
               ptrPerformanceBuffer->totalTime, \
               ptrPerformanceBuffer->constructorTime, \
               ptrPerformanceBuffer->fabricateTime, \
               ptrPerformanceBuffer->deleteTime
               );
        free (ptrPerformanceBuffer);
        free(ptrSQL_Input_Template);
        free(cbb_results);
        
        k++;
        /*
         if (k == 2) {
         for (j = 0; j < numberOfTokenReplacementPairs; j++) {
         if (strcmp(ss[j][0], "SRorSS") == 0) {
         ss[j][1] = (char *)ptrSS;
         break;
         }
         }
         }
         */
    } while (k < 4);
    rc = fclose(fp);
    
    
    return rc;
}
