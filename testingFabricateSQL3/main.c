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
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
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
extern char **fabricate2DArrays[];
extern char *sunRiseArray[];
extern fabstruct fs[3];
// P R O T O T Y P E    P R O T O T Y P E    P R O T O T Y P E    P R O T O T Y P E    P R O T O T Y P E    P R O T O T Y P E
//void fabricateSQL(int numberOfTokensEqualToNumberOfReplacements, /* number of tokens (and replacements) to process */ \
//                  char **tokens, /*  an array of pointers to characters forming the tokens */ \
//                  char **replacements, /* an array of pointers to characters forming the replacemnet strings */ \
//                  char *input_c_string_template_buffer, /* points to the buffer containing the template */ \
//                  char *resulting_c_StringBuffer, /* points to the buffer contining the resulting sql */ \
//                  int sizeOf_resulting_c_StringBuffer, /* size of the previous buffer */  \
//                  int debugFlag /* output debug messages when set to >0 [TRUE] */     );

int main(int argc, const char **argv, const char **env, const char **somethingElse) { //const char *argv[] is the same as **argv
    // ******************************************************************************************************************************* \
    Note: fabricateSQL, the dylib under test, is found at: \
    /Users/cjc/Library/Developer/Xcode/DerivedData/Build/Products/Debug/libfabricateSQL.dylib \
    This program can load the above dynamic library (dylib) which this program tests, then before compiling: \
    a) place `/Users/cjc/Library/Developer/Xcode/DerivedData/Build/Products/Debug/libfabricateSQL.dylib` in \
    "Dynamic Library Install Name"; \
    b) Place `-lfabricateSQL` in "Other Linker Flags". \
    *******************************************************************************************************************************
    printf("===============================================somethingElse=====================================================\n");
    int j=1;
    int i=0;
    int k=0;
    while (*(somethingElse+j) ) {
        printf("%02d. (note: j=0 is a pointer to 0x0…0, so we'll skip it) somethingElse address %p value %s\n", j, (somethingElse+j), *(somethingElse + j));
        j++;
    }
    printf("=====================================================env=========================================================\n");
    j=0;
    while (*(env+j) ) {
        printf("%02d. env address %p value %s\n", j, (env+j), *(env + j));
        j++;
    }
    printf("======================================================argv========================================================\n");
    j=0;
    while (*(argv+j) ) {
        printf("%02d. argv address %p value %s\n", j, (argv+j), *(argv + j));
        j++;
    }
    if  ( (argc > 1) && (((strcmp(argv[1], "--help" )) == 0) || ((strcmp(argv[1], "-h" )) == 0))  ) {
        printf ("01. The order of the command line parameters is:\n1. The decimal siteid\n02. the date of interest (in YYYY-MM-DD format)\n \
                03. The zenithdistance of sunrise/sunset as a decimal floating point number (like 90.5833..)\n4. The numer of lines of data before \
                sunrise/sunset (as a decimal integer)\n5. The number of lines after sunrise/sunset (as a decimal integer)\n6. An indicaton of \
                sunset/sunrise, then use the ASCII character character strings of `SS` or `SunSet` character for sunset, \
                or the ASCII character string `SR` or `SunRise` for sunrise\n7. An opional any single Alpha character to indicate the \
                desire to ouput debugging information.\n");
        exit(1);
    }
    char ***f2d; // Mon Dieu, triple indirection!!
    char **some2Darray;
     f2d = (fabricate2DArrays + 0);  //Pick out the first (i.e., offset zero) of the entries in array, named fabricate2DArrays. This \
    should be the SunRise array. The next (offset = 1) should be the Noon Array. After the noon Array should be the SunSet Array \
    (i.e., offset = 2).
    int d;
    for (i=0; i < argc; i++) printf ("\t%d. %s\n", i, argv[i]); //List out the command line argument
    if (strcmp("DEBUG", *(argv + argc-1)) ) { //argc-1 means that we look for the last command line argument to indicate if we \
        go into debug mode. If the last command line argument is not `DEBUG` then we are not in debug mode.
        d = 0; //Assume no debugging. Debugging enables by setting one more command line input, of ANY character.
    } else {
        d = 1; //Enable debugging info from dylib.
        printf("                                       Debug mode enabled\n");
    }
//Update the internal 2D-arrays that will drive the fabrication process.
    for (i = 0; (i < argc-1 && argc > 1); i++ ) {
        if(*(f2d + i)) {
            some2Darray = *(f2d + i);
            //        Given that the first argv entry (argc=1) is a pointer to the fully qulaified file name of this executable then:
            if (argc >= 2) {
                *(some2Darray + OFFSET_SITEID*2 + 1) = *(char **)(argv + 1); //The next command line argument is the desired siteid.
            }
            if (argc >= 3) {
                *(some2Darray + OFFSET_DATE*2 + 1)   = *(char **)(argv + 2); //Then the desired date
            }
            if (argc >= 4) { //Then the number of desired number, before and after, of entryies caller desires that this program \
                return from database.
                *(some2Darray + OFFSET_BEFOREDATAPOINTS*2 + 1)   = *(char **)(argv + 3);
                *(some2Darray + OFFSET_AFTERDATAPOINTS*2 + 1)   =  *(char **)(argv + 3);
            }
        } else {
            break;
        }
        if (d) {
            j=0;
            while ( *(some2Darray + j) != NULL ) {
                printf ("address %p, value: %s\t address %p, value: %s\n", (some2Darray + j), *(some2Darray + j), (some2Darray + j+1), *(some2Darray + j+1) );
                j = j + 2;
            }
            printf ("%02d. ==================================================================================================\n", k);
            k++;
        }
    } //End of for





    timings *ptrPerformanceBuffer;
    char *ptrSQL_Input_Template;
    char *cbb_results;
    FILE *fp;
    fp = fopen ("/Users/cjc/sql/testingFabricateSQL3.sql", "w");
    size_t rc = 0;

    int charactersWrittenToFile = 0;
    void *p;
    k=0;

    char **ptrMyArrays;
    fabstruct *f;  //Establish Addressability to typedef struct named fabsstruct
    size_t outBufSize;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    do {
        
        f = &fs[k]; //Get the k-th entry
        ptrMyArrays = f->fa; //Points to Preamble
        rc = f->templateSize + ((f->templateSize)<<2);
        printf ( "%02d. The size of the template is %d bytes. f->templateSize + ((f->templateSize)<<2) = %zu btyes.\n\n", k, f->templateSize, rc) ;
        cbb_results = (char *) calloc(( f->templateSize + ( (f->templateSize)<<2) ), 1); //Since we don't know if the \
        token/replacement process used to fabricate the SQL will result in result that is greater than or less than the size of \
        the input template, we will request an outbuffer size that is 50% greater than the template size. Probably more than \
        enough space.
        ptrSQL_Input_Template= (char *)calloc(f->templateSize, 1 );
        ptrPerformanceBuffer = (timings *)calloc(1,1);
        p = (char *)memcpy(ptrSQL_Input_Template, f->fa, f->templateSize ); //memcpy requires #include <string.h>
        if (d) printf ("04.%d ========> about to call fabricateSQL\n", k);
 //       rc = expectedNumberOfTokenReplacements>>1; // Let rc contain the number of template/replacement pairs.
        fabricateSQLr2(ptrPerformanceBuffer, f->fa, f->myTemplate, f->templateSize, cbb_results, &outBufSize, d);
        //    fabricateSQLr2(ptrPerformanceBuffer, &ss[0][0], ptrSQL_Input_Template, cbb_results, (int)sizeOfTemplateSS*2, d);
        //    fabricateSQLr2(ptrPerformanceBuffer, &ss[0][0], NULL, cbb_results, (int)sizeOfTemplateSS*2, d);
        //    fabricateSQLr2(NULL, &ss[0][0], NULL, cbb_results, (int)sizeOfTemplateSS*2, d);
        //    fabricateSQLr2(NULL, &ss[0][0], NULL, cbb_results, (int)NULL, d);
        if (d) printf("05.%d =======> Returned from fabricateSQL\n", k);
        if (d) printf("06.%d Call-back buffer, cbb, looks like:\n", k);
        printf  ("07.%d %s\n", k, cbb_results);
//        rc=fputs( cbb_results,  fp);
        printf("outBufSize is %zu, strlen(cbb_results) is %lu, ∆ is %lu\n", outBufSize, strlen(cbb_results), outBufSize - strlen(cbb_results));
        charactersWrittenToFile += fwrite(cbb_results, \
                        strlen(cbb_results), \
                        1, fp); // Output into the output file the first logical record, the SQL COPY statement.
        if (charactersWrittenToFile>0) {
            printf("09a.%d Got a non-zero return code from fprintf of %d \n", k, charactersWrittenToFile);
        } else {
            printf("09b.%d ERROR: got a negative return code from fwrite or %d \n)", k, charactersWrittenToFile);
        }
        if (d) printf("10.%d  Done =============================================================================\n", k);
        printf("fabricateSQL's total execution time: %lu nsec;\ntime to do constructor processing: %lu nsec;\ntime to do fabricate \
processing: %lu nsec;\ntime to do delete processing: %lu nsec.", \
               ptrPerformanceBuffer->totalTime, \
               ptrPerformanceBuffer->constructorTime, \
               ptrPerformanceBuffer->fabricateTime, \
               ptrPerformanceBuffer->deleteTime
               );
        

        free(ptrPerformanceBuffer);
        free(ptrSQL_Input_Template);
        free(cbb_results);
        k++;
    } while (k < 3);

    rc = fclose(fp);
    return (int)rc;
}
