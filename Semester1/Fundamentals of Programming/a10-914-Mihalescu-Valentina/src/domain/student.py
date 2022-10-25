class Student:
    def __init__(self, _student_id, name, group):
        self.__student_id = _student_id
        self._name = name
        self._group = group

    @property
    def student_id(self):
        return self.__student_id

    @property
    def name(self):
        return self._name

    @property
    def group(self):
        return self._group

    def __str__(self):
        return f"Student_id: {self.__student_id}, Name: {self._name}, Group: {self._group}"

    def __eq__(self, other):
        return self.__student_id==other.student_id