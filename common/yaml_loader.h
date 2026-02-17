//--------------------------------------------
//
// Yamlローダー [yaml_loader.h]
// Author: Fuma Sato
//
//--------------------------------------------
#pragma once
#include "native_file.h"
#include <yaml-cpp/yaml.h>

namespace file
{
    // 読み込み
    YAML::Node loadYaml(const std::filesystem::path& path);
}
