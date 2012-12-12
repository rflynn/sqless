
reasoning about values

types:
    0      NULL
    1      bool
    2(n,m) decimal(n,m)
    3      binary string

ordinality:
    NULL < INT_MIN < -1 < 0 < 1 < INT_MAX
    NULL < "" < "\u0000" < "\uffff"

equality:
    NULL == NULL
    true == true
    false == false
    0.0 == 0.0
    '' == ''

decimal(8,3)
    "00000000.000"
    [{0,0},{0,0},{0,0},{0,0}.{0,0},{0,-}]

derived values:
    datetime
    unixtime

implementation:
    values in one giant set:
        id corresponds to [{offset,len,refcnt},...]
        blob: giant blob of possibly overlapping values
            int len
            uint8_t val[len]
    tables reference values by id
        special ids:
            0 NULL
        except bools, which are packed together in the row
            ...which makes indexing them hard

