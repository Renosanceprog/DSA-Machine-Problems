import tkinter as tk
from tkinter import ttk

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

    def search_with_probes(self, key: int) -> tuple[int, list[int]]:
        start = self._hash(key)
        probed = []

        for i in range(SIZE):
            pos = (start + i) % SIZE
            probed.append(pos)
            val = self.table[pos]

            if val == EMPTY:
                return -1, probed
            if val == key:
                return pos, probed

        return -1, probed

    def search(self, key: int) -> int:
        pos, _ = self.search_with_probes(key)
        return pos

    def remove(self, key: int) -> None:
        pos = self.search(key)
        if pos == -1:
            return

        self.table[pos] = DELETED


class MySet:
    def __init__(self):
        self._ht = HashTable()
        self._count = 0

    def elements(self) -> list[int]:
        return [
            val for val in self._ht.table
            if val is not EMPTY and val != DELETED
        ]

    def is_member(self, x: int) -> bool:
        return self._ht.search(x) != -1

    def add(self, x: int) -> bool:
        if self._count == SIZE or x is None or x == DELETED:
            return False
        if self.is_member(x):
            return False

        self._ht.insert(x)
        if self._is_inserted(x):
            self._count += 1
            return True
        return False

    def _is_inserted(self, x: int) -> bool:
        return self._ht.search(x) != -1

    def remove(self, x: int) -> bool:
        if not self.is_member(x):
            return False

        self._ht.remove(x)
        self._count -= 1
        return True

    def set_union(self, other: "MySet") -> "MySet":
        result = MySet()
        for val in self.elements():
            result.add(val)
        for val in other.elements():
            result.add(val)
        return result

    def set_intersection(self, other: "MySet") -> "MySet":
        result = MySet()
        for val in self.elements():
            if other.is_member(val):
                result.add(val)
        return result

    def set_difference(self, other: "MySet") -> "MySet":
        result = MySet()
        for val in self.elements():
            if not other.is_member(val):
                result.add(val)
        return result


class SetApp:
    def __init__(self, root: tk.Tk):
        self.root = root
        self.root.title("SET ADT OPERATIONS")

        self.selected_set = tk.StringVar(value="A")
        self.last_op_label = "None"
        self.probed_slots: list[int] = []

        self._build_ui()
        self._load_sample()
        self._refresh()

    def _load_sample(self) -> None:
        self.set_a = MySet()
        self.set_b = MySet()

        for x in (10, 20, 30, 40):
            self.set_a.add(x)
        for x in (30, 40, 50, 60):
            self.set_b.add(x)

        self.set_c = self.set_a.set_union(self.set_b)
        self.last_op_label = "Sample Loaded (Union A ∪ B -> C)"
        self.probed_slots = []

    def _build_ui(self) -> None:
        pad = {"padx": 10, "pady": 6}

        tk.Label(self.root, text="SET ADT OPERATIONS", font=("Arial", 13, "bold")).pack(pady=(10, 4))

        # Select Set to Modify
        sel_frame = tk.LabelFrame(self.root, text="Select Set to Modify")
        sel_frame.pack(fill="x", **pad)
        tk.Radiobutton(sel_frame, text="Set A", variable=self.selected_set, value="A", command=self._on_set_change).pack(side="left", padx=12, pady=4)
        tk.Radiobutton(sel_frame, text="Set B", variable=self.selected_set, value="B", command=self._on_set_change).pack(side="left", padx=12, pady=4)

        # Element input
        elem_frame = tk.LabelFrame(self.root, text="Element")
        elem_frame.pack(fill="x", **pad)
        tk.Label(elem_frame, text="Enter integer:").pack(side="left", padx=(10, 6), pady=6)
        self.entry = tk.Entry(elem_frame, width=16)
        self.entry.pack(side="left", pady=6)
        self.entry.bind("<Return>", lambda _e: self.on_add())

        # Basic Set Operations
        basic_frame = tk.LabelFrame(self.root, text="Basic Set Operations")
        basic_frame.pack(fill="x", **pad)
        tk.Button(basic_frame, text="Add", width=9, command=self.on_add).pack(side="left", padx=6, pady=6)
        tk.Button(basic_frame, text="Delete", width=9, command=self.on_delete).pack(side="left", padx=6, pady=6)
        tk.Button(basic_frame, text="Search", width=9, command=self.on_search).pack(side="left", padx=6, pady=6)
        tk.Button(basic_frame, text="Display", width=9, command=self.on_display).pack(side="left", padx=6, pady=6)
        tk.Button(basic_frame, text="Clear Set", width=10, command=self.on_clear_set).pack(side="left", padx=6, pady=6)

        # Set Operations
        set_op_frame = tk.LabelFrame(self.root, text="Set Operations")
        set_op_frame.pack(fill="x", **pad)
        tk.Button(set_op_frame, text="Union", width=12, command=lambda: self.on_set_op("UNION")).pack(side="left", padx=6, pady=6)
        tk.Button(set_op_frame, text="Intersection", width=12, command=lambda: self.on_set_op("INTERSECTION")).pack(side="left", padx=6, pady=6)
        tk.Button(set_op_frame, text="Difference", width=12, command=lambda: self.on_set_op("DIFFERENCE")).pack(side="left", padx=6, pady=6)

        # Hash Table Visualization
        vis_frame = tk.LabelFrame(self.root, text="Hash Table Visualization")
        vis_frame.pack(fill="both", expand=True, **pad)
        self.tree = ttk.Treeview(vis_frame, columns=("index", "a", "b", "c"), show="headings", height=SIZE)
        for col, title in [("index", "Index"), ("a", "A"), ("b", "B"), ("c", "C")]:
            self.tree.heading(col, text=title)
            self.tree.column(col, width=85, anchor="center")
        self.tree.tag_configure("probed", background="#fff3cd")
        self.tree.pack(fill="both", expand=True, padx=6, pady=6)

        # Set Contents / Operation Results
        res_frame = tk.LabelFrame(self.root, text="Set Contents / Operation Results")
        res_frame.pack(fill="x", **pad)
        self.output = tk.Text(res_frame, height=8, width=58, state="disabled")
        self.output.pack(fill="x", padx=6, pady=6)

        # Bottom buttons
        bot_frame = tk.Frame(self.root)
        bot_frame.pack(fill="x", padx=10, pady=(2, 10))
        tk.Button(bot_frame, text="Clear Output", width=12, command=self.on_clear_output).pack(side="left")
        tk.Button(bot_frame, text="Exit", width=10, command=self.root.destroy).pack(side="right")

    def _on_set_change(self) -> None:
        self.probed_slots = []
        self._refresh()

    def _active_set(self) -> tuple[str, MySet]:
        name = self.selected_set.get()
        return name, (self.set_a if name == "A" else self.set_b)

    def _read_int(self) -> int | None:
        raw = self.entry.get().strip()
        try:
            return int(raw)
        except ValueError:
            self._log("Invalid input: please enter an integer.")
            return None

    def _fmt_slot(self, val) -> str:
        if val is EMPTY:
            return "EMPTY"
        return str(val)

    def _fmt_set(self, s: MySet) -> str:
        elems = s.elements()
        return "{" + ", ".join(str(x) for x in elems) + "}"

    def _log(self, msg: str) -> None:
        self.output.config(state="normal")
        self.output.insert("end", msg + "\n")
        self.output.see("end")
        self.output.config(state="disabled")

    def _refresh(self) -> None:
        for row in self.tree.get_children():
            self.tree.delete(row)

        for i in range(SIZE):
            tags = ("probed",) if i in self.probed_slots else ()
            self.tree.insert(
                "",
                "end",
                values=(
                    i,
                    self._fmt_slot(self.set_a._ht.table[i]),
                    self._fmt_slot(self.set_b._ht.table[i]),
                    self._fmt_slot(self.set_c._ht.table[i]),
                ),
                tags=tags,
            )

        summary = (
            f"SET A: {self._fmt_set(self.set_a)}\n"
            f"SET B: {self._fmt_set(self.set_b)}\n"
            f"SET C: {self._fmt_set(self.set_c)}\n"
            f"Current Set: {self.selected_set.get()} (Last Op: {self.last_op_label}) | "
            f"Set A Count: {self.set_a._count} | Set B Count: {self.set_b._count} | Set C Count: {self.set_c._count}\n"
        )
        self.output.config(state="normal")
        current = self.output.get("1.0", "end")
        lines = current.splitlines()
        logs = [ln for ln in lines if ln.startswith(("[", "Invalid"))]
        self.output.delete("1.0", "end")
        self.output.insert("1.0", summary + ("\n".join(logs) + "\n" if logs else ""))
        self.output.see("end")
        self.output.config(state="disabled")

    def on_add(self) -> None:
        val = self._read_int()
        if val is None:
            return
        name, s = self._active_set()
        self.probed_slots = []
        self.last_op_label = f"Add({val}) on Set {name}"
        if s.add(val):
            self._log(f"[Add] {val} added to Set {name}.")
        else:
            self._log(f"[Add] Could not add {val} to Set {name} (duplicate or full).")
        self.entry.delete(0, "end")
        self._refresh()

    def on_delete(self) -> None:
        val = self._read_int()
        if val is None:
            return
        name, s = self._active_set()
        self.probed_slots = []
        self.last_op_label = f"Delete({val}) on Set {name}"
        if s.remove(val):
            self._log(f"[Delete] {val} removed from Set {name}.")
        else:
            self._log(f"[Delete] {val} not found in Set {name}.")
        self.entry.delete(0, "end")
        self._refresh()

    def on_search(self) -> None:
        val = self._read_int()
        if val is None:
            return
        name, s = self._active_set()
        pos, probed = s._ht.search_with_probes(val)
        self.probed_slots = probed
        self.last_op_label = f"Search({val}) on Set {name}"
        if pos != -1:
            self._log(f"[Search] {val} FOUND at index {pos} in Set {name}. Probed: {probed}")
        else:
            self._log(f"[Search] {val} NOT in Set {name}. Probed: {probed}")
        self._refresh()

    def on_display(self) -> None:
        name, s = self._active_set()
        self.probed_slots = []
        self.last_op_label = f"Display Set {name}"
        self._log(f"[Display] Set {name}: {self._fmt_set(s)} (count: {s._count})")
        self._refresh()

    def on_clear_set(self) -> None:
        name, _ = self._active_set()
        self.probed_slots = []
        if name == "A":
            self.set_a = MySet()
        else:
            self.set_b = MySet()
        self.last_op_label = f"Clear Set {name}"
        self._log(f"[Clear] Set {name} cleared.")
        self._refresh()

    def on_set_op(self, op: str) -> None:
        self.probed_slots = []
        if op == "UNION":
            self.set_c = self.set_a.set_union(self.set_b)
            self.last_op_label = "Union (A ∪ B -> C)"
        elif op == "INTERSECTION":
            self.set_c = self.set_a.set_intersection(self.set_b)
            self.last_op_label = "Intersection (A ∩ B -> C)"
        else:
            self.set_c = self.set_a.set_difference(self.set_b)
            self.last_op_label = "Difference (A - B -> C)"
        self._log(f"[{op.title()}] Result stored in Set C: {self._fmt_set(self.set_c)}")
        self._refresh()

    def on_clear_output(self) -> None:
        self.output.config(state="normal")
        self.output.delete("1.0", "end")
        self.output.config(state="disabled")
        self._refresh()


if __name__ == "__main__":
    root = tk.Tk()
    app = SetApp(root)
    root.mainloop()
