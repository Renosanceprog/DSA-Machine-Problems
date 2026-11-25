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