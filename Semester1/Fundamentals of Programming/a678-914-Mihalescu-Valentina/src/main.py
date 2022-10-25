from src.repository.assignment_repo import AssignmentRepository, AssignmentFileRepository, AssignmentBinRepository
from src.repository.student_repo import StudentRepository, StudentFileRepository, StudentBinRepository
from src.ui.start import Console
from src.services.assignment_service import AssignmentService
from src.services.student_service import StudentService
from src.repository.grade_repo import GradeRepository, GradeFileRepository, GradeBinRepository
from src.services.grade_service import GradeService
from src.services.undo_redo import UndoService

if __name__ == '__main__':
    assignment_repo = AssignmentBinRepository()
    student_repo = StudentBinRepository()
    grade_repo = GradeBinRepository(student_repo, assignment_repo)
    undo_service=UndoService(student_repo,assignment_repo,grade_repo)
    console = Console(StudentService(student_repo), AssignmentService(assignment_repo),
                      GradeService(grade_repo, student_repo, assignment_repo),undo_service)

    console.read_input()
