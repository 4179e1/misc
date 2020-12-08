def search (sequence, element, lower=0, upper=None):
    if upper is None : upper = len (sequence) - 1
    if lower == upper:
        if sequence[upper] == element:
            return upper
        else:
            return None
    else:
        middle = (lower + upper) // 2
        if (element > sequence[middle]):
            return search (sequence, element, middle + 1 , upper)
        else:
            return search (sequence, element, lower, middle)

if __name__ == '__main__':
    seq = [34, 67, 8, 123, 4, 100, 95]
    seq.sort()
    print (seq)
    print (search (seq, 34))
    print (search (seq, 100))
    print (search (seq, 123))
    print (search (seq, 55))
