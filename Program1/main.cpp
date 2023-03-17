#include "Program1/IProgram1.h"
#include "Program1/Program1.h"

int main() {
    auto program1 = (IProgram1*) new Program1("KB", 64, 8080);
    program1->Run();
    return 0;
}

