// Copyright (c) 2020, QuantStack and XVega Contributors
//
// Distributed under the terms of the BSD 3-Clause License.
//
// The full license is in the file LICENSE, distributed with this software.

#include "xvega/grammar/chart.hpp"

#include <cstddef>

#include "../utils/serialize.hpp"

namespace xv
{
    void to_json(nl::json& j, const Chart& data)
    {
        j["$schema"] = "https://vega.github.io/schema/vega-lite/v4.json";
        j["data"] = data.data();
        j["mark"] = data.mark();
        j["encoding"] = data.encoding();

        for(std::size_t i=0; i<data.selections().size(); ++i)
        {
            j["selection"][data.selections()[i].name()] = data.selections()[i];
        }

        j["transform"] = data.transformations();

        serialize(j, data.width(), "width");
        serialize(j, data.height(), "height");
        serialize(j, data.config(), "config");
        serialize(j, data.title(), "title");
    }

    nl::json mime_bundle_repr(const Chart& v)
    {
        auto bundle = nl::json::object();
        bundle["application/vnd.vegalite.v3+json"] = v;
        return bundle;
    }
}
