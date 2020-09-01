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
extern unsigned long sizeOfTemplateSR;
extern const char *ptrSS;
const char *ptrSS = "SS";
char sqlTemplateSS[] = {
"SELECT * FROM tbl_sun_loc_site \
WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND id BETWEEN \
-BEFOREDATAPOINTS + ( SELECT id FROM (SELECT *,abs(zenithdistance-SUNSETDEF) \
FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND id SRorSS (SELECT avg(id) FROM tbl_sun_loc_site \
WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL)) a WHERE abs(zenithdistance-SUNSETDEF) = \
(SELECT min(abs(zenithdistance-SUNSETDEF)) FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND id SRorSS \
(SELECT avg(id) FROM tbl_sun_loc_site where lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL))  ) \
AND     \
+AFTERDATAPOINTS + ( SELECT id FROM (SELECT *,abs(zenithdistance-SUNSETDEF) \
FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND id SRorSS (SELECT avg(id) FROM tbl_sun_loc_site \
WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL)) a WHERE abs(zenithdistance-SUNSETDEF) = \
(SELECT min(abs(zenithdistance-SUNSETDEF)) FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND id SRorSS \
(SELECT avg(id) FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL))   ) \
    ORDER BY id;"
};
unsigned long sizeOfTemplateSS = sizeof(sqlTemplateSS); //Get the number of characters, including the string-terminating '\0' character.
char *ptrSQLTemplateSS = &sqlTemplateSS[0];
char sqlTemplateNOON[] = {
    "SELECT * FROM tbl_sun_loc_site WHERE \
    lt::DATE='SOMEDATE' \
    AND siteid=SITEID \
    AND events IS NULL \
    AND id BETWEEN \
    -BEFOREDATAPOINTS + (SELECT id FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND zenithdistance = (SELECT min(zenithdistance) FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL) ) \n \
    -- -- -:BEFOREDATAPOINTS + ( SELECT id FROM tbl_sun_loc_site WHERE  lt::DATE=:'SOMEDATE' AND siteid=:SITEID AND events IS NULL AND ( zenithdistance - :SUNRISEDEF ) = ( SELECT   min( zenithdistance - :SUNRISEDEF ) AS \"MinMorningZD\" FROM tbl_sun_loc_site WHERE lt::DATE=:'SOMEDATE' AND siteid=:SITEID AND events IS NULL AND date_part('J', lt) <  :NOONJD )) \n \
    AND \n \
    -- -- +:AFTERDATAPOINTS + (SELECT id FROM tbl_sun_loc_site WHERE  lt::DATE=:'SOMEDATE' AND siteid=:SITEID AND events IS NULL AND (zenithdistance - :SUNRISEDEF) = (SELECT   min(zenithdistance - :SUNRISEDEF) AS \"MinMorningZD\" FROM tbl_sun_loc_site WHERE lt::DATE=:'SOMEDATE' AND siteid=:SITEID AND events IS NULL AND date_part('J', lt) <  :NOONJD )) \n \
    +AFTERDATAPOINTS + (SELECT id FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND zenithdistance = (SELECT min(zenithdistance) FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL) ) \
    ORDER BY id ; "};
//From the above sqlTemplateNOON[], note how the SQL comments need to be bracketed between `\n` characters to delineate the \
sql comment from the REAL SQL
unsigned long sizeOfTemplateNOON = sizeof(sqlTemplateNOON); //Get the number of characters, including the string-terminating '\0' character.
char *ptrSQLTemplateNOON = &sqlTemplateNOON[0];

char sqlTemplateSR[] = {
    "SELECT * FROM tbl_sun_loc_site \
    WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND id BETWEEN \
    -BEFOREDATAPOINTS + ( SELECT id FROM (SELECT *,abs(zenithdistance-SUNSETDEF) \
    FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND id SRorSS (SELECT avg(id) FROM tbl_sun_loc_site \
    WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL)) a WHERE abs(zenithdistance-SUNSETDEF) = \
    (SELECT min(abs(zenithdistance-SUNSETDEF)) FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND id SRorSS \
    (SELECT avg(id) FROM tbl_sun_loc_site where lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL))  ) \
    AND     \
    +AFTERDATAPOINTS + ( SELECT id FROM (SELECT *,abs(zenithdistance-SUNSETDEF) \
    FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND id SRorSS (SELECT avg(id) FROM tbl_sun_loc_site \
    WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL)) a WHERE abs(zenithdistance-SUNSETDEF) = \
    (SELECT min(abs(zenithdistance-SUNSETDEF)) FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL AND id SRorSS \
    (SELECT avg(id) FROM tbl_sun_loc_site WHERE lt::DATE='SOMEDATE' AND siteid=SITEID AND events IS NULL))   ) \
    ORDER BY id;"
};
unsigned long sizeOfTemplateSR = sizeof(sqlTemplateSR); //Get the number of characters, including the string-terminating '\0' character.
char *ptrSQLTemplateSR = &sqlTemplateSR[0];
/*
    -- \set :SITEID  \d+
    -- \set :DATE \d\d\d\d-\d\d-\d\d
    -- \set :BEFOREDATAPOINTS \d+
    -- \set :AFTERDATAPOINTS \d+
*/
