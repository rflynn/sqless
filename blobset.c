/* ex: set ts=4 et: */
/*
 * blobset manages all database values
 * - storage
 * - retrieval
 * - cmp
 *
 */

#include <stdint.h>
#include <sys/uio.h>

struct blobitem
{
    uint32_t offset;
    uint16_t len;
    uint16_t refcnt;
};

struct blobset
{
    uint32_t itemcnt;
    uint32_t blobsize;
    struct blobitem *item;
    uint8_t *blob;
};

struct blobset * blobset_new(void)
{
    struct blobset *s = malloc(sizeof *s);
    if (s)
    {
        s->itemcnt = 1;
        s->blobsize = 0;
        s->item = malloc(sizeof *s->item);
        if (!s->item)
        {
            free(s);
            return 0;
        }
        /* NULL item occupies id 0 */
        s->item[0].offset = 0;
        s->item[0].len = 0;
        s->item[0].refcnt = UINT16_MAX;
        s->blob = 0;
    }
    return s;
}

uint64_t blobset_serialize(const struct blobset *s, int fd)
{
    const struct iovec v[] =
    {
        { "sqless\x00\x00", 8                     },
        { &s->itemcnt, sizeof s->itemcnt          },
        { &s->blobsize, sizeof s->blobsize        },
        { s->item, s->itemcnt * (sizeof *s->item) },
        { s->blob, s->blobsize                    }
    };
    return writev(fd, v, sizeof v / sizeof v[0]);
}

uint64_t blobset_deserialize(struct blobset *s, int fd)
{
    uint8_t header[8];
    const struct iovec v[] =
    {
        { header, sizeof header                   },
        { &s->itemcnt, sizeof s->itemcnt          },
        { &s->blobsize, sizeof s->blobsize        },
        { s->item, s->itemcnt * (sizeof *s->item) },
        { s->blob, s->blobsize                    }
    };
    return readv(fd, v, sizeof v / sizeof v[0]);
}

int blobset_add(struct blobset *s, const uint8_t * const val, uint16_t len)
{
    uint8_t *tmp;
    if (UINT32_MAX - s->blobsize < len)
    {
        return 0; /* blob full! */
    }
    tmp = realloc(s->blob, s->blobsize + len);
    if (!tmp)
    {
        return 0;
    }
    memcpy(s->blob, val, len);
    tmp = realloc(s->item, (sizeof *s->item) * (s->itemcnt + 1));
    if (!tmp)
    {
        return 0;
    }
    s->item[s->itemcnt].offset = s->blobsize;
    s->item[s->itemcnt].len = len;
    s->item[s->itemcnt].refcnt = 1;
    s->itemcnt++;
    s->blobsize += len;
    return 1;
}

int blobset_cmp(const struct blobset *s, uint32_t id1, uint32_t id2)
{
    if (id1 == id2)
    {
        return 0;
    }
    {
        uint16_t id1len = b->item[id1].len;
        uint16_t id2len = b->item[id1].len;
        uint16_t minlen = id1len < id2len ? id1len : id2len;
        int cmp = memcmp(b->blob + b->item[id1].offset,
                         b->blob + b->item[id2].offset, minlen);
        if (cmp)
        {
            return cmp;
        }
        return id1len < id2len ? 1 : -1;
    }
}

