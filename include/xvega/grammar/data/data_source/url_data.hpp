// Copyright (c) 2020, QuantStack and XVega Contributors
//
// Distributed under the terms of the BSD 3-Clause License.
//
// The full license is in the file LICENSE, distributed with this software.

#ifndef XVEGA_URL_DATA_HPP
#define XVEGA_URL_DATA_HPP

#include "../data_format/csv_data_format.hpp"
#include "../data_format/tsv_data_format.hpp"
#include "../data_format/dsv_data_format.hpp"
#include "../data_format/json_data_format.hpp"
#include "../data_format/topo_data_format.hpp"

#include "../../../utils/xmaterialize.hpp"

namespace xv
{
    using data_format_type = xtl::variant<
                                  csv_data_format, 
                                  tsv_data_format, 
                                  dsv_data_format, 
                                  json_data_format, 
                                  topo_data_format
                                  >;

    template <class D>
    struct URL_data : public xp::xobserved<D>
    {
        XPROPERTY(xtl::xoptional<std::string>, D, url);
        XPROPERTY(xtl::xoptional<std::string>, D, name);
        XPROPERTY(xtl::xoptional<data_format_type>, D, format);
    };

    using url_data = xmaterialize<URL_data>;

    inline void to_json(nl::json& j, const url_data& data)
    {
        serialize(j, data.url(), "url");
        serialize(j, data.name(), "name");
        serialize(j, data.format(), "format");
    }

#ifndef MSC_VER
    extern template class xmaterialize<URL_data>;
#endif
}

#endif
