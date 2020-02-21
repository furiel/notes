def prepend(val, lst):
    def select(selector):
        return selector(val, lst)
    return select

def first(lst):
    def first(a, b):
        return a
    return lst(first)

def rest(lst):
    def second(a, b):
        return b
    return lst(second)

l = prepend("2", prepend("1", None))

assert first(l) == "2"
r = rest(l)
assert first(r) == "1"
assert rest(r) == None

def length(lst):
    if lst == None:
        return 0
    return 1 + length(rest(lst))

assert length(l) == 2

def map(f, lst):
    if lst == None:
        return None
    return prepend(f(first(lst)), map(f, rest(lst)))

def log(x):
    print(x)
    return x
map(log, l)
