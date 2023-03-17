#include "Program2/IProgram2.h"
#include "Program2/Program2.h"

int main() {

    auto server = (IProgram2*)new Program2(8080, 2, 32);
    server->Run();

    return 0;
}
