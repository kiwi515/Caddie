class Util:
    """General utility functions"""

    @staticmethod
    def is_iterable(object) -> bool:
        """Determine whether the object is iterable"""
        try:
            iter(object)
            return True
        except TypeError:
            return False
