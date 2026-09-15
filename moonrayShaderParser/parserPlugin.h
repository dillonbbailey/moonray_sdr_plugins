// Copyright 2023-2024 DreamWorks Animation LLC
// SPDX-License-Identifier: Apache-2.0

#ifndef PXR_USD_PLUGIN_MOONRAY_PARSER_PLUGIN_H
#define PXR_USD_PLUGIN_MOONRAY_PARSER_PLUGIN_H

#include "../sdrCompat.h"
#include "pxr/base/tf/token.h"


PXR_NAMESPACE_OPEN_SCOPE


class MoonrayParserPlugin : public moonray_sdr::ParserPlugin {
public:
    MoonrayParserPlugin() = default;

    ~MoonrayParserPlugin() override = default;

    moonray_sdr::NodeUniquePtr
#if PXR_VERSION >= 2508
    ParseShaderNode(const moonray_sdr::NodeDiscoveryResult &discoveryResult)
#else
    Parse(const moonray_sdr::NodeDiscoveryResult &discoveryResult)
#endif
        override;

    const moonray_sdr::TokenVec &GetDiscoveryTypes() const override;

    const TfToken &GetSourceType() const override;

};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
