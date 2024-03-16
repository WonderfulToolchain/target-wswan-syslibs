# wf-wswan-syslibs

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
