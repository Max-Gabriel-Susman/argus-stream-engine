# Argus Stream Engine 

Argus Stream Engine is the Argus Platform's framework for stream management

## Where We're At Now

12/01/24 Just moved all of the Argus Stream Engine stuff to a new Argus-Stream-Engine repository. We got vcpkg setup and behaving properly. Created a new argus-ios-client respository as it's going to posess both stream ingress and egress client features to expedite development of the platform. Still working on getting the demo from https://www.funvisiontutorials.com/2024/08/hls-video-streaming-from-opencv-and.html#Project_Structure to function all the way.

## Dependencies

* gstreamer

## Setup

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
