class Vector2f:
    def __init__(self, x: float, y: float):
        self.x = x
        self.y = y

    @classmethod
    def from_list(xy: list[float]):
        return Vector2f(xy[0], xy[1])

    def write(self, strm: "OutputStream"):
        strm.write_float(self.x)
        strm.write_float(self.y)


class Size(Vector2f):
    def __init__(self, x: float, y: float):
        super.__init__(self, x, y)

    @classmethod
    def from_list(xy: list[float]):
        return Size(xy[0], xy[1])
