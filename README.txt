Simple UUID Type 1 Generate

base code is from 
http://www.ietf.org/rfc/rfc4122.txt

Compile:

`cc -o uuid main.c uuid.c sysdep.c -lcrypto'

Changes:
* remove Windows support (because we don't need it)
* reformat code style
* remove file read and write (find a better way performance)

You should change `get_ieee_node_identifier' if needed.

License
see copyrt.h

