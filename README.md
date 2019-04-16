# snake-game
A snake game simulation

## Building

Build by making a build directory (i.e. `build/`), run `cmake` in that dir, and then use `make` to build the desired target.

Example:

``` bash
$ mkdir build && cd build
$ cmake .. # argument is location of CMakelists.txt
$ make
$ make gtest
$ ./snake.x
```

```bash
zhajio@ubuntu:~/github/snake/build$ ./snake.x 
Enter filename: ../level.txt
###############
#$           $#
#   #     #   #
#   #     #   #
#   #  $  #   #
#   #     #   #
#   #     #   #
#             #
#   #     #   #
#   #     #   #
#   #  $  #   #
#   #     # * #
#   #     #   #
#$           $#
###############
Food eaten: 0
```
