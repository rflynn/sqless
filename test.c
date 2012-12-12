/* ex: set ts=4 et: */
/*
 *
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "sqless.h"

int main(void)
{
    struct sqless db;
    printf("opening...\n");
    if (sqless_open(&db, "test.sqless"))
    {
        struct sqless_col c[2];
        sqless_col_new(c+0, "id", sqless_type_dec(8,0,1), "primary key");
        sqless_col_new(c+1, "str", sqless_type_str(5,0), "");
        printf("table...\n");
        if (sqless_table_new(&db, "foo", c, 2))
        {
            struct sqless_val v[2];
            sqless_val_dec(v+0, c[0].type,"1.23");
            sqless_val_str(v+1, c[0].type,"abc");
            printf("insert...\n");
            if (sqless_insert(&db, "foo", v))
            {
                struct sqless_val v2[2];
                printf("select...\n");
                if (sqless_select(&db, "foo", v2))
                    assert(0 == memcmp(v, v2, sizeof v));
            }
        }
        sqless_close(&db);
    }
    return 0;
}
