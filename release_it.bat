set CMAKE_BUILDDIR=..\build\0.3.5\cmake\vc
set STARTDIR=%CD%
@if "%VS71COMNTOOLS%"=="" call "%VS80COMNTOOLS%\vsvars32.bat"
@if "%VS80COMNTOOLS%"=="" call "%VS71COMNTOOLS%\vsvars32.bat"

mkdir -p %CMAKE_BUILDDIR%

cd %CMAKE_BUILDDIR%
cmake -D WITH_DOCS:bool=ON -D WITH_MYSQL:bool=ON -D WITH_SQLITE:bool=ON -D WITH_TEST:bool=ON  %STARTDIR%
devenv /rebuild Debug litesql.sln /project "RUN_TESTS.vcproj" /projectconfig Debug
devenv /rebuild Release litesql.sln /project "PACKAGE.vcproj" /projectconfig Release

cpack --config CPackSourceConfig.cmake

cd %STARTDIR%

pause