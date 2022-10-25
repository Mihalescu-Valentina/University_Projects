class Grade:
    def __init__(self, _assignment_id, _student_id, grade_value):
        self.__assignment_id = _assignment_id
        self.__student_id = _student_id
        self._grade_value = grade_value

    @property
    def assignment_id(self):
        return self.__assignment_id

    @property
    def student_id(self):
        return self.__student_id

    @property
    def grade_value(self):
        return self._grade_value

    def __str__(self):
        return f"Assignment_id: {self.__assignment_id }, Student_id: {self.__student_id}, Grade_value: {self._grade_value}"
    def __eq__(self, other):
        return self.assignment_id == other.assignment_id and self.student_id == other.student_id

    @grade_value.setter
    def grade_value(self,grade_val):
        self.grade_value=grade_val


