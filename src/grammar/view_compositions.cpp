// Copyright (c) 2020, QuantStack and XVega Contributors
//
// Distributed under the terms of the BSD 3-Clause License.
//
// The full license is in the file LICENSE, distributed with this software.

#include "xvega/grammar/view_compositions.hpp"

#include "../utils/serialize.hpp"

namespace xv
{
    void to_json(nl::json& j, const hconcat& data)
    {
        j["$schema"] = "https://vega.github.io/schema/vega-lite/v4.json";
        int len_charts = data.charts().size();
        
        for(int i=0; i<len_charts; i++)
        {
            j["hconcat"][i]["mark"] = data.charts()[i].mark();
            j["hconcat"][i]["encoding"] = data.charts()[i].encoding();
            serialize(j["hconcat"][i], data.charts()[i].width(), "width");
            serialize(j["hconcat"][i], data.charts()[i].height(), "height");
            serialize(j["hconcat"][i], data.charts()[i].title(), "title");
            int len_selections = data.charts()[i].selections().size();
            int len_transformations = data.charts()[i].transformations().size();
            for(int k=0; k<len_selections; k++)
            {
                /*xtl::visit([&](auto&& arg){
                        j["hconcat"][i]["selection"][arg.name().value()] = arg;
                    }, data.charts()[i].selections()[k]);*/
            }
            for(int k=0; k<len_transformations; k++)
            {
                j["hconcat"][i]["transform"][k] = data.charts()[i].transformations()[k];
            }
        }
        j["data"] = data.charts()[0].data();
    }

    void to_json(nl::json& j, const vconcat& data)
    {
        j["$schema"] = "https://vega.github.io/schema/vega-lite/v4.json";
        int len_charts = data.charts().size();
        
        for(int i=0; i<len_charts; i++)
        {
            j["vconcat"][i]["mark"] = data.charts()[i].mark();
            j["vconcat"][i]["encoding"] = data.charts()[i].encoding();
            serialize(j["vconcat"][i], data.charts()[i].width(), "width");
            serialize(j["vconcat"][i], data.charts()[i].height(), "height");
            serialize(j["vconcat"][i], data.charts()[i].title(), "title");
            int len_selections = data.charts()[i].selections().size();
            int len_transformations = data.charts()[i].transformations().size();
            for(int k=0; k<len_selections; k++)
            {
                /*xtl::visit([&](auto&& arg){
                        j["vconcat"][i]["selection"][arg.name().value()]=arg;
                    }, data.charts()[i].selections()[k]);*/
            }
            for(int k=0; k<len_transformations; k++)
            {
                j["vconcat"][i]["transform"][k] = data.charts()[i].transformations()[k];
            }
        }
        j["data"] = data.charts()[0].data();
    }

    void to_json(nl::json& j, const layer& data)
    {
        j["$schema"] = "https://vega.github.io/schema/vega-lite/v4.json";
        int len_charts = data.charts().size();
        
        for(int i=0; i<len_charts; i++)
        {
            j["layer"][i]["mark"] = data.charts()[i].mark();
            j["layer"][i]["encoding"] = data.charts()[i].encoding();
            serialize(j["layer"][i], data.charts()[i].width(), "width");
            serialize(j["layer"][i], data.charts()[i].height(), "height");
            serialize(j["layer"][i], data.charts()[i].title(), "title");
            int len_selections = data.charts()[i].selections().size();
            int len_transformations = data.charts()[i].transformations().size();
            for(int k=0; k<len_selections; k++)
            {
                /*xtl::visit([&](auto&& arg){
                        j["layer"][i]["selection"][arg.name().value()]=arg;
                    }, data.charts()[i].selections()[k]);*/
            }
            for(int k=0; k<len_transformations; k++)
            {
                j["layer"][i]["transform"][k] = data.charts()[i].transformations()[k];
            }
        }
        j["data"] = data.charts()[0].data();
    }

    nl::json mime_bundle_repr(const hconcat& v)
    {
        auto bundle = nl::json::object();
        bundle["application/vnd.vegalite.v3+json"] = v;
        return bundle;
    }

    nl::json mime_bundle_repr(const layer& v)
    {
        auto bundle = nl::json::object();
        bundle["application/vnd.vegalite.v3+json"] = v;
        return bundle;
    }

    nl::json mime_bundle_repr(const vconcat& v)
    {
        auto bundle = nl::json::object();
        bundle["application/vnd.vegalite.v3+json"] = v;
        return bundle;
    }
}
