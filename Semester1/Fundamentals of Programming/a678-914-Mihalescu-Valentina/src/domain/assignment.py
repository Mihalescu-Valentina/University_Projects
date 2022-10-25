class Assignment:
    def __init__(self, _assignment_id, description, deadline):
        self.__assignment_id = _assignment_id
        self._description = description
        self._deadline = deadline

    @property
    def assignment_id(self):
        return self.__assignment_id

    @property
    def description(self):
        return self._description

    @property
    def deadline(self):
        return self._deadline

    def __str__(self):
        return f"Assignment_id: {self.__assignment_id}, Description: {self._description}, Deadline: {self._deadline}"

    def __eq__(self, other):
        return self.__assignment_id==other.assignment_id
