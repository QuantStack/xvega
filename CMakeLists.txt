# Copyright (c) 2020, QuantStack and XVega Contributors
#
# Distributed under the terms of the BSD 3-Clause License.
#
# The full license is in the file LICENSE, distributed with this software.

cmake_minimum_required(VERSION 3.1)
project(xvega)

set(XVEGA_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(XVEGA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Configuration
# ===========
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(XVEGA_INSTALL_LIBRARY_DIR "\"${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}\"")

configure_file (
    "${XVEGA_INCLUDE_DIR}/xvega/xvega_config_cling.hpp.in"
    "${XVEGA_INCLUDE_DIR}/xvega/xvega_config_cling.hpp"
)

# Versionning
# ===========

file(STRINGS "${XVEGA_INCLUDE_DIR}/xvega/xvega_config.hpp" xvega_version_defines
     REGEX "#define XVEGA_VERSION_(MAJOR|MINOR|PATCH)")
foreach(ver ${xvega_version_defines})
    if(ver MATCHES "#define XVEGA_VERSION_(MAJOR|MINOR|PATCH) +([^ ]+)$")
        set(XVEGA_VERSION_${CMAKE_MATCH_1} "${CMAKE_MATCH_2}" CACHE INTERNAL "")
    endif()
endforeach()
set(${PROJECT_NAME}_VERSION
    ${XVEGA_VERSION_MAJOR}.${XVEGA_VERSION_MINOR}.${XVEGA_VERSION_PATCH})
message(STATUS "xvega v${${PROJECT_NAME}_VERSION}")

# Dependencies
# ============

set(xtl_REQUIRED_VERSION 0.6.11)
find_package(xtl ${xtl_REQUIRED_VERSION} REQUIRED)
message(STATUS "Found xtl: ${xtl_INCLUDE_DIRS}/xtl")

set(xproperty_REQUIRED_VERSION 0.10.4)
find_package(xproperty ${xproperty_REQUIRED_VERSION} REQUIRED)
message(STATUS "Found xproperty: ${xproperty_INCLUDE_DIRS}/xproperty")

set(nlohmann_json_REQUIRED_VERSION 3.7.3)
find_package(nlohmann_json ${nlohmann_json_REQUIRED_VERSION} REQUIRED)
message(STATUS "Found nlohmann_json: ${nlohmann_json_INCLUDE_DIRS}/nlohmann_json")

# Build
# =====

set(XVEGA_HEADERS
    ${XVEGA_INCLUDE_DIR}/xvega/xvega.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/xvega_config.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/xvega_config_cling.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/base/xvega-base.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/marks.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/marks/mark_arc.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/marks/mark_area.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/marks/mark_bar.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/marks/mark_circle.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/marks/mark_geoshape.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/marks/mark_image.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/marks/mark_line.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/marks/mark_point.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/marks/mark_rect.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/marks/mark_rule.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/marks/mark_square.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/marks/mark_text.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/marks/mark_tick.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/marks/mark_trail.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/selections.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/selections/selection_single.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/selections/selection_multi.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/selections/selection_mark.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/selections/selection_interval.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/selections/bindings/bind_checkbox.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/selections/bindings/bind_input.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/selections/bindings/bind_radio_select.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/selections/bindings/bind_range.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/selections/bindings/legend_stream_binding.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/selections/streams/event_stream.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/selections/streams/derived_stream.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/selections/streams/merged_stream.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channel-options/aggregate.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channel-options/axis.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channel-options/bin.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channel-options/condition.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channel-options/datetime.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channel-options/datum.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channel-options/field.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channel-options/header.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channel-options/impute.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channel-options/legend.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channel-options/repeatRef.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channel-options/scale.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channel-options/sort.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channel-options/stack.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channel-options/timeunit.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channel-options/value.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/detail-channel/detail.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/facet-channels/column.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/facet-channels/facet.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/facet-channels/row.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/hyperlink-channels/href.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/mark-property-channels/color.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/mark-property-channels/fill.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/mark-property-channels/fillOpacity.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/mark-property-channels/opacity.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/mark-property-channels/shape.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/mark-property-channels/size.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/mark-property-channels/stroke.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/mark-property-channels/strokeDash.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/mark-property-channels/strokeOpacity.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/mark-property-channels/strokeWidth.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/order-channel/order.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/position-channels/latitude.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/position-channels/longitude.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/position-channels/latitude2.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/position-channels/longitude2.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/position-channels/x.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/position-channels/y.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/position-channels/x2.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/position-channels/y2.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/position-channels/xerror.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/position-channels/xerror2.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/position-channels/yerror.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/position-channels/yerror2.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/text-tooltip-channels/key.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/text-tooltip-channels/text.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/encodings/encoding-channels/text-tooltip-channels/tooltip.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/utils/custom_datatypes.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/utils/xeither.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/utils/serialize.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/utils/random_string.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/data/data_format.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/data/data_format/json_data_format.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/data/data_format/csv_data_format.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/data/data_format/tsv_data_format.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/data/data_format/dsv_data_format.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/data/data_format/topo_data_format.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/data/data_source/named_data.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/data/data_source/url_data.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/data/data_source/inline_data.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/data/generator/sequence_generator.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/data/generator/sphere_generator.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/data/generator/graticule_generator.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/transformations/transform_aggregate.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/transformations/transform_bin.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/transformations/transform_calculate.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/transformations/transform_density.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/transformations/transform_flatten.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/transformations/transform_fold.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/transformations/transform_impute.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/transformations/transform_join_aggregate.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/transformations/transform_loess.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/transformations/transform_lookup.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/transformations/transform_pivot.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/transformations/transform_quantile.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/transformations/transform_regression.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/transformations/transform_sample.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/transformations/transform_stack.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/transformations/transform_timeunit.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/transformations/transform_window.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/view_compositions/layering.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/view_compositions/hconcat.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/view_compositions/vconcat.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/config.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/config/area_config.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/config/auto_size_params.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/config/axis_config.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/config/bar_config.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/config/base_config.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/config/box_plot_config.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/config/composition_config.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/config/error_band_config.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/config/error_bar_config.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/config/header_config.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/config/legend_config.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/config/line_config.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/config/mark_config.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/config/overlay_mark_def.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/config/projection_config.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/config/range_config.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/config/rect_config.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/config/scale_config.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/config/selection_config.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/config/style_config_index.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/config/tick_config.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/config/title_config.hpp
    ${XVEGA_INCLUDE_DIR}/xvega/grammar/config/view_config.hpp
)

set(XVEGA_SOURCES
    ${XVEGA_SOURCE_DIR}/base/xvega-base.cpp
    ${XVEGA_SOURCE_DIR}/utils/custom_datatypes.cpp
    ${XVEGA_SOURCE_DIR}/utils/random_string.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channel-options/aggregate.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channel-options/axis.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channel-options/bin.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channel-options/condition.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channel-options/datetime.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channel-options/header.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channel-options/impute.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channel-options/legend.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channel-options/repeatRef.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channel-options/scale.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channel-options/sort.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channel-options/timeunit.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channel-options/value.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/detail-channel/detail.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/facet-channels/column.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/facet-channels/facet.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/facet-channels/row.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/hyperlink-channels/href.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/mark-property-channels/color.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/mark-property-channels/fill.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/mark-property-channels/fillOpacity.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/mark-property-channels/opacity.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/mark-property-channels/shape.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/mark-property-channels/size.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/mark-property-channels/stroke.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/mark-property-channels/strokeDash.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/mark-property-channels/strokeOpacity.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/mark-property-channels/strokeWidth.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/order-channel/order.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/position-channels/latitude.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/position-channels/longitude.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/position-channels/latitude2.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/position-channels/longitude2.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/position-channels/x.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/position-channels/y.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/position-channels/x2.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/position-channels/y2.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/position-channels/xerror.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/position-channels/xerror2.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/position-channels/yerror.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/position-channels/yerror2.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/text-tooltip-channels/key.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/text-tooltip-channels/text.cpp
    ${XVEGA_SOURCE_DIR}/grammar/encodings/encoding-channels/text-tooltip-channels/tooltip.cpp
    ${XVEGA_SOURCE_DIR}/grammar/marks/mark_arc.cpp
    ${XVEGA_SOURCE_DIR}/grammar/marks/mark_area.cpp
    ${XVEGA_SOURCE_DIR}/grammar/marks/mark_bar.cpp
    ${XVEGA_SOURCE_DIR}/grammar/marks/mark_circle.cpp
    ${XVEGA_SOURCE_DIR}/grammar/marks/mark_geoshape.cpp
    ${XVEGA_SOURCE_DIR}/grammar/marks/mark_image.cpp
    ${XVEGA_SOURCE_DIR}/grammar/marks/mark_line.cpp
    ${XVEGA_SOURCE_DIR}/grammar/marks/mark_point.cpp
    ${XVEGA_SOURCE_DIR}/grammar/marks/mark_rect.cpp
    ${XVEGA_SOURCE_DIR}/grammar/marks/mark_rule.cpp
    ${XVEGA_SOURCE_DIR}/grammar/marks/mark_square.cpp
    ${XVEGA_SOURCE_DIR}/grammar/marks/mark_text.cpp
    ${XVEGA_SOURCE_DIR}/grammar/marks/mark_tick.cpp
    ${XVEGA_SOURCE_DIR}/grammar/marks/mark_trail.cpp
    ${XVEGA_SOURCE_DIR}/grammar/selections/bindings/bind_checkbox.cpp
    ${XVEGA_SOURCE_DIR}/grammar/selections/bindings/bind_input.cpp
    ${XVEGA_SOURCE_DIR}/grammar/selections/bindings/bind_radio_select.cpp
    ${XVEGA_SOURCE_DIR}/grammar/selections/bindings/bind_range.cpp
    ${XVEGA_SOURCE_DIR}/grammar/selections/bindings/legend_stream_binding.cpp
    ${XVEGA_SOURCE_DIR}/grammar/selections/streams/derived_stream.cpp
    ${XVEGA_SOURCE_DIR}/grammar/selections/streams/event_stream.cpp
    ${XVEGA_SOURCE_DIR}/grammar/selections/streams/merged_stream.cpp
    ${XVEGA_SOURCE_DIR}/grammar/selections/selection_mark.cpp
    ${XVEGA_SOURCE_DIR}/grammar/selections/selection_single.cpp
    ${XVEGA_SOURCE_DIR}/grammar/selections/selection_multi.cpp
    ${XVEGA_SOURCE_DIR}/grammar/selections/selection_interval.cpp
    ${XVEGA_SOURCE_DIR}/grammar/data/data_format/json_data_format.cpp
    ${XVEGA_SOURCE_DIR}/grammar/data/data_format/csv_data_format.cpp
    ${XVEGA_SOURCE_DIR}/grammar/data/data_format/tsv_data_format.cpp
    ${XVEGA_SOURCE_DIR}/grammar/data/data_format/dsv_data_format.cpp
    ${XVEGA_SOURCE_DIR}/grammar/data/data_format/topo_data_format.cpp
    ${XVEGA_SOURCE_DIR}/grammar/data/data_source/named_data.cpp
    ${XVEGA_SOURCE_DIR}/grammar/data/data_source/url_data.cpp
    ${XVEGA_SOURCE_DIR}/grammar/data/data_source/inline_data.cpp
    ${XVEGA_SOURCE_DIR}/grammar/data/generator/sequence_generator.cpp
    ${XVEGA_SOURCE_DIR}/grammar/data/generator/sphere_generator.cpp
    ${XVEGA_SOURCE_DIR}/grammar/data/generator/graticule_generator.cpp
    ${XVEGA_SOURCE_DIR}/grammar/transformations/transform_aggregate.cpp
    ${XVEGA_SOURCE_DIR}/grammar/transformations/transform_bin.cpp
    ${XVEGA_SOURCE_DIR}/grammar/transformations/transform_calculate.cpp
    ${XVEGA_SOURCE_DIR}/grammar/transformations/transform_density.cpp
    ${XVEGA_SOURCE_DIR}/grammar/transformations/transform_flatten.cpp
    ${XVEGA_SOURCE_DIR}/grammar/transformations/transform_fold.cpp
    ${XVEGA_SOURCE_DIR}/grammar/transformations/transform_impute.cpp
    ${XVEGA_SOURCE_DIR}/grammar/transformations/transform_join_aggregate.cpp
    ${XVEGA_SOURCE_DIR}/grammar/transformations/transform_loess.cpp
    ${XVEGA_SOURCE_DIR}/grammar/transformations/transform_lookup.cpp
    ${XVEGA_SOURCE_DIR}/grammar/transformations/transform_pivot.cpp
    ${XVEGA_SOURCE_DIR}/grammar/transformations/transform_quantile.cpp
    ${XVEGA_SOURCE_DIR}/grammar/transformations/transform_regression.cpp
    ${XVEGA_SOURCE_DIR}/grammar/transformations/transform_sample.cpp
    ${XVEGA_SOURCE_DIR}/grammar/transformations/transform_stack.cpp
    ${XVEGA_SOURCE_DIR}/grammar/transformations/transform_timeunit.cpp
    ${XVEGA_SOURCE_DIR}/grammar/transformations/transform_window.cpp
    ${XVEGA_SOURCE_DIR}/grammar/config.cpp
    ${XVEGA_SOURCE_DIR}/grammar/config/area_config.cpp
    ${XVEGA_SOURCE_DIR}/grammar/config/auto_size_params.cpp
    ${XVEGA_SOURCE_DIR}/grammar/config/axis_config.cpp
    ${XVEGA_SOURCE_DIR}/grammar/config/bar_config.cpp
    ${XVEGA_SOURCE_DIR}/grammar/config/box_plot_config.cpp
    ${XVEGA_SOURCE_DIR}/grammar/config/composition_config.cpp
    ${XVEGA_SOURCE_DIR}/grammar/config/error_band_config.cpp
    ${XVEGA_SOURCE_DIR}/grammar/config/error_bar_config.cpp
    ${XVEGA_SOURCE_DIR}/grammar/config/header_config.cpp
    ${XVEGA_SOURCE_DIR}/grammar/config/legend_config.cpp
    ${XVEGA_SOURCE_DIR}/grammar/config/line_config.cpp
    ${XVEGA_SOURCE_DIR}/grammar/config/mark_config.cpp
    ${XVEGA_SOURCE_DIR}/grammar/config/overlay_mark_def.cpp
    ${XVEGA_SOURCE_DIR}/grammar/config/projection_config.cpp
    ${XVEGA_SOURCE_DIR}/grammar/config/range_config.cpp
    ${XVEGA_SOURCE_DIR}/grammar/config/rect_config.cpp
    ${XVEGA_SOURCE_DIR}/grammar/config/scale_config.cpp
    ${XVEGA_SOURCE_DIR}/grammar/config/selection_config.cpp
    ${XVEGA_SOURCE_DIR}/grammar/config/style_config_index.cpp
    ${XVEGA_SOURCE_DIR}/grammar/config/tick_config.cpp
    ${XVEGA_SOURCE_DIR}/grammar/config/title_config.cpp
    ${XVEGA_SOURCE_DIR}/grammar/config/view_config.cpp
)

add_library(xvega SHARED ${XVEGA_SOURCES} ${XVEGA_HEADERS})
target_include_directories(xvega PUBLIC $<BUILD_INTERFACE:${XVEGA_INCLUDE_DIR}>
                                               $<INSTALL_INTERFACE:include>)
target_link_libraries(xvega PUBLIC xtl)
target_link_libraries(xvega PUBLIC xproperty)
# target_link_libraries(xvega PUBLIC nlohmann_json)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
endif (MSVC)

set_target_properties(xvega PROPERTIES
#                       LINKER_LANGUAGE CXX
#                       PUBLIC_HEADER DESTINATION "${XVEGA_HEADERS}"
                       COMPILE_DEFINITIONS "XVEGA_EXPORTS"
#                       PREFIX ""
#                       VERSION ${${PROJECT_NAME}_VERSION}
#                       SOVERSION ${${PROJECT_NAME}_VERSION}
#                       OUTPUT_NAME "libxvega")
                     )

# Installation
# ============

OPTION(BUILD_TESTS "xvega test suite" OFF)
OPTION(DOWNLOAD_GTEST "build gtest from downloaded sources" OFF)

if(DOWNLOAD_GTEST OR GTEST_SRC_DIR)
    set(BUILD_TESTS ON)
endif()

if(BUILD_TESTS)
    add_subdirectory(test)
endif()

install(TARGETS xvega
        EXPORT ${PROJECT_NAME}-targets)

# Makes the project importable from the build directory
export(EXPORT ${PROJECT_NAME}-targets
       FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake")

install(DIRECTORY ${XVEGA_INCLUDE_DIR}/xvega
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

set(XVEGA_CMAKECONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}" CACHE STRING "install path for xvegaConfig.cmake")

configure_package_config_file(${PROJECT_NAME}Config.cmake.in
                              "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
                              INSTALL_DESTINATION ${XVEGA_CMAKECONFIG_INSTALL_DIR})

# Remove CMAKE_SIZEOF_VOID_P from xvegaConfigVersion.cmake so that an xvegaConfig.cmake
# generated for a 64 bit target can be used for 32 bit targets and vice versa.
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
                                 VERSION ${${PROJECT_NAME}_VERSION}
                                 COMPATIBILITY AnyNewerVersion)
set(CMAKE_SIZEOF_VOID_P ${_XVEGA_CMAKE_SIZEOF_VOID_P})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION ${XVEGA_CMAKECONFIG_INSTALL_DIR})
install(EXPORT ${PROJECT_NAME}-targets
        FILE ${PROJECT_NAME}Targets.cmake
        DESTINATION ${XVEGA_CMAKECONFIG_INSTALL_DIR})

