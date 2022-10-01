#include "repository.h"
#include "controller.h"
#include "ui.h"
#include <stdio.h>
#include <crtdbg.h>

int main() {
	test_domain();
	test_repository();
	test_controller();
	test_dynamic_array();

	Repository* repo = createRepo();
	Controller* cont = createController(repo);
	UI* ui = createUI(cont);
	startUI(ui);
	destroyUI(ui);
	_CrtDumpMemoryLeaks();
	return 0;
}