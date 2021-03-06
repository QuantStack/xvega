// Copyright (c) 2020, QuantStack and XVega Contributors
//
// Distributed under the terms of the BSD 3-Clause License.
//
// The full license is in the file LICENSE, distributed with this software.

#ifndef XVEGA_ENCODING_TEXT_HPP
#define XVEGA_ENCODING_TEXT_HPP

#include <xproperty/xobserved.hpp>

#include <xtl/xoptional.hpp>
#include <xtl/xjson.hpp>

#include <nlohmann/json.hpp>

#include "../../encoding-channel-options/aggregate.hpp"
#include "../../encoding-channel-options/bin.hpp"
#include "../../encoding-channel-options/field.hpp"
#include "../../encoding-channel-options/timeunit.hpp"
#include "../../../../utils/custom_datatypes.hpp"

namespace nl = nlohmann;

namespace xv
{
    struct Text : public xp::xobserved<Text>
    {
        XPROPERTY(xtl::xoptional<agg_type>, Text, aggregate);
        XPROPERTY(xtl::xoptional<bin_type>, Text, bin);
        // XPROPERTY(xtl::xoptional<condition_type>, Text, condition);
        XPROPERTY(xtl::xoptional<field_type>, Text, field);
        XPROPERTY(xtl::xoptional<string_object_type>, Text, format);
        XPROPERTY(xtl::xoptional<std::string>, Text, formatType);
        XPROPERTY(xtl::xoptional<std::string>, Text, labelExpr);
        XPROPERTY(xtl::xoptional<time_unit_type>, Text, timeUnit);
        XPROPERTY(xtl::xoptional<string_vec_none_type>, Text, title);
        XPROPERTY(xtl::xoptional<std::string>, Text, type);
    };

    XVEGA_API void to_json(nl::json& j, const Text& data);
}

#endif