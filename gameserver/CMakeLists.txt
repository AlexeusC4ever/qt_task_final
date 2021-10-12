find_package(Qt6 REQUIRED Widgets Network)

qt_wrap_cpp(
    NET_MOC_WRAPPERS
    server-dlg.h)

qt_wrap_ui(
    NET_UIC_WRAPPERS
    server-dlg.ui)
	
add_library(
	server STATIC
	server-dlg.cpp
	server-dlg.h
	${NET_MOC_WRAPPERS}
	${NET_UIC_WRAPPERS}
)

target_link_libraries(server Qt6::Widgets Qt6::Network)
