/* ex: set ts=4 et: */
/*
 * 
 */

#ifndef SQLESS_H
#define SQLESS_H

#include <stdint.h>
#include <stddef.h>

struct sqless_table
{
    const char *name;
    const struct sqless_col *col;
    size_t colcnt;
};

struct sqless
{
    int fd;
    const char *path;
    struct sqless_table tbl;
};

int sqless_open(struct sqless *, const char *);
int sqless_close(struct sqless *);

#define SQLESS_TYPE_NULL 0
#define SQLESS_TYPE_BOOL 1
#define SQLESS_TYPE_DEC  2
#define SQLESS_TYPE_STR  3

#define SQLESS_TYPE_STR_MAXLEN  ((1<<22)-1)

struct sqless_type
{
    uint32_t type:2,
             maxlen:22,
             decn:7,
             null:1;
};

struct sqless_type sqless_type_dec(uint16_t maxlen, uint8_t decn, int nullable);
struct sqless_type sqless_type_str(uint32_t maxlen, int nullable);

struct sqless_col
{
    const char *name;
    struct sqless_type type;
    uint8_t primary_key:1,
            unique:1;
};

int sqless_col_new(struct sqless_col *c,
                   const char *name,
                   const struct sqless_type,
                   const char *opts);

int sqless_table_new(struct sqless *,
                     const char *,
                     const struct sqless_col *,
                     size_t colcnt);

struct sqless_val
{
    uint32_t id;
};

int sqless_val_dec(struct sqless_val *, struct sqless_type, const char *);
int sqless_val_str(struct sqless_val *, struct sqless_type, const char *);

int sqless_insert(struct sqless *,
                  const char *,
                  const struct sqless_val *);

int sqless_select(struct sqless *,
                  const char *,
                  const struct sqless_val *);

#endif

