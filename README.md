# image_logger

Saves all images from a data channel into a directory on your local hard drive.

Currently only GREY/RGB images and only the PGM/PPM file formats are supported.

## Config
- **image_channel** - Read images from this data channel.
- **directory** - Write all images into this local folder.
- **format** - Image file format, either pgm or ppm.

## Dependencies
- [imaging](https://github.com/syxolk/imaging)

## Recommended modules
- [image_converter](https://github.com/syxolk/image_converter) - to convert the image to another format before saving it
- [camera_importer](https://github.com/Phibedy/camera) - to get an image from a camera
