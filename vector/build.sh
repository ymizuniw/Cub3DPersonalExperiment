#!/bin/bash

cc -Wall -Wextra -Werror -I. -c *.c
ar rcs vector.a *.o