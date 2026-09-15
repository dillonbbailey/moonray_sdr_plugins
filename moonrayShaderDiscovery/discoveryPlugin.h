// Copyright 2023-2024 DreamWorks Animation LLC
// SPDX-License-Identifier: Apache-2.0

#ifndef PXR_USD_PLUGIN_MOONRAY_DISCOVERY_PLUGIN_H
#define PXR_USD_PLUGIN_MOONRAY_DISCOVERY_PLUGIN_H

#include "../sdrCompat.h"
#include "pxr/base/tf/token.h"


PXR_NAMESPACE_OPEN_SCOPE

class MoonrayDiscoveryPlugin : public moonray_sdr::DiscoveryPlugin {
public:
    MoonrayDiscoveryPlugin();

    ~MoonrayDiscoveryPlugin() override = default;

    virtual moonray_sdr::NodeDiscoveryResultVec
#if PXR_VERSION >= 2508
    DiscoverShaderNodes(const Context &context)
#else
    DiscoverNodes(const Context &context)
#endif
        override;

    virtual const moonray_sdr::StringVec& GetSearchURIs() const override;

private:
    moonray_sdr::StringVec _searchPaths;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
