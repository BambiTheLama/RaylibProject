#include "Core/Engine.h"
#ifdef test
#include "json.hpp"
#include <fstream>
#endif // test



int main()
{
#ifdef test
    const char* path = "Res/Weapon.json";
    std::ifstream r(path);
    if (r.is_open())
    {
        nlohmann::json j;
        r >> j;
        r.close();
        std::ofstream w(path);
        w << j.dump(2);
        w.close();
    }
#endif // test
    Engine e;
    return 0;
}
