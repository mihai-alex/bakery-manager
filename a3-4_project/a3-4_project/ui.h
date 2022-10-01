#pragma once
#include "controller.h"

typedef struct {
	Controller* cont;
} UI;

UI* createUI(Controller* cont);

void destroyUI(UI* ui);

void startUI(UI* ui);

void addMaterialUI(UI* ui);

void deleteMaterialUI(UI* ui);

void updateMaterialUI(UI* ui);

void listExpiredMaterialsUI(UI* ui, char* str);

void listAllMaterialsUI(UI* ui);