# SR-SHELL
A linux shell written in C.

_The SR in SR-SHELL comes from the initials of my name, just if you were curious._

## Build Instructions
Building the shell is simple.
* Clone the repository.
* `cd` into the project-directory.
* Run `make` to build the shell.
* Run `./sr-shell` to start (and be welcomed by) the shell.
* Run `make clean` to get rid of the object files created.

## Highlights

### History Recall
* To move up/down while recalling command history, press `UP/DOWN ARROW` and then keep pressing `ENTER` key until you reach the desired command.
* On every press of `ENTER` key, you will see the corresponding command record from history.
* To execute the desired command, press `RIGHT ARROW` followed by `ENTER` key.
* To leave the history recall mode anytime, press `LEFT ARROW` followed by `ENTER` key.
* To view full history, execute `history`. To clear the history, execute `history clear`.

### Aliases and the `.srshell_rc` File
* Yeah, you can set aliases for frequently used commands with the help of `alias` command. Eg. `alias c="clear"`
* Though, by entering the above command in the shell, it will remain active only for that session. You can store the aliases permanently by inserting the alias commands in `.srshell_rc` file which is in the `HOME` directory.
* The `.srshell_rc` file gets sourced everytime the shell is run. For explicit sourcing, enter `source <PATH-TO-FILE>`.

### Layout Highlights
* Colorful and informative prompt, giving info about the `USER`, `HOSTNAME`, current working directory.
* Also, it displays the git branch if the directory is a git repository.

*A demo of the entire thing is covered in the screen-recorded GIF above.*

## Features

* Builtin commands supported (*just to list some*):
  * alias
  * cd
  * echo
  * history
  * ls
  * ps
  * pkill
  * pwd
  * source
  * quit  
* Input and Output redirection supported.
* Single piping supported.
* History stored in `.srshell_hist` file in `HOME` directory.

### Yet to be done:
* Builtin commands (*just to list some*):
  * fg
  * bg
  * jobs
  * cronjob
  * `MORE-TO-BE-ADDED`
* Multiple piping.
* Support for `~` as a substitute for `HOME`.
* Combination of commands using `&&`.

## Author
* [Shivansh Rakesh](https://github.com/shivanshrakesh)

## Contribution
Every small bit of contribution is welcomed. Just make sure to open a issue describing the bug / improvement / suggestion / etc. before commencing work.
