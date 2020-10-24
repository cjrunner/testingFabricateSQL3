//
//  constants.c
//  testingFabricateSQL3
//
//  Created by Clifford Campo on 8/10/20.
//  Copyright © 2020 CliffordCampo. All rights reserved.
//
#include "testingFabricateSQL3.h"

extern char sqlTemplateSS[];
extern unsigned long sizeOfTemplateSS;
extern char sqlTemplateNOON[];
extern unsigned long sizeOfTemplateNOON;
extern char *ptrSQLTemplateNOON;
extern char *ptrSQLTemplateSS;
extern char *ptrSQLTemplateSR;
extern char **fabricate2DArrays[];
extern char *ptrToDate;
extern char *ptrToSiteID;
extern char theDate[];
extern char theSiteId[];
extern fabstruct fs[];
extern unsigned long sizeOfTemplateSR;
extern const char *ptrSS;
const char *ptrSS = "SS";
char theSiteID[3] = {'0'}; //Max of 2 characters
char *ptrToSiteID = theSiteID;
char theDate[12] = {'0'}; //The date we're looking for in YYYY-MM-DD Format: 10 characters + 0x'00' c-string terminator character
char *ptrToDate = &theDate[0];
char sqlTemplateSS[] = {
"PREAMBLE SELECT * FROM tbl_sun_loc_site \
WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND id BETWEEN \
-BEFOREDATAPOINTS + ( SELECT id FROM (SELECT *,abs(FIELD-SUNSETDEF) \
FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND id SRorSS (SELECT avg(id) FROM tbl_sun_loc_site \
WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL)) a WHERE abs(FIELD-SUNSETDEF) = \
(SELECT min(abs(FIELD-SUNSETDEF)) FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND id SRorSS \
(SELECT avg(id) FROM tbl_sun_loc_site where lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL))  ) \
AND     \
+AFTERDATAPOINTS + ( SELECT id FROM (SELECT *,abs(FIELD-SUNSETDEF) \
FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND id SRorSS (SELECT avg(id) FROM tbl_sun_loc_site \
WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL)) a WHERE abs(FIELD-SUNSETDEF) = \
(SELECT min(abs(FIELD-SUNSETDEF)) FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND id SRorSS \
(SELECT avg(id) FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL))   ) \
    ORDER BY id; POSTAMBLE\n"
};
//Define a 2-dimensional array of pointers to characters used to construct the above SQL for determining sun set
char *sunSetArray[][2] = { \
    {"PREAMBLE","BEGIN; DECLARE srnoonssportal CURSOR FOR "}, \
    {"SITEID","0"}, \
    {"SOMEDATE","2020-10-19"}, \
    {"SUNSETDEF", "90.58333333"}, /* SUNSETDEF AND SUNRISEDEF are the same  */ \
    {"BEFOREDATAPOINTS", "3"}, \
    {"AFTERDATAPOINTS","3"}, \
    {"SRorSS", "SS"}, \
    {"FIELD","zenithdistance"}, \
    {"POSTAMBLE", "\nFETCH ALL srnoonssportal;\nCLOSE srnoonssportal;\nEND;"}, \
    {"Term", "Term"},
    {0,0} /* The usual list terminator */
};
unsigned long sizeOfTemplateSS = sizeof(sqlTemplateSS); //Get the number of characters, including the string-terminating '\0' character.
char *ptrSQLTemplateSS = &sqlTemplateSS[0];
char sqlTemplateNOON[] = {
    "PREAMBLE\nSELECT * FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND id BETWEEN \n\
  -BEFOREDATAPOINTS + (SELECT id FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND FIELD = \
(SELECT min(FIELD) FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL) ) \n \
AND \n \
  +AFTERDATAPOINTS + (SELECT id FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND FIELD = \
    (SELECT min(FIELD) FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL) ) ORDER BY id ; POSTAMBLE\n"};
//From the above sqlTemplateNOON[], note how the SQL comments need to be bracketed between `\n` characters to delineate the \
sql comment from the REAL SQL
unsigned long sizeOfTemplateNOON = sizeof(sqlTemplateNOON); //Get the number of characters, including the string-terminating '\0' character.
char *ptrSQLTemplateNOON = &sqlTemplateNOON[0];
//Define a 2-dimensional array of pointers to characters used to construct the above SQL for determining sun set
char *noonArray[][2] = { \
    {"PREAMBLE","BEGIN; DECLARE srnoonssportal CURSOR FOR "}, /* 00 should always be first*/ \
    {"SITEID","0"},                                           /* 01 SITEID should always be at offset */ \
    {"SOMEDATE","2020-10-19"},                                /* 02 SOMEDATE should always be at offset */ \
    {"FIELD","zenithdistance"}, /* NB: For the noon array only, let FIELD be offset 03 to take up the 3rd slot so the 4th and 5th
 slots are same as the sunrise and sunset arrays */ \
    {"BEFOREDATAPOINTS", "4"},                                /* 03 BEFOREDATAPOINTS should always be at offset */ \
    {"AFTERDATAPOINTS", "4"},                                 /* 05 AFTERDATAPOINTS should always be at offset */ \
    {"POSTAMBLE", "\nFETCH ALL srnoonssportal;\nCLOSE srnoonssportal;\nEND;\n"}, /* 06 Should be next-to-last */ \
    {"Term", "Term"},                                          /* 07 MUST always be last */ \
    {0,0} /* The usual list terminator */
};
char sqlTemplateSR[] = {
    "PREAMBLE\nSELECT * FROM tbl_sun_loc_site \
WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND id BETWEEN \n \
    -BEFOREDATAPOINTS + ( SELECT id FROM (SELECT *,abs(FIELD-SUNSETDEF) \
FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND id SRorSS (SELECT avg(id) FROM tbl_sun_loc_site \
WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL)) a WHERE abs(FIELD-SUNSETDEF) = \
(SELECT min(abs(FIELD-SUNSETDEF)) FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND id SRorSS \
(SELECT avg(id) FROM tbl_sun_loc_site where lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL))  ) \n \
AND \n \
    +AFTERDATAPOINTS + ( SELECT id FROM (SELECT *,abs(FIELD-SUNSETDEF) \
FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND id SRorSS (SELECT avg(id) FROM tbl_sun_loc_site \
WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL)) a WHERE abs(FIELD-SUNSETDEF) = \
(SELECT min(abs(FIELD-SUNSETDEF)) FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND id SRorSS \
(SELECT avg(id) FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL))   ) \
ORDER BY id; POSTAMBLE\n"
};
unsigned long sizeOfTemplateSR = sizeof(sqlTemplateSR); //Get the number of characters, including the string-terminating '\0' character.
char *ptrSQLTemplateSR = &sqlTemplateSR[0];
char *sunRiseArray[12][2] = { \
    {"PREAMBLE","BEGIN;\nDECLARE srnoonssportal CURSOR FOR\n"},  \
    {"SITEID","0"},               /* sunRiseArray[1][1] is a pointer to the desired site id   */ \
    {"SOMEDATE","2020-10-19"},    /*sunRiseArray[2][1] is a pointer to the desired date */ \
    {"SUNSETDEF", "90.58333333"}, /*sunRiseArray[3][1] is a pointer to the desired definition of sunrise or sunset. Doesn't change*/ \
    {"BEFOREDATAPOINTS", "3"},    /* sunRiseArray[4][1] is a pointer to the desired before data points  */ \
    {"AFTERDATAPOINTS","3"},      /* sunRiseArray[5][1] is a pointer to the desired after data points  */ \
    {"SRorSS", "SR"},             /* sunRiseArray[6][1] is a pointer to the desired SRorSS indicator which can be either 'R|SS*/ \
    {"FIELD","zenithdistance"},   /* sunRiseArray[7][1] is a pointer to the desired field  */ \
    {"POSTAMBLE", "\nFETCH ALL srnoonssportal;\nCLOSE srnoonssportal;\nEND;\n"}, \
    {"Term", "Term"}, \
    {0,0} /* The usual list terminator */
};
int   numberOfPairs[3]     = {       10,                     6,                10       };
char  **fabricate2DArrays[4] = { &sunRiseArray[0][0], &noonArray[0][0], &sunSetArray[0][0], 0}; //Used by test program to loop through \
the three, 2-dimensional, arrays that will be handed-off to fabricateSQLr2.dylib for testing this dylib.
/*
    -- \set :SITEID  \d+
    -- \set :DATE \d\d\d\d-\d\d-\d\d
    -- \set :BEFOREDATAPOINTS \d+
    -- \set :AFTERDATAPOINTS \d+
*/

fabstruct fs[4] = {
    {&sunRiseArray[0][0], &sqlTemplateSR[0], sizeof(sqlTemplateSR),  10}, \
    {&noonArray[0][0],    sqlTemplateNOON,   sizeof(sqlTemplateNOON), 8}, \
    {&sunSetArray[0][0],  sqlTemplateSS,     sizeof(sqlTemplateSR),  10}, \
    {0, 0, 0, 0} //List terminator.
};
fabstruct *ptr_fs = &fs[0];
