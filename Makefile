
# deprecated
compile: 
	g++ main.cpp

# deprecated
run: 
	./a.out

test-gstreamer:
	gst-launch-1.0 videotestsrc ! videoconvert ! autovideosink

# TODO: consider splitting into separate targets for ffmpeg xor gstreamer
install-opencv:
	..\vcpkg\vcpkg.exe install opencv4[ffmpeg,gstreamer]:x64-windows --recurse

cmake-toolchain:
	cmake "-DCMAKE_TOOLCHAIN_FILE=C:/Users/prometheus/Documents/vcpkg/scripts/buildsystems/vcpkg.cmake" 
# cmake "-DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake" 

# TODO: add vcpkg to PATH and include instructions in README
vcpkg-list:
	..\vcpkg\vcpkg.exe list

install-opencv:
	..\vcpkg\vcpkg.exe install opencv[core]:x64-windows

gen-playlist:
	ffmpeg -i input.mp4 -codec: copy -start_number 0 -hls_time 10 -hls_list_size 0 -f hls playlist.m3u8

fetch-video: 
	yt-dlp -f mp4 "https://www.youtube.com/watch?v=7mCUoUaQsLE"

# test url: http://localhost:8080/hls/playlist.m3u8

# sample file rcs: http://sample.vodobox.net/skate_phantom_flex_4k/skate_phantom_flex_4k.m3u8

# note, m308 is not a video format; it's a pointer to an online video source

# the source in the server is town0.avi

conf: 
	.\Makefile.ps1 conf

build: 
	.\Makefile.ps1 build

delete: 
	.\Makefile.ps1 delete