def oddp(num):
    return num % 2 == 1

def identity(x):
    return x

def constantly(x):
    def inner():
        return x
    return inner

def find_first_odd(l, success, failure):
    if not l:
        return failure()

    first = l[0]
    if oddp(first):
        return success(first)

    return find_first_odd(l[1:], success, failure)

# print(find_first_odd([0, 2, 3, 1, 4], identity, constantly(None)))
# print(find_first_odd([0, 2], identity, constantly(None)))

# --------------------------

def collect_odd(l, success):
    if not l:
        return success([])
    first = l[0]

    if oddp(first):
        def new_success(l):
            l.append(first)
            return success(l)
        return collect_odd(l[1:], new_success)
    else:
        return collect_odd(l[1:], success)

# print(collect_odd([1, 2, 3, 4], identity))
# print(collect_odd([2, 4], identity))

# -----------------------

def subseq_with_sum(sum, l, success, failure):
    if sum == 0:
        return success([])

    candidates = list(filter(lambda x: x <= sum, l))
    if not candidates:
        return failure()

    first_candidate = candidates[0]
    rest_candidates = candidates[1:]

    def new_success(l):
        l.append(first_candidate)
        return success(l)

    def new_failure():
        return subseq_with_sum(sum, rest_candidates, success, failure)

    return subseq_with_sum(sum-first_candidate, rest_candidates, new_success, new_failure)

# print(subseq_with_sum(10, [1, 2, 5, 6, 7], identity, constantly([])))
# print(subseq_with_sum(10, [1, 2, 5, 6], identity, constantly([])))
