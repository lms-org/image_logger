#include <cstdio>
#include <sys/stat.h>
#include <sys/types.h>

#include "image_logger.h"
#include "lms/datamanager.h"
#include "lms/imaging/pnm.h"

bool ImageLogger::initialize() {
    directory = config().get<std::string>("directory");
    filepattern = config().get<std::string>("filepattern");
    bool createDateSubdirectory = config().get<bool>("create_subfolder_with_current_date");
    imageCounter = 0;

    if(directory.empty()) {
        logger.error("init") << "directory is empty";
        return false;
    }

    if(filepattern.empty()) {
        logger.error("init") << "filepattern was not specified";
        return false;
    }

    if(createDateSubdirectory) {
        char dateDir[50];

        time_t rawtime;
        time (&rawtime);
        tm *t = gmtime(&rawtime);
        snprintf(dateDir, sizeof(dateDir), "%04i%02i%02i-%02i%02i%02i",
            t->tm_year+1900,
            t->tm_mon+1,
            t->tm_mday,
            t->tm_hour,
            t->tm_min,
            t->tm_sec
        );

        directory = directory + "/" + dateDir;

        // create directory if not existing (ignoring any errors here)
        mkdir(directory.c_str(), 0775);
    }

    logger.debug("init") << "Log images to " << directory;

    imagePtr = readChannel<lms::imaging::Image>("IMAGE");
    return true;
}

bool ImageLogger::deinitialize() {
    return true;
}

bool ImageLogger::cycle() {
    using lms::imaging::Format;

    bool result = false;

    char name[50];
    std::snprintf(name, sizeof(name), filepattern.c_str(), imageCounter);
    std::string fullPath = directory + "/" + name;

    switch(imagePtr->format()) {
    case Format::GREY:
        result = lms::imaging::savePGM(*imagePtr, fullPath + ".pgm");
        break;
    case Format::RGB:
        result = lms::imaging::savePPM(*imagePtr, fullPath + ".ppm");
        break;
    default:
        logger.error("cycle")
            << "Image format is neither GREY nor RGB, but "
            << imagePtr->format();
        return false;
    }

    if(! result) {
        logger.warn("cycle") << "Could not write image";
        return false;
    }else{
        logger.debug("cycle") << "Wrote image: " << fullPath;
    }

    imageCounter++;

    return true;
}
