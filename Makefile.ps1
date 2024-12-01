param (
    [Parameter(Mandatory=$true)]
    [string]$Action
)
$project = Get-Location
switch ($Action) {
    "conf" {
        mkdir build
        Set-Location -Path $project\build
        Write-Host "Configuring..."
        cmake .. "-DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake" -G "Visual Studio 17 2022" -DCMAKE_CXX_STANDARD=17 -A x64
        Set-Location -Path $project
    }
    "del" {
        Write-Host "Delete..."
        RM -r build
    }
    "build" {
        Set-Location -Path $project\build
        Write-Host "Building..."
        cmake --build .
        Set-Location -Path $project
    }
    default {
        Write-Host "Unknown action: $Action"
    }
}