class Vector:
    """Vector represents an ordered sequence of elements."""

    def __init__(self, elements):
        self.elements = elements

    # Returns the result of multiplying the ith element of this vector
    # with the ith element of the given vector
    def multiply(self, other):
        if len(self.elements) != len(other.elements):
            raise ValueError("Vectors must have the same length")

        return Vector([a * b for a, b in zip(self.elements, other.elements)])
