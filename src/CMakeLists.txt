add_executable(fe-xico-doctor)

ecm_add_qml_module(fe-xico-doctor
    URI io.github.royoshi.fexicodoctor
)

target_sources(fe-xico-doctor
    PRIVATE
        main.cpp
        doctorbackend.cpp
        doctorbackend.h
)

ecm_target_qml_sources(fe-xico-doctor
    SOURCES
        Main.qml
)

target_link_libraries(fe-xico-doctor
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
        Qt6::QuickControls2
        Qt6::Widgets
        KF6::I18n
        KF6::CoreAddons
        KF6::IconThemes
)

install(
    TARGETS fe-xico-doctor
    ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
)