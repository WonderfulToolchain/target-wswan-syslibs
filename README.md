# target-wswan-syslibs

This repository provides the base system libraries for the WSwan/WWitch targets:

* **crts**, crt0 implementations;
* **libc**, a shoehorned-together partial implementation based in part on the following projects:
    * [nanoprintf](https://github.com/charlesnicholson/nanoprintf)
    * [PDCLib](https://github.com/DevSolar/pdclib);
* **libws**, WSwan system library;
* **libwsx**, WSwan/WWitch extra library;
* **libww**, WWitch system library;
* **libwwcl**, WWitch compatibility layer for WS;
* **target**, additional buildsystem/include files.

## License

The system libraries as a whole are available under the terms of the zlib license.

In addition, code from **libc** may be used under Creative Commons Zero/"public domain" terms.

As part of its text engine, **libwwcl** contains fonts under the following terms:

* [Misaki](https://littlelimit.net/misaki.htm) by Little Limit:

    These fonts are free software.
    Unlimited permission is granted to use, copy, and distribute them, with or without modification, either commercially or noncommercially.
    THESE FONTS ARE PROVIDED "AS IS" WITHOUT WARRANTY.

* [Unscii](http://viznut.fi/unscii/) by Viznut:

     The two main variants are unscii-8 (8×8 pixels per glyph) and unscii-16 (8×16).
     [...] 
     "unscii-16-full" falls under GPL because of how Unifont is
     licensed; the other variants are in the Public Domain.

As the "unscii-16-full" variant is not used, the variant used in target-wswan-syslibs falls under the public domain.
