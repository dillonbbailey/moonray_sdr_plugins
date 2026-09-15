// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <pxr/pxr.h>
#include <pxr/usd/sdr/shaderNode.h>
#if PXR_VERSION >= 2508
#include <pxr/usd/sdr/discoveryPlugin.h>
#include <pxr/usd/sdr/parserPlugin.h>
#include <pxr/usd/sdr/shaderNodeDiscoveryResult.h>
#else
#include <pxr/usd/ndr/discoveryPlugin.h>
#include <pxr/usd/ndr/parserPlugin.h>
#include <pxr/usd/ndr/nodeDiscoveryResult.h>
#endif

PXR_NAMESPACE_OPEN_SCOPE
// Ndr was removed in USD 25.08. Keep these aliases local to this project.
namespace moonray_sdr {
#if PXR_VERSION >= 2508
using NodeUniquePtr = SdrShaderNodeUniquePtr;
using NodeDiscoveryResult = SdrShaderNodeDiscoveryResult;
using NodeDiscoveryResultVec = SdrShaderNodeDiscoveryResultVec;
using PropertyUniquePtrVec = SdrShaderPropertyUniquePtrVec;
using DiscoveryPlugin = SdrDiscoveryPlugin;
using DiscoveryPluginContext = SdrDiscoveryPluginContext;
using ParserPlugin = SdrParserPlugin;
using TokenVec = SdrTokenVec;
using TokenMap = SdrTokenMap;
using OptionVec = SdrOptionVec;
using StringVec = SdrStringVec;
using StringSet = SdrStringSet;
using Identifier = SdrIdentifier;
using Version = SdrVersion;
#else
using NodeUniquePtr = NdrNodeUniquePtr;
using NodeDiscoveryResult = NdrNodeDiscoveryResult;
using NodeDiscoveryResultVec = NdrNodeDiscoveryResultVec;
using PropertyUniquePtrVec = NdrPropertyUniquePtrVec;
using DiscoveryPlugin = NdrDiscoveryPlugin;
using DiscoveryPluginContext = NdrDiscoveryPluginContext;
using ParserPlugin = NdrParserPlugin;
using TokenVec = NdrTokenVec;
using TokenMap = NdrTokenMap;
using OptionVec = NdrOptionVec;
using StringVec = NdrStringVec;
using StringSet = NdrStringSet;
using Identifier = NdrIdentifier;
using Version = NdrVersion;
#endif

inline NodeUniquePtr invalidNode(const NodeDiscoveryResult& result)
{
#if PXR_VERSION >= 2508
    return ParserPlugin::GetInvalidShaderNode(result);
#else
    return ParserPlugin::GetInvalidNode(result);
#endif
}
} // namespace moonray_sdr
PXR_NAMESPACE_CLOSE_SCOPE
