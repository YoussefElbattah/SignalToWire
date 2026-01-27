# SignalToWire - Setup Guide

## Prerequisites
- STM32 development board (STM32L152RE or STM32U385RG)
- OpenOCD installed
- ARM GCC toolchain

## Installation

### 1. Clone the Repository
```bash
git clone git@github.com:YoussefElbattah/SignalToWire.git
cd SignalToWire
```

### 2. Configure VS Code Settings

Edit `.vscode/launch.json`:
```json
{
    "configurations": [
        {
            "configFiles": [
                "path/to/your/openocd/folder/openocd/scripts/interface/stlink.cfg",
                "path/to/your/openocd/folder/openocd/scripts/target/stm32u3x.cfg"
            ]
        }
    ]
}
```

Edit `.vscode/settings.json` with your GDB and OpenOCD paths.

### 3. Build the Project

Choose your board and build:
```bash
make BOARD=stm32u385rg
make bin BOARD=stm32u385rg
```

Available boards: `stm32l152re`, `stm32u385rg`

### 4. Install VS Code Extensions
- Cortex-Debug (Manus)
- C/C++ (Microsoft)

### 5. Debug
Restart VS Code, then click the Debug button (left sidebar) to start debugging.

## Supported Boards
- STM32L152RE
- STM32U385RG