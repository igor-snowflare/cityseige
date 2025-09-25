#!/bin/sh

clear;

echo "Commencing build...";

clang++ main.cpp -o prog \
-F/Library/Frameworks/SDL3.xcframework/macos-arm64_x86_64 \
-framework sdl3 \
-rpath /Library/Frameworks/SDL3.xcframework/macos-arm64_x86_64/ \
\
-F./SDL3_image.xcframework/macos-arm64_x86_64 \
-framework sdl3_image \
-rpath ./SDL3_image.xcframework/macos-arm64_x86_64;

echo "Build done";