# image_logger

Saves all images from a data channel into a directory on your local hard drive.

Currently only GREY images and only the PGM file format are supported.

## Config
- **image_channel** - Read images from this data channel.
- **directory** - Write all images into this local folder.

## Dependencies
- [imaging](https://github.com/syxolk/imaging)

## Recommended modules
- [image_converter](https://github.com/syxolk/image_converter) - to convert the image to another format before saving it
- [camera_importer](https://github.com/Phibedy/camera) - to get an image from a camera
