@echo off

call ./installer/spdlog_installer Release
call ./installer/glad_installer Release
call ./installer/imgui_installer Release
call ./installer/eigen_installer Release
call ./installer/nlohmann_json_installer Release
call ./installer/vulkan_installer Release