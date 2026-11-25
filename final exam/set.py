SIZE = 10
EMPTY = None
DELETED = "DELETED"


class HashTable:
    def __init__(self):
        self.table = [EMPTY] * SIZE

    def _hash(self, key: int) -> int:
        return key % SIZE

    def insert(self, key: int) -> None:
        if key is None or key == DELETED:
            return

        start = self._hash(key)
        deleted_pos = -1

        for i in range(SIZE):
            pos = (start + i) % SIZE
            val = self.table[pos]

            if val == key:
                return

            if val == DELETED and deleted_pos == -1:
                deleted_pos = pos

            if val == EMPTY:
                target = deleted_pos if deleted_pos != -1 else pos
                self.table[target] = key
                return

        if deleted_pos != -1:
            self.table[deleted_pos] = key
        else:
            pass

    def search(self, key: int) -> int:
        start = self._hash(key)

        for i in range(SIZE):
            pos = (start + i) % SIZE
            val = self.table[pos]

            if val == EMPTY:
                return -1
            if val == key:
                return pos

        return -1

    def remove(self, key: int) -> None:
        pos = self.search(key)
        if pos == -1:
            return

        self.table[pos] = DELETED


class MySet:
    def __init__(self):
        self._ht = HashTable()
        self._count = 0

    def _elements(self) -> list[int]:
        return [
            val for val in self._ht.table
            if val is not EMPTY and val != DELETED
        ]

    def _is_member(self, x: int) -> bool:
        return self._ht.search(x) != -1

    def add(self, x: int) -> bool:
        if self._count == SIZE or x is None or x == DELETED:
            return False
        if self._is_member(x):
            return False

        self._ht.insert(x)
        if self._is_member(x):
            self._count += 1
            return True
        return False

    def remove(self, x: int) -> bool:
        if not self._is_member(x):
            return False

        self._ht.remove(x)
        self._count -= 1
        return True

    def display_set(self) -> None:
        items = ", ".join(str(v) for v in self._elements())
        print(f"{{{items}}} ctr = {self._count}", end="")

    def set_union(self, other: "MySet") -> "MySet":
        result = MySet()
        for val in self._elements():
            result.add(val)
        for val in other._elements():
            result.add(val)
        return result

    def set_intersection(self, other: "MySet") -> "MySet":
        result = MySet()
        for val in self._elements():
            if other._is_member(val):
                result.add(val)
        return result

    def set_difference(self, other: "MySet") -> "MySet":
        result = MySet()
        for val in self._elements():
            if not other._is_member(val):
                result.add(val)
        return result