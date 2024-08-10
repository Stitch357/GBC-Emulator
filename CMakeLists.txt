cmake_minimum_required(VERSION 3.10)
project(GBC_Emulator VERSION 0.00.01)

# Specify the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Set the build type to Debug
set(CMAKE_BUILD_TYPE Debug)

# Include directories
include_directories(
    "${PROJECT_SOURCE_DIR}/GBC_Emulator_Library/APU"
    "${PROJECT_SOURCE_DIR}/GBC_Emulator_Library/CPU"
    "${PROJECT_SOURCE_DIR}/GBC_Emulator_Library/Cartridge"
    "${PROJECT_SOURCE_DIR}/GBC_Emulator_Library/GB"
    "${PROJECT_SOURCE_DIR}/GBC_Emulator_Library/Main Instructions"
    "${PROJECT_SOURCE_DIR}/GBC_Emulator_Library/MBC"
    "${PROJECT_SOURCE_DIR}/GBC_Emulator_Library/Misc"
    "${PROJECT_SOURCE_DIR}/GBC_Emulator_Library/PPU"
    "${PROJECT_SOURCE_DIR}/GBC_Emulator_Library/Prefix CB Instructions"
    "${PROJECT_SOURCE_DIR}/GBC_Emulator_Library/Structs"
    "${PROJECT_SOURCE_DIR}/GBC_Emulator_Library/Enums"
)

# Add the executable
add_executable(GBC_Emulator
    src/emu.c
    GBC_Emulator_Library/APU/apu.c
    GBC_Emulator_Library/CPU/cpu.c
    GBC_Emulator_Library/Cartridge/cartridge.c
    GBC_Emulator_Library/GB/gameboy.c
    GBC_Emulator_Library/Main\ Instructions/mi.c
    GBC_Emulator_Library/MBC/mbc.c
    GBC_Emulator_Library/Misc/misc.c
    GBC_Emulator_Library/PPU/ppu.c
    GBC_Emulator_Library/Prefix\ CB\ Instructions/cbi.c
)

# Specify any necessary libraries to link with (if applicable)
# target_link_libraries(GBC_Emulator PRIVATE some_library)