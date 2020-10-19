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
extern char **fabricateArrays[];
extern fabstruct fs[];
extern unsigned long sizeOfTemplateSR;
extern const char *ptrSS;
const char *ptrSS = "SS";
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
    ORDER BY id; POSTAMBLE"
};
//Define a 2-dimensional array of pointers to characters used to construct the above SQL for determining sun set
char *sunSetArray[][2] = { \
    {"PREAMBLE","BEGIN; DECLARE srnoonssportal CURSOR FOR "}, \
    {"SITEID","17"}, \
    {"SOMEDATE","2020-10-16"}, \
    {"SUNSETDEF", "90.58333333"}, \
    {"BEFOREDATAPOINTS", "3"}, \
    {"AFTERDATAPOINTS","3"}, \
    {"SRorSS", "SR"}, \
    {"FIELD","zenithdistance"}, \
    {"POSTAMBLE", " FETCH ALL srnoonssportal; CLOSE srnoonssportal; END;"}, \
    {"Term", "Term"}
};
unsigned long sizeOfTemplateSS = sizeof(sqlTemplateSS); //Get the number of characters, including the string-terminating '\0' character.
char *ptrSQLTemplateSS = &sqlTemplateSS[0];
char sqlTemplateNOON[] = {
    "PREAMBLE SELECT * FROM tbl_sun_loc_site WHERE \
    lt::DATE='SOMEDATE' \
    AND siteid=SITEID \
    AND events IS NULL \
    AND id BETWEEN \
    -BEFOREDATAPOINTS + (SELECT id FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND FIELD = (SELECT min(FIELD) FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL) ) \n \
    -- --> -:BEFOREDATAPOINTS + ( SELECT id FROM tbl_sun_loc_site WHERE  lt::DATE=:'SOMEDATE' AND siteid=:SITEID AND events IS NULL AND ( FIELD - :SUNRISEDEF ) = ( SELECT   min( FIELD - :SUNRISEDEF ) AS \"MinMorningZD\" FROM tbl_sun_loc_site WHERE lt::DATE=:'SOMEDATE' AND siteid=:SITEID AND events IS NULL AND date_part('J', lt) <  :NOONJD )) \n \
    AND \n \
    -- --> +:AFTERDATAPOINTS + (SELECT id FROM tbl_sun_loc_site WHERE  lt::DATE=:'SOMEDATE' AND siteid=:SITEID AND events IS NULL AND (FIELD - :SUNRISEDEF) = (SELECT   min(FIELD - :SUNRISEDEF) AS \"MinMorningZD\" FROM tbl_sun_loc_site WHERE lt::DATE=:'SOMEDATE' AND siteid=:SITEID AND events IS NULL AND date_part('J', lt) <  :NOONJD )) \n \
    +AFTERDATAPOINTS + (SELECT id FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND FIELD = (SELECT min(FIELD) FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL) ) \
    ORDER BY id ; POSTAMBLE"};
//From the above sqlTemplateNOON[], note how the SQL comments need to be bracketed between `\n` characters to delineate the \
sql comment from the REAL SQL
unsigned long sizeOfTemplateNOON = sizeof(sqlTemplateNOON); //Get the number of characters, including the string-terminating '\0' character.
char *ptrSQLTemplateNOON = &sqlTemplateNOON[0];
//Define a 2-dimensional array of pointers to characters used to construct the above SQL for determining sun set
char *noonArray[][2] = { \
    {"PREAMBLE","BEGIN; DECLARE srnoonssportal CURSOR FOR "}, \
    {"SITEID","17"}, \
    {"SOMEDATE","2020-10-16"}, \
    {"FIELD","zenithdistance"}, \
    {"POSTAMBLE", " FETCH ALL srnoonssportal; CLOSE srnoonssportal; END;"}, \
    {"Term", "Term"}
};
char sqlTemplateSR[] = {
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
    ORDER BY id; POSTAMBLE"
};
unsigned long sizeOfTemplateSR = sizeof(sqlTemplateSR); //Get the number of characters, including the string-terminating '\0' character.
char *ptrSQLTemplateSR = &sqlTemplateSR[0];
char *sunRiseArray[][2] = { \
    {"PREAMBLE","BEGIN; DECLARE srnoonssportal CURSOR FOR "}, \
    {"SITEID","17"}, \
    {"SOMEDATE","2020-10-16"}, \
    {"SUNSETDEF", "90.58333333"}, \
    {"BEFOREDATAPOINTS", "3"}, \
    {"AFTERDATAPOINTS","3"}, \
    {"SRorSS", "SR"}, \
    {"FIELD","zenithdistance"}, \
    {"POSTAMBLE", " FETCH ALL srnoonssportal; CLOSE srnoonssportal; END; "}, \
    {"Term", "Term"}
};
int   numberOfPairs[3]     = {       10,                     6,                10       };
char  **fabricateArrays[3] = { &sunRiseArray[0][0], &noonArray[0][0], &sunSetArray[0][0]}; //Used by test program to loop through \
the three, 2-dimensional, arrays that will be handed-off to fabricateSQLr2.dylib for testing this dylib.
/*
    -- \set :SITEID  \d+
    -- \set :DATE \d\d\d\d-\d\d-\d\d
    -- \set :BEFOREDATAPOINTS \d+
    -- \set :AFTERDATAPOINTS \d+
*/

fabstruct fs[4] = {
    {&sunRiseArray[0][0], &sqlTemplateSR[0], sizeof(sqlTemplateSR),  10}, \
    {&noonArray[0][0],    sqlTemplateNOON,   sizeof(sqlTemplateNOON), 6}, \
    {&sunSetArray[0][0],  sqlTemplateSS,     sizeof(sqlTemplateSR),  10}, \
    {0, 0, 0, 0} //List terminator.
};
fabstruct *ptr_fs = &fs[0];
