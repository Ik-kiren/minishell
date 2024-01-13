### Valgrind:
`valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=valgrind.supp --gen-suppressions=all --track-fds=yes ./minishell`

### Tests
`export TEST="coucou" && echo $TEST` :white_check_mark: 
`<<test` :white_check_mark: (just its sending a `'' command not found`, but not the real bash)
`<<test'test                 'coucou` :white_check_mark: 
`<<test"coucou                         "test` :white_check_mark: 
`te$?st` => te0st :white_check_mark: 
`'te$?st'` => te$?st :white_check_mark: 
`"te$?st"` => te0st :white_check_mark: 
`'$HOME'` => `$HOME` :white_check_mark: 
`"$HOME"` => /home/pioupia/ :white_check_mark: 
`"'$HOME'"` => `'/home/pioupia/'` :white_check_mark: 
`'"$HOME"'` => `"$HOME"` :white_check_mark: 
`<< STOP cat < Makefile` :white_check_mark: 
`<< STOP cat << TEST` :white_check_mark: 
`cat < test.txt < README.md < test.txt  -e` :white_check_mark: 
`cat -e test.txt > salut test > coucou > bjr` (with test file doesn't exist) :white_check_mark: 
`cat -e test.txt > salut > coucou > bjr` :white_check_mark: 
`cd -` (do not manage)
`cd ~` (do not mamage)
`<> world` will create the world file :white_check_mark: 
`<> world cat -e` will open the world file, read it, send its content into the cat command. But the original file is not modified. :x:
`1<> world cat` will edit the content of the world file, and wait the read of the `cat` command...
`echo "test" <> world` will echo in the console then create the world file. :x:
`echo "test" 1<> world` will print nothing but will write `test` in the world file. :x:
`'' "$HOME"` :white_check_mark: (its sending `/home/pioupia` command not found, but it should print `''` command not found)
`'' '$HOME'` :white_check_mark:
`'' $HOME` :white_check_mark:
`< *.h cat` => should return an error if multiple `.h` files, if just one file, thats working (should just print `ambigous redirection` and stop the command here) :white_check_mark: 
`< make* cat | cat -e Makefile` :white_check_mark: 
`cat parser.h > *.c` => Will create a `*.c` file if there is no .c file; if there are 2 .c files or more, it fails :white_check_mark: 
`>> bonjour` => create a `bonjour` file :white_check_mark: 
` $HOME"TEST"` :white_check_mark: 
`export PATH="" && ls` => command not found :white_check_mark:
`echo "test" 8191> coucou` => working :x:
`echo "test" 8192> coucou` => `bash: 8192: Bad file descriptor` :x:
`echo "test" -1> coucou` => no output -> write `test -1\n` in the `coucou` file. :x:
`cat -e Makefile && << test cat` :white_check_mark: 
`cat | cat | cat | ls` => `ls` should be executed before all cat.
`<< lim << lim << lim << lim | cat > out` => open all lim but only send the content of the first lim to the cat command :white_check_mark: 
`cat | asdoijasiod` => send `error not found` then the return code is 127 :white_check_mark: 
`export TEST="coucou===Commenttuvas?" && ./minishell` => the env variable TEST should be well formated.
`<< "$HOME test"coucou` :white_check_mark: 
`"" cat` :white_check_mark:
` << "" "" cat` :white_check_mark: 
`./ls` were `ls` does not exists in the current dir. :white_check_mark: (send too many errors)
`test` where test is an executable in the current directory :white_check_mark:
` << LIM < tset < salut cat | cat < file > output | asdjaisj <>world | > a > b > c > d > e` :x:
` cat -e Makefile| > a > b > c > d > e` :white_check_mark: 
`cat < Makefile > out` :white_check_mark: send the Makefile content into the outfile
`> out` :white_check_mark: (reset the out file)
`<< LIM < test < coucou < salut`  :white_check_mark:  (working but should exit with `1` as status code - don't because of the input file crash).
`cat "$TEST"*'.md'` => with one or many md files :x:
`make*` => work with one file :white_check_mark: 
`make*` if we have a file named `make` and a file named `makecoucou`, the file named `makecoucou` will be set in the args array. :white_check_mark:
`cat < make*` => with one file were its name starts by `make` it'll work. If we have multiple files, that just not working and send an error `bash: make*: ambiguous redirect` :white_check_mark: 
:warning: The wildcard works with directory.
`(cat M*k*)` :white_check_mark:
`cat -e < make* | iadoiausidasdoudo` with ambigous redirection (should print `iadoi... command not found`) :white_check_mark:
`cat -e < "$PWD"/make*` :x:
`(echo 1 && echo 2) | cat` :white_check_mark: 
`cat Makefile | aisdaisdiasdij | cat -e README.md` :white_check_mark: 
`asuidhausid | echo $? | aoisdjiasd | echo $? | echo $? | asdopjasd` will just print errors :white_check_mark: 
`cat | cat | ls > sss || $?` :white_check_mark: 
`export PATH=` => has to refresh the parse array in the minishell struct. :white_check_mark: 
Injecting env variable before the launch of the minishell.
`export TEST="coucou=salut"` :white_check_mark: 
then run the minishell and run:
`echo $TEST` :white_check_mark: 
`exit -2500000` => exit code 96 :white_check_mark: 
`exit -23974` => exit code 90 :white_check_mark: 
`exit 42564` => exit code 68 :white_check_mark: 
`exit test` => exit code 2 + stderr: `exit\nbash: exit: test: numeric argument required` :white_check_mark: 
`exit 0 test` => don't exit + stderr: `exit\nbash: exit: too many arguments` :white_check_mark: 
`cd` => go to the `$HOME` location :white_check_mark: 
`unset HOME && cd` => stderror: `bash: cd: HOME not set` ; status: `1` ; the directory don't move :white_check_mark:
`unset HOME && export HOME && cd` => stderror: `bash: cd: HOME not set` ; status: `1` ; the directory don't move :white_check_mark:
`unset HOME && export HOME= && cd` => status: `0` ; the directory don't move :white_check_mark:
`export HOME=/home/pioupia/unexisting_path && cd` => stderr: `bash: cd: /home/pioupia/unexisting_path: No such file or directory` ; status `1` ; directory don't move :white_check_mark:
`export HOME=./libft && cd`  => change the directory to the local libft dir. :white_check_mark:
`echo 1 || echo 2 | echo 3 | echo 4 || echo 10 || echo 100` => ça echo `1\n` :white_check_mark:
`asdhaosid || echo 2 | echo 3 | echo 4 || echo 10 || echo 100` => ça echo `asdhaosid: command not found` (stderr) + `4` sur une nouvelle ligne. :white_check_mark:
`echo 1 || echo 2 && echo 3` => echo `1`, `3` :white_check_mark:
`echo 3 && aposjdaopsd || echo 2` => echo `3`, `aposjdaopsd: command not found`, `2` :white_check_mark:
`echo 3 && echo 1 || echo 2` => echo `3`, `1` :white_check_mark:
`cat | cat | ls || echo 1` => `cat | cat | ls` normal :white_check_mark:
`cat | cat | ls && echo 1` => `cat | cat | ls` normal mais `1\n` à la fin. :white_check_mark:
`echo 1 || echo 2 && echo 3` => should print `1` and `3` on a new line :white_check_mark:
`echo 1 || (echo 2 && echo 3)` => should print `1` followed by a new line :white_check_mark:
`asdojasoidhaiosdh && (echo 1 || echo 2)` => just an error :white_check_mark:
`asdojasoidhaiosdh && echo 1 || echo 2` => error + echo 2 :white_check_mark:
`<< LIM ''` => take the limiter and `command not found` :white_check_mark: ; status `127`
`<< LIM` => only take the limiter without errors :white_check_mark:  ; status `1`
`<< '' cat` => should not print any errors :white_check_mark:
`echo expr $? + $?` => should print `expr 0 + 0` :white_check_mark:
`echo '' test '' salut '' '' '' '' '' coucou` should print ` test  salut      coucou`
`ca"$TEST"t` if the $TEST variable doesn't exist, this should execute the `cat` command.

Should execute the `echo` command:
```
export H="echo "
$H salut
```

`$TEST cat -e Makefile` should print the Makefile if the `TEST` variable does not exist.

should echo salut:
```
export A=e B=ch C=o
$A$B$C salut
```

`test.sh`:
```sh
while read line
do
  echo "$line"
done < "${1:-/dev/stdin}"
```
`./test.sh | ls` => will execute `ls` before `./test.sh`

`<< a )` => Has to take the here_doc before sending an error
`<< a (` => Has to take the here_doc before sending an error
`<< a ) && << b` => take only the first here_doc before error
`<< a ) << b` => take only the first here_doc before error

Redirections:
```
<< "$H"'T'*W
<< "              $H               "'                    T                               '*W
<< "              $H               "              '                    T                               '*W
<< "$H       test        "              '                    T                               '*W
<< "test  $H "              '                    T                               '*W
<< "test  $H test"              '                    T                               '*W
<< "$H"T *W
```
Try to `control + d`, `control + c` and `control + \` on the here_doc see how the real bash react.

Test Ikar :
- crash sur `echo -n` -> ne crash pas sur les pipe -> fork
- Signal interuption -> valeur de retour pas set en cas d'interuptioon (128 + valeur du signal)
- le parsing des `""` et des `''` se fait apres la verification des commandes -> `"ls"` ne marche pas, contrairement a son vrai commportement
- SHLVL: increment la variable plz
- export sans arguments -> j'aurais aimé les `decalre -x`
- malheureusement, vis-a-vis du pwd/cd/gestion de la variable PWD, il suit le lien symboliques de maniere physiques et pas logiques
	- ex: cd `$HOME/goinfre` puis `cd ..` ne place dans `/goinfre` et non pas dans `$HOME`
- :( les pipes on m'avait dit ils etaient bien et au final ils ont pas le bon comportement (tout les process en meme temps)
- les headers ! point III-6 de la 