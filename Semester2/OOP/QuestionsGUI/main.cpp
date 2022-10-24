#include "QuestionsGUI.h"
#include <QtWidgets/QApplication>
#include "Service.h"
#include "UserRepo.h"
#include "QuestionRepo.h"
#include "AnswerRepo.h"
#include "SecondWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::string filename = "Users.txt";
    UserRepo urepo(filename);
    filename = "Questions.txt";
    QuestionRepo qrepo(filename);
    filename = "Answers.txt";
    AnswerRepo arepo(filename);
    Service service(urepo, qrepo,arepo);
    std::vector<User> elems = service.getUsers();
    for (User& elem : elems)
    {
        auto window = new QuestionsGUI{ service,elem };
        window->show();
    }
    const char* name = "second window";
    auto window2 = new SecondWindow{name,service};
    window2->show();
    return QApplication::exec();
}
