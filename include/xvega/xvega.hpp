// Copyright (c) 2020, QuantStack and XVega Contributors
//
// Distributed under the terms of the BSD 3-Clause License.
//
// The full license is in the file LICENSE, distributed with this software.

#ifndef XVEGA_HPP
#define XVEGA_HPP

#include "nlohmann/json.hpp"
#include "base/xvega-base.hpp"
#include "grammar/view_compositions/layering.hpp"
#include "grammar/view_compositions/hconcat.hpp"
#include "grammar/view_compositions/vconcat.hpp"
#include "./utils/serialize.hpp"
#include "./xvega_config.hpp"

namespace nl = nlohmann;

namespace xv
{   
    inline nl::json mime_bundle_repr(const Chart& v)
    {
        auto bundle = nl::json::object();
        bundle["application/vnd.vegalite.v3+json"] = v;
        return bundle;
    }
}

#endif