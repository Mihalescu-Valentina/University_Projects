from src.repository.assignment_repo import AssignmentRepository, AssignmentFileRepository, AssignmentBinRepository
from src.repository.student_repo import StudentRepository, StudentFileRepository, StudentBinRepository
from src.ui.start import Console
from src.services.assignment_service import AssignmentService
from src.services.student_service import StudentService
from src.repository.grade_repo import GradeRepository, GradeFileRepository, GradeBinRepository
from src.services.grade_service import GradeService
from src.services.undo_redo import UndoService
from configparser import ConfigParser
if __name__ == '__main__':
    config = ConfigParser()
    config.read("data/settings.properties")
    choice_repo = config.get("Settings","repository")
    students =config.get("Settings","students")
    assignments = config.get("Settings","assignments")
    grades = config.get("Settings","grades")

    if choice_repo == "inmemory":
        student_repo=StudentRepository()
        assignment_repo=AssignmentRepository()
        grade_repo=GradeRepository(student_repo,assignment_repo)

    elif choice_repo =="textfiles":
        assignment_repo = AssignmentFileRepository(assignments)
        student_repo = StudentFileRepository(students)
        grade_repo = GradeFileRepository(grades,student_repo, assignment_repo)

    elif choice_repo == "binaryfiles":
        assignment_repo=AssignmentBinRepository(assignments)
        student_repo =StudentBinRepository(students)
        grade_repo= GradeBinRepository(grades,student_repo,assignment_repo)


    undo_service=UndoService(student_repo,assignment_repo,grade_repo)
    console = Console(StudentService(student_repo), AssignmentService(assignment_repo),
                      GradeService(grade_repo, student_repo, assignment_repo),undo_service)

    console.read_input()
