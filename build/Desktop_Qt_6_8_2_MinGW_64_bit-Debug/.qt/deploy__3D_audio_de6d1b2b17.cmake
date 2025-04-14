include(E:/WorkPlace/QT/3D_audio_rebuild/3D_audio/build/Desktop_Qt_6_8_2_MinGW_64_bit-Debug/.qt/QtDeploySupport.cmake)
include("${CMAKE_CURRENT_LIST_DIR}/3D_audio-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase;qtmultimedia")

qt6_deploy_runtime_dependencies(
    EXECUTABLE E:/WorkPlace/QT/3D_audio_rebuild/3D_audio/build/Desktop_Qt_6_8_2_MinGW_64_bit-Debug/3D_audio.exe
    GENERATE_QT_CONF
)
