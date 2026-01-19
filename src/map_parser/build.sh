#!/bin/bash

cc -Wall -Wextra -Werror -c *.c
ar rcs libparse_map.a *.o