// Copyright (c) 2020, QuantStack and XVega Contributors
//
// Distributed under the terms of the BSD 3-Clause License.
//
// The full license is in the file LICENSE, distributed with this software.

#ifndef XVEGA_CHART_HPP
#define XVEGA_CHART_HPP

#include <vector>

#include "../xvega_config.hpp"

#include "../utils/custom_datatypes.hpp"
#include "../utils/xany.hpp"

#include "../grammar/marks.hpp"
#include "../grammar/encodings.hpp"
#include "../grammar/selections.hpp"
#include "../grammar/transformations.hpp"
#include "../grammar/config.hpp"
#include "../grammar/title.hpp"

// data
#include "../grammar/data/data_source/named_data.hpp"
#include "../grammar/data/data_source/inline_data.hpp"
#include "../grammar/data/data_source/url_data.hpp"

// generators
#include "../grammar/data/generator/sequence_generator.hpp"
#include "../grammar/data/generator/sphere_generator.hpp"
#include "../grammar/data/generator/graticule_generator.hpp"

namespace nl = nlohmann;

namespace xv
{
    using data_type = xtl::variant<
        named_data, inline_data, url_data,
        sequence_generator, sphere_generator, graticule_generator,
        data_frame>;

    using marks_type = xany<mark>;
    using selection_type = xany<selection>;
    using transform_type = xany<transformation>;
    using title_type = xtl::variant<std::string, Title>;

    struct Chart : public xp::xobserved<Chart>
    {
        XPROPERTY(data_type, Chart, data);
        XPROPERTY(marks_type, Chart, mark);
        XPROPERTY(nl::json, Chart, encoding);
        XPROPERTY(std::vector<selection_type>, Chart, selections);
        XPROPERTY(std::vector<transform_type>, Chart, transformations);
        XPROPERTY(xtl::xoptional<double>, Chart, width);
        XPROPERTY(xtl::xoptional<double>, Chart, height);
        XPROPERTY(xtl::xoptional<Config>, Chart, config);
        XPROPERTY(xtl::xoptional<title_type>, Chart, title);
    };
    
    nl::json XVEGA_API mime_bundle_repr(const Chart& v);
}

#endif
