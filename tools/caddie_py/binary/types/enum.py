from caddie_py.binary.types.primitive import Primitive


class Enum(Primitive):
    """Primitive member associated with an enum"""

    def __init__(self, underlying_type: str, name: str, arr: str = None, value=None):
        super().__init__(underlying_type, name, arr, value)
        self.__enum = self.VALUES.copy()

    def set_value(self, data):
        """Set member value"""
        assert data in self.__enum, f"Invalid enum value: {data} not in {self.__class__.__name__}"
        Primitive.set_value(self.__enum[data])
