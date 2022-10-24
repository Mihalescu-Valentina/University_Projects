#include "DynamicVector.h"
#include "Event.h"
#include "Comparator.h"
#include <crtdbg.h>
#include <string>
#include <iostream>
#include <assert.h>
#include"Repository.h"
#include "Service.h"
#include "UI.h"
#include"Tests.h"
#include "EventsList.h"

using namespace std;
int main()
{
    /*Comparator<int>* c;
    c->TestComparator();*/

	
    cout << "What tipe of file would you like to use? csv or html?";
    int ok = 1;
    char ch[20];
    Repository_file* repo = new Repository_file{};
    while (ok == 1)
    {
        cin.get(ch, 20);
        cin.get();
        if (strcmp(ch, "csv") == 0) {
            EventsList* events_csv=new EventsListCsv{};
            Service service(repo,events_csv );
            UI ui(service);
            ui.startUI(service);
            ok = 0;
            delete events_csv;
        }
        else if (strcmp(ch, "html") == 0) {
            EventsList* events_html = new EventsListHtml{};
            Service service(repo, events_html);
            UI ui(service);
            ui.startUI(service);
            delete events_html;
            ok = 0;
        }
        else
            cout << "invalid input";
    }

    
    

	
	return 0;
}