class Node:
    left::Node = None
    right::Node = None

    def __init__(self):
        pass

    def depth(self)::int:
        if self.left is None:
            left = 0
        else:
            left = self.left.depth()
        if self.right is None:
            right = 0
        else:
            right = self.right.depth()

        return left + 1 if left > right else right + 1


root = Node()
root.left = Node()
root.right = Node()


print root.depth()
