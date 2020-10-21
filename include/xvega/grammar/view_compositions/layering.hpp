// Copyright (c) 2020, QuantStack and XVega Contributors
//
// Distributed under the terms of the BSD 3-Clause License.
//
// The full license is in the file LICENSE, distributed with this software.

#include "xvega/base/xvega-base.hpp"
#include <xproperty/xobserved.hpp>
#include <xtl/xoptional.hpp>
#include <xtl/xvariant.hpp>
#include <xtl/xjson.hpp>
#include <nlohmann/json.hpp>
#include "../../xvega_config.hpp"
#include "../../utils/serialize.hpp"

namespace nl = nlohmann;

namespace xv
{
    struct layer : public xp::xobserved<layer>
    {
        XPROPERTY(std::vector<Chart>, layer, charts);
    };

    inline nl::json mime_bundle_repr(const layer& v)
    {
        auto j = nl::json::object();
        j["$schema"] = "https://vega.github.io/schema/vega-lite/v4.json";
        int len_charts = v.charts().size();
        
        for(int i=0; i<len_charts; i++)
        {
            j["layer"][i]["mark"] = v.charts()[i].mark();
            serialize(j["layer"][i], v.charts()[i].encoding(), "encoding");
            serialize(j["layer"][i], v.charts()[i].width(), "width");
            serialize(j["layer"][i], v.charts()[i].height(), "height");
            int len_selections = v.charts()[i].selections().size();
            int len_transformations = v.charts()[i].transformations().size();
            for(int k=0; k<len_selections; k++)
            {
                xtl::visit([&](auto&& arg){
                        j["layer"][i]["selection"][arg.name().value()]=arg;
                    }, v.charts()[i].selections()[k]);
            }
            for(int k=0; k<len_transformations; k++)
            {
                xtl::visit([&](auto&& arg){
                        j["layer"][i]["transform"][k]=arg;
                    }, v.charts()[i].transformations()[k]);
            }
        }
        j["data"] = v.charts()[0].data();

        auto bundle = nl::json::object();
        bundle["application/vnd.vegalite.v3+json"] = j;
        return bundle;
    }
}