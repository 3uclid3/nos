class ArrayPrinter:
    class _iterator:
        def __init__(self, begin, end, size, capacity):
            self.it = begin
            self.end = end
            self.size = size
            self.sizeShown = 0
            self.capacity = capacity
            self.capacityShown = 0
            self.count = 0

        def __iter__(self):
            return self

        def __next__(self):
            if self.sizeShown == 0:
                self.sizeShown = 1
                return '[size]', int(self.size)
            if self.capacityShown == 0:
                self.capacityShown = 1
                return '[capacity]', int(self.capacity)
            count = self.count
            self.count = count + 1
            if self.it == self.end:
                raise StopIteration
            elt = self.it.dereference()
            self.it = self.it + 1
            return '[%d]' % count, elt

    def __init__(self, val):
        self.val = val
        self.begin = val['_buffer'].cast(self.val.type.template_argument(0).pointer())
        self.end = self.begin + int(val['_size'])

    def children(self):
        return self._iterator(self.begin, self.end, self.val['_size'], self.val['_capacity'])

    def to_string(self):
        return '%s of size %d, capacity %d' % (str(self.val.type), int(self.val['_size']), int(self.val['_capacity']))

    def display_hint(self):
        return 'array'


def nos_lookup_type(val):
    if 'Array' in str(val.type): return ArrayPrinter(val)
    return None


gdb.pretty_printers.append(nos_lookup_type)
