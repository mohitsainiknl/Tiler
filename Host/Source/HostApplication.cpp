#include "Tiler.h"


class Host : public Tiler::Application {

public:
	Host() {

	}
	~Host() {

	}
};

Tiler::Application* Tiler::CreateApplication() {

	return new Host();
}





