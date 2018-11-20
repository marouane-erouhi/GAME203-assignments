#include <iostream>
#include "GameManager.h"

#include "Vector.h"
#include "Matrix.h"
#include "VMath.h"

int main(int argc, char* args[]) { /// Standard C-style entry point, you need to use it

	GameManager *ptr = new GameManager();
	bool status  = ptr->OnCreate();
	if (status == true) {
		ptr->Run();
	} else if (status == false) {
		/// You should have learned about stderr (std::cerr) in Operating Systems 
		std::cerr << "Fatal error occured. Cannot start this program" << std::endl;
		getchar(); /// Pause the program so you can read the error
	}
	delete ptr;
	return 0;

}