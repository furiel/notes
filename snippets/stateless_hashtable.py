# Line by line transformation from The Seasoned Schemer.

def new_table():
    def notfound(_):
        raise Exception("not found")
    return notfound

def extend_table(table, key, value):
    def new_table(k):
        if k == key:
            return value
        else:
            return table(k)
    return new_table

t = extend_table(extend_table(new_table(), "1", "a"), "2", "b")

assert t("1") == "a"
assert t("2") == "b"

import pytest
with pytest.raises(Exception):
    t("none")
