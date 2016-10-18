set ( SOURCES
    "src/interface.cpp"
    "src/image_logger.cpp"
)

set (HEADERS
    "include/image_logger.h"
	${HEADERS_SHARED}
)

include_directories("include")

add_library ( image_logger MODULE ${SOURCES} ${HEADERS})
target_link_libraries(image_logger PRIVATE lmscore lms_imaging)
