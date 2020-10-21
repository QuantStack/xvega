// Copyright (c) 2020, QuantStack and XVega Contributors
//
// Distributed under the terms of the BSD 3-Clause License.
//
// The full license is in the file LICENSE, distributed with this software.

#ifndef XVEGA_MARK_POINT_HPP
#define XVEGA_MARK_POINT_HPP

#include "../marks.hpp"
#include "../../utils/xmaterialize.hpp"

namespace xv
{
    template <class D>
    struct point : public mark<D>
    {
        using base_type = mark<D>;

        // Point Mark Properties
        XPROPERTY(xtl::xoptional<std::string>, D, shape);
        XPROPERTY(xtl::xoptional<double>, D, size);

        inline point()
        {
            this->type = "point";
        }

        inline void to_json(nl::json& j) const
        {
            base_type::to_json(j);

            serialize(j, shape(), "shape");
            serialize(j, size(), "size");
        }
    };

    using mark_point = xmaterialize<point>;

#ifndef MSC_VER
    extern template class xmaterialize<point>;
#endif
}

#endif
