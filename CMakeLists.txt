cmake_minimum_required(VERSION 3.19)
project(3D_audio LANGUAGES CXX)

find_package(Qt6 6.8 REQUIRED COMPONENTS Multimedia Concurrent Core Widgets LinguistTools)

qt_standard_project_setup()

set(CMAKE_AUTOUIC ON)  # 自动处理ui文件, 自动处理ui文件是有前提的, 必须在需要编译的头文件(add_executable)中的某个头文件中包含ui_xxx.h(比如#include "ui_model002.h")
set(CMAKE_AUTOMOC ON)  # 自动调用moc(元对象编译器)
set(CMAKE_AUTORCC ON)  # 自动处理资源

# 设置 OpenAL 动态库的路径
set(OPENAL_DLL_PATH ${PROJECT_SOURCE_DIR}/dll/soft_oal.dll)

set(PORTAUDIO_LIBRARY_PATH ${PROJECT_SOURCE_DIR}/lib/portaudio_x64.lib)
set(PORTAUDIO_DLL_PATH ${PROJECT_SOURCE_DIR}/dll/portaudio_x64.dll)
# 设置头文件路径
file(GLOB INCLUDE "include/AUDIO/*.h" "include/CONTROL/*.h" "include/GUI/*.h" "include/AL/*.h" "include/PA/*.h")

# 设置ui文件路径
file(GLOB_RECURSE UI_PATH "*.ui")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
list(APPEND CMAKE_AUTOUIC_SEARCH_PATHS "./form")
# 设置资源文件qrc路径
file(GLOB_RECURSE QRC_PATH ./resources/resources.qrc)

aux_source_directory (src/. SRC_LIST)
aux_source_directory (src/AUDIO/. SRC_LIST)
aux_source_directory (src/CONTROL/. SRC_LIST)
aux_source_directory (src/GUI/. SRC_LIST)


qt_add_executable(3D_audio
    WIN32 MACOSX_BUNDLE

    ${SRC_LIST}
    ${QRC_PATH}
    ${INCLUDE}
    ${UI_PATH}
)

# 设置头文件路径
target_include_directories(3D_audio PUBLIC
    ${PROJECT_SOURCE_DIR}/include/
    ${PROJECT_SOURCE_DIR}/include/AUDIO
    ${PROJECT_SOURCE_DIR}/include/CONTROL
    ${PROJECT_SOURCE_DIR}/include/GUI
    ${PROJECT_SOURCE_DIR}/include/PA
)



# qt_add_translations(
#     TARGETS 3D_audio
#     TS_FILES 3D_audio_zh_CN.ts
# )


target_link_libraries(3D_audio
    PUBLIC
        Qt::Core
        Qt::Widgets
        Qt6::Multimedia
        Qt6::Concurrent
        ${PORTAUDIO_LIBRARY_PATH}
        ${OPENAL_DLL_PATH}
        ${PORTAUDIO_DLL_PATH}
)

include(GNUInstallDirs)

install(TARGETS 3D_audio
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET 3D_audio
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

# ├─build
# │  ├─.qt
# │  ├─3D_audio_autogen
# │  │  └─include
# │  └─CMakeFiles
# │      ├─3D_audio.dir
# │      │  ├─3D_audio_autogen
# │      │  └─src
# │      │      ├─AUDIO
# │      │      ├─CONTROL
# │      │      └─GUI
# │      ├─3D_audio_autogen.dir
# │      ├─3D_audio_autogen_timestamp_deps.dir
# │      ├─4.0.1
# │      │  └─CompilerIdCXX
# │      │      └─tmp
# │      ├─CMakeScratch
# │      ├─pkgRedirects
# │      └─Progress
# ├─dll
# ├─form
# ├─include
# │  ├─AL
# │  ├─AUDIO
# │  ├─CONTROL
# │  ├─GUI
# │  └─UI
# ├─lib
# ├─resources
# │  ├─icons
# │  ├─music
# │  └─qss
# └─src
#     ├─AUDIO
#     ├─CONTROL
#     └─GUI


# E:\WorkPlace\QT\3D_audio_rebuild\build
# E:\WorkPlace\QT\3D_audio_rebuild\CMakeLists.txt
# E:\WorkPlace\QT\3D_audio_rebuild\CMakeLists.txt.autosave
# E:\WorkPlace\QT\3D_audio_rebuild\CMakeLists.txt.user
# E:\WorkPlace\QT\3D_audio_rebuild\dll
# E:\WorkPlace\QT\3D_audio_rebuild\form
# E:\WorkPlace\QT\3D_audio_rebuild\include
# E:\WorkPlace\QT\3D_audio_rebuild\lib
# E:\WorkPlace\QT\3D_audio_rebuild\resources
# E:\WorkPlace\QT\3D_audio_rebuild\src
# E:\WorkPlace\QT\3D_audio_rebuild\build\.qt
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeCache.txt
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles
# E:\WorkPlace\QT\3D_audio_rebuild\build\cmake_install.cmake
# E:\WorkPlace\QT\3D_audio_rebuild\build\Makefile
# E:\WorkPlace\QT\3D_audio_rebuild\build\.qt\3D_audio-plugins.cmake
# E:\WorkPlace\QT\3D_audio_rebuild\build\.qt\deploy__3D_audio_de6d1b2b17.cmake
# E:\WorkPlace\QT\3D_audio_rebuild\build\.qt\QtDeploySupport.cmake
# E:\WorkPlace\QT\3D_audio_rebuild\build\.qt\QtDeployTargets.cmake
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\deps
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\include
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\LETX6WCXY7
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\MELDYZ2Z65
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\mocs_compilation.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\moc_predefs.h
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\RCUKELS2VO
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\timestamp
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\LETX6WCXY7\moc_audiosourcepanel.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\LETX6WCXY7\moc_audiosourcepanel.cpp.d
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\LETX6WCXY7\moc_draggableitem.cppE:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\LETX6WCXY7\moc_draggableitem.cpp.d
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\LETX6WCXY7\moc_draggablelistener.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\LETX6WCXY7\moc_draggablelistener.cpp.d
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\LETX6WCXY7\moc_draggablesource.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\LETX6WCXY7\moc_draggablesource.cpp.d
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\LETX6WCXY7\moc_mapscene.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\LETX6WCXY7\moc_mapscene.cpp.d
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\LETX6WCXY7\moc_occlusionfilterpanel.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\LETX6WCXY7\moc_occlusionfilterpanel.cpp.d
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\LETX6WCXY7\moc_parameterwidget.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\LETX6WCXY7\moc_parameterwidget.cpp.d
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\LETX6WCXY7\moc_sourceparameterwidget.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\LETX6WCXY7\moc_sourceparameterwidget.cpp.d
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\LETX6WCXY7\moc_wallrectitem.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\LETX6WCXY7\moc_wallrectitem.cpp.d
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\LETX6WCXY7\moc_waveformwidget.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\LETX6WCXY7\moc_waveformwidget.cpp.d
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\LETX6WCXY7\moc_xwidget.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\LETX6WCXY7\moc_xwidget.cpp.d
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\MELDYZ2Z65\moc_audiorecorder.cppE:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\MELDYZ2Z65\moc_audiorecorder.cpp.d
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\MELDYZ2Z65\moc_auxeffectslot.cppE:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\MELDYZ2Z65\moc_auxeffectslot.cpp.d
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\RCUKELS2VO\moc_audiomanager.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\RCUKELS2VO\moc_audiomanager.cpp.d
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\RCUKELS2VO\moc_roommap.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\build\3D_audio_autogen\RCUKELS2VO\moc_roommap.cpp.d
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio.dir
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio_autogen.dir
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio_autogen_timestamp_deps.dir
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\4.0.1
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\cmake.check_cache
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\CMakeConfigureLog.yaml
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\CMakeDirectoryInformation.cmake
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\CMakeRuleHashes.txt
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\InstallScripts.json
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\Makefile.cmake
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\Makefile2
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\pkgRedirects
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\Progress
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\progress.marks
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\TargetDirectories.txt
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio.dir\3D_audio_autogen
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio.dir\build.make
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio.dir\cmake_clean.cmake
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio.dir\compiler_depend.make
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio.dir\compiler_depend.ts
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio.dir\depend.make
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio.dir\DependInfo.cmake
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio.dir\flags.make
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio.dir\includes_CXX.rsp
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio.dir\link.txt
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio.dir\linkLibs.rsp
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio.dir\objects1.rsp
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio.dir\progress.make
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio.dir\src
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio.dir\src\AUDIO
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio.dir\src\CONTROL
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio.dir\src\GUI
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio_autogen.dir\AutogenInfo.json
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio_autogen.dir\AutogenUsed.txt
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio_autogen.dir\build.make
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio_autogen.dir\cmake_clean.cmakeE:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio_autogen.dir\compiler_depend.make
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio_autogen.dir\compiler_depend.ts
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio_autogen.dir\DependInfo.cmake
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio_autogen.dir\ParseCache.txt
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio_autogen.dir\progress.make
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio_autogen_timestamp_deps.dir\build.make
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio_autogen_timestamp_deps.dir\cmake_clean.cmake
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio_autogen_timestamp_deps.dir\compiler_depend.make
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio_autogen_timestamp_deps.dir\compiler_depend.ts
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio_autogen_timestamp_deps.dir\DependInfo.cmake
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\3D_audio_autogen_timestamp_deps.dir\progress.make
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\4.0.1\CMakeCXXCompiler.cmake
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\4.0.1\CMakeDetermineCompilerABI_CXX.bin
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\4.0.1\CMakeRCCompiler.cmake
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\4.0.1\CMakeSystem.cmake
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\4.0.1\CompilerIdCXX
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\4.0.1\CompilerIdCXX\a.exe
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\4.0.1\CompilerIdCXX\CMakeCXXCompilerId.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\4.0.1\CompilerIdCXX\tmp
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\Progress\1
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\Progress\23
# E:\WorkPlace\QT\3D_audio_rebuild\build\CMakeFiles\Progress\count.txt
# E:\WorkPlace\QT\3D_audio_rebuild\dll\OpenAL32.dll
# E:\WorkPlace\QT\3D_audio_rebuild\form\audiosourcepanel.ui
# E:\WorkPlace\QT\3D_audio_rebuild\form\occlusionfilterpanel.ui
# E:\WorkPlace\QT\3D_audio_rebuild\form\roommap.ui
# E:\WorkPlace\QT\3D_audio_rebuild\form\sourceparameterwidget.ui
# E:\WorkPlace\QT\3D_audio_rebuild\form\xwidget.ui
# E:\WorkPlace\QT\3D_audio_rebuild\include\AL
# E:\WorkPlace\QT\3D_audio_rebuild\include\AUDIO
# E:\WorkPlace\QT\3D_audio_rebuild\include\CONTROL
# E:\WorkPlace\QT\3D_audio_rebuild\include\GUI
# E:\WorkPlace\QT\3D_audio_rebuild\include\UI
# E:\WorkPlace\QT\3D_audio_rebuild\include\AL\al.h
# E:\WorkPlace\QT\3D_audio_rebuild\include\AL\alc.h
# E:\WorkPlace\QT\3D_audio_rebuild\include\AL\alext.h
# E:\WorkPlace\QT\3D_audio_rebuild\include\AL\efx-creative.h
# E:\WorkPlace\QT\3D_audio_rebuild\include\AL\efx-presets.h
# E:\WorkPlace\QT\3D_audio_rebuild\include\AL\efx.h
# E:\WorkPlace\QT\3D_audio_rebuild\include\AUDIO\audiorecorder.h
# E:\WorkPlace\QT\3D_audio_rebuild\include\AUDIO\audiosource.h
# E:\WorkPlace\QT\3D_audio_rebuild\include\AUDIO\auxeffectslot.h
# E:\WorkPlace\QT\3D_audio_rebuild\include\AUDIO\listener.h
# E:\WorkPlace\QT\3D_audio_rebuild\include\AUDIO\occlusionfilter.h
# E:\WorkPlace\QT\3D_audio_rebuild\include\AUDIO\parametercalculationengine.h
# E:\WorkPlace\QT\3D_audio_rebuild\include\CONTROL\audiomanager.h
# E:\WorkPlace\QT\3D_audio_rebuild\include\CONTROL\roommap.h
# E:\WorkPlace\QT\3D_audio_rebuild\include\GUI\audiosourcepanel.h
# E:\WorkPlace\QT\3D_audio_rebuild\include\GUI\draggableitem.h
# E:\WorkPlace\QT\3D_audio_rebuild\include\GUI\draggablelistener.h
# E:\WorkPlace\QT\3D_audio_rebuild\include\GUI\draggablesource.h
# E:\WorkPlace\QT\3D_audio_rebuild\include\GUI\mapscene.h
# E:\WorkPlace\QT\3D_audio_rebuild\include\GUI\occlusionfilterpanel.h
# E:\WorkPlace\QT\3D_audio_rebuild\include\GUI\parameterwidget.h
# E:\WorkPlace\QT\3D_audio_rebuild\include\GUI\sourceparameterwidget.h
# E:\WorkPlace\QT\3D_audio_rebuild\include\GUI\wallrectitem.h
# E:\WorkPlace\QT\3D_audio_rebuild\include\GUI\waveformwidget.h
# E:\WorkPlace\QT\3D_audio_rebuild\include\GUI\xwidget.h
# E:\WorkPlace\QT\3D_audio_rebuild\resources\icons
# E:\WorkPlace\QT\3D_audio_rebuild\resources\music
# E:\WorkPlace\QT\3D_audio_rebuild\resources\qss
# E:\WorkPlace\QT\3D_audio_rebuild\resources\resources.qrc
# E:\WorkPlace\QT\3D_audio_rebuild\resources\icons\listener.svg
# E:\WorkPlace\QT\3D_audio_rebuild\resources\icons\play.svg
# E:\WorkPlace\QT\3D_audio_rebuild\resources\icons\stop.svg
# E:\WorkPlace\QT\3D_audio_rebuild\resources\icons\test.svg
# E:\WorkPlace\QT\3D_audio_rebuild\resources\music\lia.mp3
# E:\WorkPlace\QT\3D_audio_rebuild\resources\music\lia.wav
# E:\WorkPlace\QT\3D_audio_rebuild\resources\music\recorder.wav
# E:\WorkPlace\QT\3D_audio_rebuild\resources\music\test.mp3
# E:\WorkPlace\QT\3D_audio_rebuild\resources\music\test2.wav
# E:\WorkPlace\QT\3D_audio_rebuild\resources\music\wave1.wav
# E:\WorkPlace\QT\3D_audio_rebuild\resources\music\wave2.wav
# E:\WorkPlace\QT\3D_audio_rebuild\resources\music\wave3.wav
# E:\WorkPlace\QT\3D_audio_rebuild\resources\qss\contentwidget.qss
# E:\WorkPlace\QT\3D_audio_rebuild\resources\qss\xwidget.qss
# E:\WorkPlace\QT\3D_audio_rebuild\src\AUDIO
# E:\WorkPlace\QT\3D_audio_rebuild\src\CONTROL
# E:\WorkPlace\QT\3D_audio_rebuild\src\GUI
# E:\WorkPlace\QT\3D_audio_rebuild\src\main.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\src\AUDIO\audiorecorder.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\src\AUDIO\audiosource.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\src\AUDIO\auxeffectslot.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\src\AUDIO\listener.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\src\AUDIO\occlusionfilter.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\src\AUDIO\parametercalculationengine.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\src\CONTROL\audiomanager.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\src\CONTROL\roommap.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\src\GUI\audiosourcepanel.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\src\GUI\draggableitem.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\src\GUI\draggablelistener.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\src\GUI\draggablesource.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\src\GUI\mapscene.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\src\GUI\occlusionfilterpanel.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\src\GUI\parameterwidget.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\src\GUI\sourceparameterwidget.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\src\GUI\wallrectitem.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\src\GUI\waveformwidget.cpp
# E:\WorkPlace\QT\3D_audio_rebuild\src\GUI\xwidget.cpp
