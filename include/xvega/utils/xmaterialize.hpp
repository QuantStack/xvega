// Copyright (c) 2020, QuantStack and XVega Contributors
//
// Distributed under the terms of the BSD 3-Clause License.
//
// The full license is in the file LICENSE, distributed with this software.

#ifndef XVEGA_MATERIALIZE_HPP
#define XVEGA_MATERIALIZE_HPP

#include <utility>

#include "nlohmann/json.hpp"

#include "../xvega_config.hpp"

namespace nl = nlohmann;

namespace xv
{
    template <template <class> class B, class... P>
    struct xmaterialize final : public B<xmaterialize<B, P...>>
    {
        using self_type = xmaterialize<B, P...>;
        using base_type = B<self_type>;
        using base_type::base_type;
    };
}

#endif
