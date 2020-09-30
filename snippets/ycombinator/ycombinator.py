# based on https://blog.klipse.tech//lambda/2016/08/07/almost-y-combinator-clojure.html

def length(lst):
    if lst:
        return 1 + length(lst[1:])
    return 0

print("length", length([1, "a", "b"]))

def generate_length(f):
    def inner(lst):
        if lst:
            return 1 + f(lst[1:])
        return 0
    return inner

print("generate_length", generate_length(length)([1, "a", "b"]))

def callmyself_length(f):
    def inner(lst):
        if lst:
            return 1 + f(f)(lst[1:])
        return 0
    return inner

print("callmyself_length", callmyself_length(callmyself_length)([1, "a", "b"]))

def length_with_ycombinator(lst):
    def ycombinator(f):
        return f(f)

    def prototype(f):
        def inner(lst):
            if lst:
                return 1 + f(f)(lst[1:])
            return 0
        return inner

    return ycombinator(prototype)(lst)

print("ycombinator_length", length_with_ycombinator([1, "a", "b"]))
