#pragma once

#include <iostream>
#include <diy_optional.hpp>

namespace tests
{

    void integer(std::ostream& ost = std::cout)
    {
        diy::optional<int> opt;

        opt = 5;
        ost << opt.value() << "\n";

        opt = -123;
        ost << *opt << "\n";
    }

    void floating(std::ostream& ost = std::cout)
    {
        diy::optional<double> opt(2.5f);
        ost << opt.value() << "\n";

        diy::optional<double> opt2(-0.5f);
        ost << *opt2 << "\n";
    }

    void strings(std::ostream& ost = std::cout)
    {
        diy::optional<const char*> opt("kangaroo");
        ost << opt.value() << "\n";

        diy::optional<const char*> opt2("helm");
        ost << *opt2 << "\n";

        diy::optional<const char*> opt3;
        opt3 = "cycle";
        ost << opt3.value() << "\n";

        opt3 = "moon";
        ost << *opt3 << "\n";
    }

    void nullPointers(std::ostream& ost = std::cout)
    {
        diy::optional<const char*> opt(nullptr);

        ost << opt.valueOr("Not valid") << "\n";
    }

} // namespace tests
