
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "sqless.h"

int sqless_open(struct sqless *db, const char *path)
{
    db->path = path;
    db->fd = creat(path, 0644);
    return db->fd > 0;
}

int sqless_close(struct sqless *db)
{
    return 0;
}

struct sqless_type sqless_type_str(uint32_t maxlen, int nullable)
{
    struct sqless_type t;
    t.type = SQLESS_TYPE_STR;
    assert(maxlen <= SQLESS_TYPE_STR_MAXLEN);
    t.maxlen = maxlen;
    t.decn = 0;
    t.null = !!nullable;
    return t;
}

struct sqless_type sqless_type_dec(uint16_t maxlen, uint8_t decn, int nullable)
{
    struct sqless_type t;
    t.type = SQLESS_TYPE_DEC;
    assert(maxlen <= 22);
    t.maxlen = maxlen;
    t.decn = decn;
    t.null = !!nullable;
    return t;
}

int sqless_col_new(struct sqless_col *c,
                   const char *name,
                   const struct sqless_type type,
                   const char *opts)
{
    c->name = name;
    c->type = type;
    c->primary_key = !!strcmp(opts, "primary key");
    c->unique = 0;
    return 1;
}

int sqless_table_new(struct sqless *db,
                     const char *name,
                     const struct sqless_col *col,
                     size_t colcnt)
{
    db->tbl.name = name;
    db->tbl.col = col;
    db->tbl.colcnt = colcnt;
    return 1;
}

int sqless_val_dec(struct sqless_val *v,
                   struct sqless_type type,
                   const char *str)
{
    return 0;
}

int sqless_val_str(struct sqless_val *v,
                   struct sqless_type type,
                   const char *str)
{
    return 0;
}

int sqless_insert(struct sqless *db,
                  const char *table,
                  const struct sqless_val *v)
{
    return 0;
}

int sqless_select(struct sqless *db,
                  const char *table,
                  const struct sqless_val *v)
{
    return 0;
}

