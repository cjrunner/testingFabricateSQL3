//
//  constants.c
//  testingFabricateSQL3
//
//  Created by Clifford Campo on 8/10/20.
//  Copyright © 2020 CliffordCampo. All rights reserved.
//

extern char sqlTemplateSS[];
extern unsigned long sizeOfTemplateSS;
char sqlTemplateSS[] = {
"SELECT * FROM tbl_sun_loc_site \
WHERE lt::DATE='_DATE_' AND siteid=SITEID AND id BETWEEN \
-BEFORESUNSET + ( SELECT id FROM (SELECT *,abs(zenithdistance-SUNSETDEF) \
FROM tbl_sun_loc_site WHERE lt::DATE='_DATE_' AND siteid=SITEID AND events IS NULL AND id SRorSS (SELECT avg(id) FROM tbl_sun_loc_site \
WHERE lt::DATE='_DATE_' AND siteid=SITEID AND events IS NULL)) a WHERE abs(zenithdistance-SUNSETDEF) = \
(SELECT min(abs(zenithdistance-SUNSETDEF)) FROM tbl_sun_loc_site WHERE lt::DATE='_DATE_' AND siteid=SITEID AND events IS NULL AND id SRorSS \
(SELECT avg(id) FROM tbl_sun_loc_site where lt::DATE='_DATE_' AND siteid=SITEID AND events IS NULL))  ) \
AND     \
+AFTERSUNSET + ( SELECT id FROM (SELECT *,abs(zenithdistance-SUNSETDEF) \
FROM tbl_sun_loc_site WHERE lt::DATE='_DATE_' AND siteid=SITEID AND events IS NULL AND id SRorSS (SELECT avg(id) FROM tbl_sun_loc_site \
WHERE lt::DATE='_DATE_' AND siteid=SITEID AND events IS NULL)) a WHERE abs(zenithdistance-SUNSETDEF) = \
(SELECT min(abs(zenithdistance-SUNSETDEF)) FROM tbl_sun_loc_site WHERE lt::DATE='_DATE_' AND siteid=SITEID AND events IS NULL AND id SRorSS \
(SELECT avg(id) FROM tbl_sun_loc_site WHERE lt::DATE='_DATE_' AND siteid=SITEID AND events IS NULL))   ) \
    ORDER BY id;"
};
unsigned long sizeOfTemplateSS = sizeof(sqlTemplateSS); //Get the number of characters, including the string-terminating '\0' character.
