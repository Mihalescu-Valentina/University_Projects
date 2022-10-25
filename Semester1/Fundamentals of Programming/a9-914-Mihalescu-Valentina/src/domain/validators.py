import datetime

class ValidatorException(Exception):
    pass

class Validators:

  @staticmethod
  def check_id(id):
      if str(id).isdigit()==False:
          raise ValidatorException("The id must be a positive number")
      else:
          if int(id)<1:
              raise ValidatorException("The id must be a positive number")

class StudentValidators:
    @staticmethod
    def check_group(group):
        if str(group).isdigit()==False:
            raise ValidatorException("The group must be a number between 911 and 917")
        else:
            if int(group)<911 or int(group)>917:
                raise ValidatorException("The group must be a number between 911 and 917")
    @staticmethod
    def check_name(name):
        name_withoutspace=name.split(' ')
        if len(name_withoutspace)==2:
           if name_withoutspace[0].isalpha()==False or name_withoutspace[1].isalpha()==False:
             raise ValidatorException("Enter a surname and a name")
        else:
                raise ValidatorException("Enter a name and a surname both strings when adding a student")


class AssignmentValidators:
    @staticmethod
    def check_description(description):
            if not isinstance(description, str):
                raise ValidatorException("Enter a valid description! Description needs to be a string.")

    @staticmethod
    def check_date(date):
        try:
            datetime.datetime.strptime(date, '%Y-%m-%d %H:%M')
        except ValueError:
            raise ValueError("Incorrect data format, it should be YYYY-MM-DD HH:MM")

class GradeValidator:
    @staticmethod
    def validate_grade_value(grade_value):
        if grade_value < 0 or grade_value > 10:
            raise ValidatorException("Enter a valid grade with value between 1 and 10.")

    @staticmethod
    def validate_grade(grade):
        if not isinstance(grade, int):
            raise ValidatorException("Enter a valid grade! Grade needs to be an integer.")





