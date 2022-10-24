#pragma once
#include "Repository.h"

typedef struct
{
	Repository* repo;
} UI;

UI* createUI(Repository* repo);

void destroyUI(UI* ui);

void startUI(UI* ui);
