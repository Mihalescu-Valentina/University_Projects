#include "Offer.h"
#include<crtdbg.h>
#include"DynamicVector.h"
#include "Repository.h"
#include "UI.h"
int main()
{
	Repository * repo = create_repo();
	UI* ui = createUI(repo);

	startUI(ui);

	destroyUI(ui);
	test_dynamic_vector();
	_CrtDumpMemoryLeaks();

	return 0;
}