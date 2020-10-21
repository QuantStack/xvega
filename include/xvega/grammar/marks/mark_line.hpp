// Copyright (c) 2020, QuantStack and XVega Contributors
//
// Distributed under the terms of the BSD 3-Clause License.
//
// The full license is in the file LICENSE, distributed with this software.

#ifndef XVEGA_MARK_LINE_HPP
#define XVEGA_MARK_LINE_HPP

#include "../marks.hpp"
#include "../../utils/xmaterialize.hpp"

namespace xv
{
    template <class D>
    struct line : public mark<D>
    {
        using base_type = mark<D>;

        XPROPERTY(xtl::xoptional<std::string>, D, orient);
        XPROPERTY(xtl::xoptional<std::string>, D, interpolate);
        XPROPERTY(xtl::xoptional<double>, D, tension);
        XPROPERTY(xtl::xoptional<bool_string_object_type>, D, point);

        inline line()
        {
            this->type = "line";
        }

        inline void to_json(nl::json& j) const
        {
            base_type::to_json(j);

            serialize(j, orient(), "orient");
            serialize(j, interpolate(), "interpolate");
            serialize(j, tension(), "tension");
            serialize(j, point(), "point");
        }
    };

    using mark_line = xmaterialize<line>;

#ifndef MSC_VER
    extern template class xmaterialize<line>;
#endif
}

#endif
