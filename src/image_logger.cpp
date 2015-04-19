#include <cstdio>
#include <sys/stat.h>
#include <sys/types.h>

#include "image_logger.h"
#include "lms/datamanager.h"
#include "lms/imaging/pnm.h"

bool ImageLogger::initialize() {
    config = getConfig();

    std::string imageChannel = config->get<std::string>("image_channel");
    directory = config->get<std::string>("directory");
    format = config->get<std::string>("format");
    filepattern = config->get<std::string>("filepattern");
    bool createDateSubdirectory = config->get<bool>("create_subfolder_with_current_date");
    imageCounter = 0;

    if(directory.empty()) {
        logger.error("init") << "directory is empty";
        return false;
    }

    if(imageChannel.empty()) {
        logger.error("init") << "image_channel is empty";
        return false;
    }

    if(format.empty()) {
        logger.error("init") << "format was not specified";
        return false;
    } else if(format != "pgm" && format != "ppm") {
        logger.error("init") << "format must be either pgm or ppm";
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

    imagePtr = datamanager()->readChannel<lms::imaging::Image>(this, imageChannel);
    return true;
}

bool ImageLogger::deinitialize() {
    return true;
}

bool ImageLogger::cycle() {
    bool result = false;

    char name[50];
    std::snprintf(name, sizeof(name), filepattern.c_str(), imageCounter);
    std::string fullPath = directory + "/" + name;

    if(format == "pgm") {
        if(imagePtr->format() != lms::imaging::Format::GREY) {
            logger.error("cycle") << "Image is in format " << imagePtr->format()
                                  << " but expected " << lms::imaging::Format::GREY;
            return false;
        }

        result = lms::imaging::savePGM(*imagePtr, fullPath);
    } else if(format == "ppm") {
        if(imagePtr->format() != lms::imaging::Format::RGB) {
            logger.error("cycle") << "Image is in format " << imagePtr->format()
                                  << " but expected " << lms::imaging::Format::RGB;
            return false;
        }

        result = lms::imaging::savePPM(*imagePtr, fullPath);
    }

    if(! result) {
        logger.warn("cycle") << "Could not write image";
    }

    imageCounter++;
    return true;
}
