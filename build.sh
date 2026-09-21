#!/bin/zsh
xcode-select -s /Applications/Xcode.app/Contents/Developer
xcrun clang -arch arm64 -miphoneos-version-min=17.0 -framework IOKit -o aveprobe ave_probe.c
mkdir -p Payload/aveprobe.app
cp aveprobe Payload/aveprobe.app/
cd Payload
zip -r ../aveprobe.ipa *
