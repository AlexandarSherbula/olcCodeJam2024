call "D:\SoftwareDev\emsdk\emsdk_env.bat"

md build\bin\Release\WASM

call em++ -std=c++17 -O2 -s ALLOW_MEMORY_GROWTH=1 -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=2 -s USE_LIBPNG=1 olcCodeJam2024/src/main.cpp olcCodeJam2024/src/Game.cpp olcCodeJam2024/src/Map.cpp olcCodeJam2024/src/Object.cpp olcCodeJam2024/src/olcPixelGameEngine.cpp olcCodeJam2024/src/Assets.cpp olcCodeJam2024/src/Camera.cpp olcCodeJam2024/src/Player.cpp -o build/bin/Release/WASM/pge.html --preload-file .\assets

call emrun build/bin/Release/WASM/index.html