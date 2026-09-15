// Copyright 2023-2024 DreamWorks Animation LLC
// SPDX-License-Identifier: Apache-2.0

#include "discoveryPlugin.h"

#include "pxr/base/tf/diagnostic.h"
#include "pxr/base/tf/fileUtils.h"
#include "pxr/base/tf/stringUtils.h"
#include "pxr/base/tf/envSetting.h"
#include "pxr/base/tf/pathUtils.h"

#include "pxr/usd/ar/resolver.h"
#include "pxr/usd/ar/resolverScopedCache.h"

#if PXR_VERSION >= 2508
#include "pxr/usd/sdr/debugCodes.h"
#else
#include "pxr/usd/ndr/debugCodes.h"
#endif
#include <functional>

PXR_NAMESPACE_OPEN_SCOPE

using namespace moonray_sdr;

TfToken moonrayNodeType("moonrayClass");

namespace {

bool examineFiles(NodeDiscoveryResultVec* foundNodes,
                  StringSet* foundNames,
                  const DiscoveryPluginContext* context,
                  const std::string& dirPath,
                  const StringVec& dirFileNames)
{
    for (const std::string& fileName : dirFileNames) {
        std::string extension = TfStringToLower(TfGetExtension(fileName));
        if (extension == "json") {
            std::string uri = TfStringCatPaths(dirPath, fileName);
            std::string className = TfStringGetBeforeSuffix(fileName, '.');

            if (!foundNames->insert(className).second) {
#if PXR_VERSION >= 2508
                 TF_DEBUG(SDR_DISCOVERY)
#else
                 TF_DEBUG(NDR_DISCOVERY)
#endif
                    .Msg(
                     "Duplicate moonray class [%s] found at URI [%s], ignoring.",
                     className.c_str(), uri.c_str());
                continue;
            }

            foundNodes->emplace_back(
                Identifier(className),          // Identifier
                Version().GetAsDefault(),       // Version
                className,                         // Name
                TfToken(),                         // Family
                moonrayNodeType,                   // DiscoveryType
                moonrayNodeType,                   // SourceType
                uri,
                ArGetResolver().Resolve(uri)
            );
        }
    }

    // Continue walking directories
    return true;
}
} // namespace {

const StringVec&
MoonrayDiscoveryPlugin::GetSearchURIs() const
{
    return _searchPaths;
}

MoonrayDiscoveryPlugin::MoonrayDiscoveryPlugin()
{
    const char* env = std::getenv("MOONRAY_CLASS_PATH");
    if (env) {
        _searchPaths = TfStringSplit(env, ":");
    }
}

NodeDiscoveryResultVec
#if PXR_VERSION >= 2508
MoonrayDiscoveryPlugin::DiscoverShaderNodes(const Context& context)
#else
MoonrayDiscoveryPlugin::DiscoverNodes(const Context& context)
#endif
{
    NodeDiscoveryResultVec foundNodes;
    StringSet foundNames;
    ArResolverScopedCache resolverCache;

    for (const std::string& searchPath : _searchPaths) {

        if (!TfIsDir(searchPath)) {
            continue;
        }

        TfWalkDirs(
            searchPath,
            std::bind(
                &examineFiles,
                &foundNodes,
                &foundNames,
                &context,
                std::placeholders::_1,
                std::placeholders::_3
            ),
            /* topDown = */ true,
            TfWalkIgnoreErrorHandler,
            /* followSymlinks = */ true
        );
    }

    return foundNodes;
}

#if PXR_VERSION >= 2508
SDR_REGISTER_DISCOVERY_PLUGIN(MoonrayDiscoveryPlugin);
#else
NDR_REGISTER_DISCOVERY_PLUGIN(MoonrayDiscoveryPlugin);
#endif

PXR_NAMESPACE_CLOSE_SCOPE
