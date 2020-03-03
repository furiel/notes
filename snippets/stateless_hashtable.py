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

def multi_extend_table(table, *args):
    if not args:
        return table

    key = args[0]
    value = args[1]
    rest = args[2:]

    return extend_table(multi_extend_table(table, *rest), key, value)

t2 = multi_extend_table(new_table(), "1", "a", "2", "b", "3", "c")
assert t2("1") == "a"
assert t2("2") == "b"
assert t2("3") == "c"

import pytest
with pytest.raises(Exception):
    t2("none")
