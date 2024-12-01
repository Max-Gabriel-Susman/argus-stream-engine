# Argus Stream Engine 

Argus Stream Engine is the Argus Platform's framework for stream management


## Dependencies

* gstreamer

## Setup

https://www.funvisiontutorials.com/2023/11/opencv-installed-by-vcpkg-package.html

cmake "-DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake" -DCMAKE_CXX_STANDARD=17 -A x64

vcpkg install opencv:x64-windows ffmpeg:x64-windows

.\Makefile.ps1 conf
.\Makefile.ps1 del
.\Makefile.ps1 build

This repository uses vcpkg for pkg mgmt, instructions for vcpkg setup can be found online.


1. Opencv installed by VCPKG package manager for CMAKE project

2. Build process 

## TODOs 

* CODEOWNERS - created, need to verify it's good

* HLS stream server - can serve content via api exposure, need to extend api to allow storage of content by clients

* gh action CI - created, need to verify it's good

* test coverage 

* docker image for containerization - created, need to verify it's good

* cloud infrastructure for hosting 

* parameterization for the service and it's infrastructure 

* it looks like we're gonna want to eventually move vcpkg to root level as opposed to in documents

* add vcpkg to path 

* grok m3u8, it's not a file format persay but rather a ptr to resources that can be streamed

## NOTE

* vcpkg has been moved to root since a lot of the make targets that consume it were created

## Local Development Usage

### Test Streaming With VLC media player

1. select media > Open Network Stream

2. use the following network url: http://localhost:8080/hls/playlist.m3u8

3. hit Play, audio/video should resemble the resource at http://sample.vodobox.net/skate_phantom_flex_4k/skate_phantom_flex_4k.m3u8
