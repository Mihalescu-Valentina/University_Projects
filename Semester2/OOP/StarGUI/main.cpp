#include "StarGUI.h"
#include <QtWidgets/QApplication>
#include "AstronomerRepo.h"
#include "StarRepo.h"
#include "Service.h"
#include "SecondWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    std::string filename = "Astronomers.txt";
    AstronomerRepo arepo(filename);
    filename = "Stars.txt";
    StarRepo srepo(filename);
    Service service(arepo, srepo);
    
    auto model = new AstronomersTableModel{ service };
    std::vector<Astronomer> elems = service.getAstronomers();
    auto models = new Models();
    for (Astronomer& elem : elems)
    {   
        auto model = new AstronomersTableModel{ service };
        models->addModel(model);
        auto window = new StarGUI{service,elem,*model,*models};
        window->show();
    }
    const char* name = "second window";
    auto window2 = new SecondWindow{ name,service};
    window2->show();
    
    return a.exec();
}
